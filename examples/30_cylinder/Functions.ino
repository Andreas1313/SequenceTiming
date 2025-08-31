/*This is exactly the same function as 20_cylinder. It only has the waiting time at the previous steps
**For test:**
- Press A2(to GND) for start/reset

- After approx 10 sec press A0(to GND)
- After 2 sec it switch automatically from step 1 to step 2
- After approx 6 sec press A1(to GND)
- After 3 sec it switch automatically from step 2 to step 1
- Repeat. After approx 10 s..
If you are to fast or to slow, you get an error


**This example is for:**
Air pressure cylinder with end switches on both ends. (A0CylinderIsRight_pin, A1CylinderIsLeft_pin)
The cylinder needs approx 10 sec to move from left to right.
The cylinder needs approx 6 sec to move from right to left.
The cylinder waits 2 sec right and 3 sec left before moving to the other side

Process:
Start condition: The cylinder is left
- S0_.. Press A2StartReset_pin. This will force 
- S1_MoveCylinderToRight   (D0MoveCylinderToRight_pin)

- S1_.. The cylinder need approx 10 sec (between 5 sec and 15 sec)
- S1_.. A0CylinderIsRight_pin is reached
- S1_Wait2s (Trigger from S2 was there, but wait)
- S2_MoveCylinderToLeft   (LedBuiltin_MoveCylinderToLeft_pin)
- S2_.. The cylinder need approx 6 sec (between 2 sec and 10 sec)
- S2_.. A1CylinderIsLeft_pin is reached
- S2_Wait3s (Trigger from S1 was there, but wait)
- S1_MoveCylinderToRight   (D0MoveCylinderToRight_pin)
- Repeat: S1_.. The cylinder need approx 10 s.. */

void sequenceLoopSimple(){
  switch (simple_1.getActualStep()){
    case Step::S0_DoNothing:
      break;
    case Step::S1_MoveCylinderToRightAndWait2s:
      if ( ! digitalRead(A0CylinderIsRight_pin)){ //because of INPUT_PULLUP it is inverse with the "!"
        simple_1.setNextStep(Step::S2_MoveCylinderToLeftAndWait3s);
      }
      break;
    case Step::S2_MoveCylinderToLeftAndWait3s:
      if ( ! digitalRead(A1CylinderIsLeft_pin)){
        simple_1.setNextStep(Step::S1_MoveCylinderToRightAndWait2s);
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
  digitalWrite(D0MoveCylinderToRight_pin, simple_1.getActualStep() == Step::S1_MoveCylinderToRightAndWait2s);
  digitalWrite(LedBuiltin_MoveCylinderToLeft_pin, simple_1.getActualStep() == Step::S2_MoveCylinderToLeftAndWait3s);
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