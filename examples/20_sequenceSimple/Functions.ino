//You have to set A0_pin to GND and wait 2000ms to activate the step S2_Output_LED_BUILTIN.
//You have to set A1_pin to GND and wait 2000ms to activate S1_Output_D0
void sequenceLoopSimple(){
  switch (simple_1.get_actualStep()){
    case Step::S0_DoNothing:
      break;
    case Step::S1_Output_D0:
      if ( ! digitalRead(A0_pin)){ //because of INPUT_PULLUP it is inverse with the "!"
        simple_1.set_nextStep(Step::S2_Output_LED_BUILTIN);
      }
      break;
    case Step::S2_Output_LED_BUILTIN:
      if ( ! digitalRead(A1_pin)){
        simple_1.set_nextStep(Step::S1_Output_D0);
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
  digitalWrite(D0_pin, simple_1.get_actualStep() == Step::S1_Output_D0);
  digitalWrite(LED_BUILTIN_pin, simple_1.get_actualStep() == Step::S2_Output_LED_BUILTIN);
}