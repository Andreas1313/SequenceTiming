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
}

void loop() {
  sequenceLoopGateBarrier();
  sequenceLoopSignalLight();

  if ( ! digitalRead(resetAndStartButton_pin)){
    gate_1.setForceStep(GateStep::S1_StartReference);
  }

  static GateStep oldStep = GateStep::VeryLastEnum;
  if(oldStep != gate_1.getActualStep()){
    oldStep = gate_1.getActualStep();
    Serial.print(F("Actual Step (int): "));
    Serial.print(uint32_t(gate_1.getActualStep()));
    Serial.print(F(". endDelay: "));
    Serial.print(inputAtClass_endDelay_ms[uint32_t(gate_1.getActualStep())]);
    Serial.println(F("ms"));
  }

  static uint32_t printError_ms = millis();
  if (gate_1.getError() == SequenceTimingError::LatestNextStepElapsed && millis() - printError_ms > 3000){
    printError_ms = millis();
    Serial.print(F("error_stepTimeElapsed at Step (int): "));
    Serial.println(uint32_t(gate_1.getActualStep()));
    for(uint32_t stepNumber = 0; stepNumber < uint32_t(GateStep::VeryLastEnum); stepNumber++){
      Serial.print(F("Time when Step was last time active. Step "));
      Serial.print(stepNumber);
      Serial.print(F(": "));
      Serial.print(outputFromClass_stepTime_ms[stepNumber]);
      Serial.println(F("ms. "));
    }
  }
  if (gate_1.getError() == SequenceTimingError::EarliestNextStepNotElapsed && millis() - printError_ms > 3000){
    printError_ms = millis();
    Serial.print(F("error_minimumTime of "));
    Serial.print(inputAtClass_earliestStartNextStep_ms[uint32_t(gate_1.getActualStep())]);
    Serial.print(F(" ms. NotElapsed at Step (int): "));
    Serial.println(uint32_t(gate_1.getActualStep()));
  }
}