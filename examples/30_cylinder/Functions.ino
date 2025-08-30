//Air pressure cylinder with end switches on both ends
//The cylinder is left - A1CylinderIsLeft_pin
//Press A2Reset_pin. This will force S1_MoveCylinderToRight   (D0MoveCylinderToRight_pin)

//The cylinder need approx 10 sec (between 5 sec and 15 sec)
//A0CylinderIsRight_pin is rached
//Stay 2 xec at this position. endDelay of S1_MoveCylinderToRight
//setNextStep S1_MoveCylinderToLeft   (LedBuiltin_MoveCylinderToLeft_pin)
//The cylinder need approx 6 sec (between 2 sec and 10 sec)
//A1CylinderIsLeft_pin is reached
//Stay 3 xec at this position
//setNextStep S1_MoveCylinderToRight   (D0MoveCylinderToRight_pin)
//Repeat: The cylinder need approx 10 s..
void sequenceLoopSimple(){
  switch (simple_1.getActualStep()){
    case Step::S0_DoNothing:
      break;
    case Step::S1_MoveCylinderToRight:
      if ( ! digitalRead(A0CylinderIsRight_pin)){ //because of INPUT_PULLUP it is inverse with the "!"
        simple_1.setNextStep(Step::S2_MoveCylinderToLeft);
      }
      break;
    case Step::S2_MoveCylinderToLeft:
      if ( ! digitalRead(A1CylinderIsLeft_pin)){
        simple_1.setNextStep(Step::S1_MoveCylinderToRight);
      }
      break;
    case Step::S3_DoNothing: //Not used
      break;
    default:
      while(true){
        Serial.println(F("Fatal Error. Wrong step"));
        delay(10000);
      }
      break;
  }

//Separate the Output from the sequence:
  digitalWrite(D0MoveCylinderToRight_pin, simple_1.getActualStep() == Step::S1_MoveCylinderToRight);
  digitalWrite(LedBuiltin_MoveCylinderToLeft_pin, simple_1.getActualStep() == Step::S2_MoveCylinderToLeft);
}

void printStepTime(){
  for(uint32_t stepNumber = 0; stepNumber < uint32_t(Step::VeryLastEnum); stepNumber++){
    Serial.print(F("Time when Step was last time active. Step "));
    Serial.print(stepNumber);
    Serial.print(F(": "));
    Serial.print(outputFromClass_stepTime_ms[stepNumber]);
    Serial.println(F("ms. "));
  }
}