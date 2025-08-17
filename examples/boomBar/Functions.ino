//To run, do not wait to long between the steps:
//A0 to GND. Step 1
//A0 Remove GND. Step 2
//A1 to GND. Step 3
//A2 to GND. Step 4
//A3 to GND. Step 5
//A4 to GND. Step 6
//A5 to GND. Step 7
//Wait 5 sec, until Step8 is active
//A6 to GND. Step 9
//A1 to GND. Step 3
//A2 to GND. Step 4
//..
//To reset: A0 to GND

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
    case GateStep::S2_SlowDownReference:
      if ( ! digitalRead(downSwitch_pin)){
        gate_1.set_nextStep(GateStep::S3_WaitDown);
      }
      break;
    case GateStep::S3_WaitDown:
      if ( ! digitalRead(requestSwitch_pin)){
        gate_1.set_nextStep(GateStep::S4_FastUp);
      }
      break;
    case GateStep::S4_FastUp:
      if ( ! digitalRead(nearlyUpSwitch_pin)){
        gate_1.set_nextStep(GateStep::S5_SlowUp);
      }
      break;
    case GateStep::S5_SlowUp:
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
    case GateStep::S8_FastDown:
      if ( ! digitalRead(nearlyDown_pin)){
        gate_1.set_nextStep(GateStep::S9_SlowDown);
      }
      break;
    case GateStep::S9_SlowDown:
      if ( ! digitalRead(downSwitch_pin)){
        gate_1.set_nextStep(GateStep::S3_WaitDown);
      }
      break;
    case GateStep::S10_DoNothing: //Not used
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

  bool blinkYellowLight = 
      gate_1.get_actualStep() == GateStep::S7_StartBlinkForClosingAndDelay ||
      gate_1.get_actualStep() == GateStep::S8_FastDown ||
      gate_1.get_actualStep() == GateStep::S9_SlowDown;
  if (blinkYellowLight){
    digitalWrite(blinkYellow_pin, signalLight.get_actualStep() == BlinkLight::S1_On);
  } else {
    digitalWrite(blinkYellow_pin, LOW);
  }
  if (gate_1.get_error_latestStartNextStepElapsed() || gate_1.get_error_earliestStartNextStepNotElapsed()){
    digitalWrite(blinkError_pin, signalLight.get_actualStep() == BlinkLight::S1_On);
  } else {
    digitalWrite(blinkError_pin, LOW);
  }
}

//This sequence run all the time. Use this that all blinking lights blink simultaneous
void sequenceLoopSignalLight(){
  signalLight.sequenceProcess();

  switch (signalLight.get_actualStep()){
    case BlinkLight::S0_DoNothing:
      signalLight.set_nextStep(BlinkLight::S2_Off);
      break;
    case (BlinkLight::S2_Off): //Only to show that the order is not important. S2 is before S1
      signalLight.set_nextStep(BlinkLight::S1_On);
      break;
    case BlinkLight::S1_On:
      signalLight.set_nextStep(BlinkLight::S2_Off);
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
}