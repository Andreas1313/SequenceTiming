//If Step S1_Output_D0 is one time active (in setup()), it change every 2000ms between step S2_Output_LED_BUILTIN and step S1_Output_D0
void sequenceLoopSimple(){
  switch (simple_1.get_actualStep()){
    case Step::S0_DoNothing:
      break;
    case Step::S1_Output_D0:
      simple_1.set_nextStep(Step::S2_Output_LED_BUILTIN);
      break;
    case Step::S2_Output_LED_BUILTIN:
      simple_1.set_nextStep(Step::S1_Output_D0);
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