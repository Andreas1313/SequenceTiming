void setup() {
  Serial.begin(115200);
  while( ! Serial){}
  delay(100);
  Serial.println();
  Serial.println(F( __DATE__"," __TIME__));

  pinMode(resetAndStartButton_pin,    INPUT_PULLUP);
  pinMode(downSwitch_pin,     INPUT_PULLUP);
  pinMode(requestSwitch_pin,  INPUT_PULLUP);
  pinMode(nearlyUpSwitch_pin, INPUT_PULLUP);
  pinMode(upSwitch_pin,       INPUT_PULLUP);
  pinMode(lightBarrier_pin,   INPUT_PULLUP);
  pinMode(nearlyDown_pin,     INPUT_PULLUP);
  pinMode(moveSlowDown_pin,   OUTPUT);
  pinMode(moveUp_pin,         OUTPUT);
  pinMode(moveSlowUp_pin,     OUTPUT);
  pinMode(moveDown_pin,       OUTPUT);
  pinMode(blinkYellow_pin,    OUTPUT);
  pinMode(blinkError_pin,     OUTPUT);

  //set the start delay of every step
  for (uint32_t step = 0; step < gate_1.get_numberOfSteps(); step++){
    gate_1.set_startDelay_ms(startDelay_ms[step], step);
    gate_1.set_latestStartNextStep_ms(latestStartNextStep_ms[step], step);
    gate_1.set_earliestStartNextStep_ms(earliestStartNextStep_ms[step], step);
    gate_1.set_endDelay_ms(endDelay_ms[step], step);
  }
  for (uint32_t step = 0; step < yellowLight.get_numberOfSteps(); step++){//errorLight and yellowLight have the same number of steps, because they have the same enum class
    yellowLight.set_endDelay_ms(endDelaySignalLight_ms[step], step);
    errorLight.set_endDelay_ms(endDelaySignalLight_ms[step], step);
  }
}

void loop() {
  static uint32_t debounceOld_ms = millis();

  sequenceLoopGateBarrier();
  sequenceLoopYellowLight();
  sequenceLoopErrorLight();
  
  if (digitalRead(resetAndStartButton_pin)){
    debounceOld_ms = millis();
  }
  else if (millis() - debounceOld_ms > 20){  //resetAndStartButton_pin is pressed and debounce time is elapsed
    gate_1.set_forceStepImmediately(GateStep::S1_StartReference);
  }

//for Serial Monitor:
  static GateStep oldStep = GateStep::S9_SlowDown;
  if(oldStep != gate_1.get_actualStep()){
    oldStep = gate_1.get_actualStep();
    Serial.print(F("Actual Step (int): "));
    Serial.println(gate_1.get_actualStep_int());
  }

  static uint32_t printError_ms = millis();
  if (gate_1.get_error_latestStartNextStepElapsed() && millis() - printError_ms > 3000){
    printError_ms = millis();
    Serial.print(F("error_stepTimeElapsed at Step (int): "));
    Serial.println(gate_1.get_actualStep_int());
  }
  if (gate_1.get_error_earliestStartNextStepNotElapsed() && millis() - printError_ms > 3000){
    printError_ms = millis();
    Serial.print(F("error_minimumTimeNotElapsed at Step (int): "));
    Serial.println(gate_1.get_actualStep_int());
  }
}