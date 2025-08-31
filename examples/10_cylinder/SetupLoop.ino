void setup(){
  Serial.begin(115200);
  while( ! Serial){}
  delay(100);
  Serial.println();
  Serial.println(F( __DATE__"," __TIME__));

  pinMode(A0CylinderIsRight_pin,       INPUT_PULLUP);
  pinMode(A1CylinderIsLeft_pin,        INPUT_PULLUP);
  pinMode(A2StartReset_pin,            INPUT_PULLUP);
  pinMode(D0MoveCylinderToRight_pin,          OUTPUT);
  pinMode(LedBuiltin_MoveCylinderToLeft_pin,  OUTPUT);
}

void loop(){
  //Start/Reset:
  if( ! digitalRead(A2StartReset_pin)){
    cylinder.setForceStep(Step::S1_MoveCylinderToRight);
  }

//The sequenceProcess_error() must always called in loop()
  if ( ! cylinder.sequenceProcess_error()){ //because of INPUT_PULLUP it is inverse with the "!"
//Only if there is no error, it makes sense to call your sequence:
    sequenceLoopSimple();
  }
//Print error:
  static SequenceTimingError oldSequenceTimingError = SequenceTimingError::LatestNextStepElapsed;
  SequenceTimingError sequenceTimingError = cylinder.getError();
  if (sequenceTimingError != oldSequenceTimingError){
    oldSequenceTimingError = sequenceTimingError;
    Serial.println(sequenceTimingError_char[uint32_t(sequenceTimingError)]);
  }

//Print the actual step:
  static Step oldStep = Step::VeryLastEnum;
  Step step = cylinder.getActualStep();
  if(oldStep != step){ //If the step change, print the actual step
    oldStep = step;
    Serial.print(F("Actual Step (int): "));
    Serial.println(uint32_t(step)); //to convert the type "Step" to int use uint32_t(...
  }
}
