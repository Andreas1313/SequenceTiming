void sequenceLoopGateBarrier(){

  gate_1.sequenceProcess();

  switch (gate_1.get_actualStep()){
    case GateStep::S0_DoNothing:
      break;
    case GateStep::S1_StartReference:
      if ( ! digitalRead(downSwitch_pin)){
        gate_1.set_nextStep(GateStep::S3_WaitDown);
      } else {
        gate_1.set_nextStep(GateStep::S2_SlowDownReference);
      }
      break;
    case (GateStep::S2_SlowDownReference):
      if ( ! digitalRead(downSwitch_pin)){
        gate_1.set_nextStep(GateStep::S3_WaitDown);
      }
      break;
    case (GateStep::S3_WaitDown):
      if ( ! digitalRead(requestSwitch_pin)){
        gate_1.set_nextStep(GateStep::S4_FastUp);
      }
      break;
    case (GateStep::S4_FastUp):
      if ( ! digitalRead(nearlyUpSwitch_pin)){
        gate_1.set_nextStep(GateStep::S5_SlowUp);
      }
      break;
    case (GateStep::S5_SlowUp):
      if ( ! digitalRead(upSwitch_pin)){
        gate_1.set_nextStep(GateStep::S6_WaitUp);
      }
      break;
    case GateStep::S6_WaitUp:
      if ( ! digitalRead(lightBarrier_pin)){
        gate_1.set_nextStep(GateStep::S7_StartBlinkForClosingAndDelay);
      }
      break;
    case GateStep::S7_StartBlinkForClosingAndDelay:
      gate_1.set_nextStep(GateStep::S8_FastDown);
      // The endDelay is included
      break;
    case (GateStep::S8_FastDown):
      if ( ! digitalRead(nearlyDown_pin)){
        gate_1.set_nextStep(GateStep::S9_SlowDown);
      }
      break;
    case (GateStep::S9_SlowDown):
      if ( ! digitalRead(downSwitch_pin)){
        gate_1.set_nextStep(GateStep::S3_WaitDown);
      }
      break;
    case (GateStep::S10_DoNothing): //Not used
      break;
    default:
      while(true){
        Serial.println(F("Fatal Error. Wrong step"));
        delay(10000);
      }
      break;
  }

  
  
  digitalWrite(moveSlowDown_pin,
                gate_1.get_actualStep() == GateStep::S2_SlowDownReference ||
                gate_1.get_actualStep() == GateStep::S9_SlowDown
              );
  digitalWrite(moveUp_pin, gate_1.get_actualStep() == GateStep::S4_FastUp);
  digitalWrite(moveSlowUp_pin, gate_1.get_actualStep() == GateStep::S5_SlowUp);
  digitalWrite(moveDown_pin, gate_1.get_actualStep() == GateStep::S8_FastDown);

  global_blinkYellowLight = 
      gate_1.get_actualStep() == GateStep::S7_StartBlinkForClosingAndDelay ||
      gate_1.get_actualStep() == GateStep::S8_FastDown ||
      gate_1.get_actualStep() == GateStep::S9_SlowDown;
}

//The global_blinkYellowLight variable is used:
void sequenceLoopYellowLight(){

  yellowLight.sequenceProcess();

  switch (yellowLight.get_actualStep()){
    case BlinkLight::S0_DoNothing:
      yellowLight.set_nextStep(BlinkLight::S2_Off);
      break;
    case (BlinkLight::S2_Off): //Only to show that the order is not important. S2 is before S1
      if (global_blinkYellowLight){
        yellowLight.set_nextStep(BlinkLight::S1_On);
      }
      break;
    case BlinkLight::S1_On:
      yellowLight.set_nextStep(BlinkLight::S2_Off);
      break;
    case (BlinkLight::S3_DoNothing):
      break;
    default:
      while(true){
        Serial.println(F("Fatal Error. Wrong step"));
        delay(10000);
      }
      break;
  }

  digitalWrite(blinkYellow_pin, yellowLight.get_actualStep() == BlinkLight::S1_On);
}

void sequenceLoopErrorLight(){

  errorLight.sequenceProcess();

  switch (errorLight.get_actualStep()){
    case BlinkLight::S0_DoNothing:
      errorLight.set_nextStep(BlinkLight::S2_Off);
      break;
    case (BlinkLight::S2_Off): //Only to show that the order is not important. S2 is before S1
      if (gate_1.get_error_latestStartNextStepElapsed() || gate_1.get_error_earliestStartNextStepNotElapsed()){
        errorLight.set_nextStep(BlinkLight::S1_On);
      }
      break;
    case BlinkLight::S1_On:
      errorLight.set_nextStep(BlinkLight::S2_Off);
      break;
    case (BlinkLight::S3_DoNothing):
      break;
    default:
      while(true){
        Serial.println(F("Fatal Error. Wrong step"));
        delay(10000);
      }
      break;
  }

  digitalWrite(blinkError_pin, errorLight.get_actualStep() == BlinkLight::S1_On);
}