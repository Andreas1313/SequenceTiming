/*For test:
- Press A2(to GND) for start/reset

- After approx 10 sec press A0(to GND)
- After approx 6 sec press A1(to GND)
- Repeat. After approx 10 sec press A0(to GND)....
If you are to fast or to slow, you get an error

This example is for:
Air pressure cylinder with end switches on both ends. (A0CylinderIsRight_pin, A1CylinderIsLeft_pin)
The cylinder needs approx 10 sec to move from Left to right.
The cylinder needs approx 6 sec to move from right to left.

Process:
Start condition: The cylinder is left
- S0_ Press A2StartReset_pin. This will force
- S1_MoveCylinderToRight   (D0MoveCylinderToRight_pin)

- S1_.. The cylinder need approx 10 sec (between 5 sec and 15 sec)
- S1_.. A0CylinderIsRight_pin is reached
- S2_MoveCylinderToLeft   (LedBuiltin_MoveCylinderToLeft_pin)
- S2_.. The cylinder need approx 6 sec (between 2 sec and 10 sec)
- S2_.. A1CylinderIsLeft_pin is reached
- S1_MoveCylinderToRight   (D0MoveCylinderToRight_pin)
- Repeat: S1_.. The cylinder need approx 10 s.. */

void sequenceLoopSimple(){
  switch (cylinder.getActualStep()){
    case Step::S0_DoNothing:
      break;
    case Step::S1_MoveCylinderToRight:
      if ( ! digitalRead(A0CylinderIsRight_pin)){ //because of INPUT_PULLUP it is inverse with the "!"
        cylinder.setNextStep(Step::S2_MoveCylinderToLeft);
      }
      break;
    case Step::S2_MoveCylinderToLeft:
      if ( ! digitalRead(A1CylinderIsLeft_pin)){
        cylinder.setNextStep(Step::S1_MoveCylinderToRight);
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
  digitalWrite(D0MoveCylinderToRight_pin, cylinder.getActualStep() == Step::S1_MoveCylinderToRight);
  digitalWrite(LedBuiltin_MoveCylinderToLeft_pin, cylinder.getActualStep() == Step::S2_MoveCylinderToLeft);
}