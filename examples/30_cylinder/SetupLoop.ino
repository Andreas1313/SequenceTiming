void setup(){
  Serial.begin(115200);
  while( ! Serial){}
  delay(100);
  Serial.println();
  Serial.println(F( __DATE__"," __TIME__));

  pinMode(A0CylinderIsRight_pin,       INPUT_PULLUP);
  pinMode(A1CylinderIsLeft_pin,        INPUT_PULLUP);
  pinMode(A2Reset_pin,                 INPUT_PULLUP);
  pinMode(D0MoveCylinderToRight_pin,            OUTPUT);
  pinMode(LedBuiltin_MoveCylinderToLeft_pin,    OUTPUT);
}

void loop(){
  //Reset:
  if( ! digitalRead(A2Reset_pin)){ //because of INPUT_PULLUP it is inverse with the "!"
    simple_1.setForceStep(Step::S1_MoveCylinderToRightAndWait2s);
  }

//The sequenceProcess_error() must always called in loop()
  if ( ! simple_1.sequenceProcess_error()){
//Only if there is no error, it makes sense to call your sequence:
    sequenceLoopSimple();
  }
  //Print error:
  static SequenceTimingError oldSequenceTimingError = SequenceTimingError::LatestNextStepElapsed;
  SequenceTimingError sequenceTimingError = simple_1.getError();
  if (sequenceTimingError != oldSequenceTimingError){
    oldSequenceTimingError = sequenceTimingError;
    Serial.println(sequenceTimingError_char[uint32_t(sequenceTimingError)]);
  }

  //Print the actual step:
  static Step oldStep = Step::VeryLastEnum;
  Step step = simple_1.getActualStep();
  if(oldStep != step){ //If the step change, print the actual step
    oldStep = step;
    Serial.println(step_char[uint32_t(step)]);
    printStepTime(); //Additionally print the step time
  }
  //Print the pending endDelay_ms:
  static uint32_t oldPendingEndDelay = millis();
  uint32_t pendingEndDelay_ms = simple_1.getPendingEndDelay_ms();
  if(oldPendingEndDelay != pendingEndDelay_ms){
    oldPendingEndDelay = pendingEndDelay_ms;
    Serial.print(F("PendingEndDelay_ms: "));
    Serial.println(pendingEndDelay_ms);
  }
}
