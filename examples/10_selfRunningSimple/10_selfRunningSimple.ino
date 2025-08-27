#include <SequenceTiming.h>

enum class Step{
  S0_DoNothing,
//Jump to this to start:
  S1_Output_D0,
  S2_Output_LED_BUILTIN,
//Not used at the moment:
  S3_DoNothing,
  VeryLastEnum
};
                                                  // S0_,  S1_,  S2_,  S3_
uint32_t inputAtClass_earliestStartNextStep_ms[] ={    0,    0,    0,    0};
uint32_t inputAtClass_latestStartNextStep_ms[]   ={    0,    0,    0,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelay_ms[]              ={    0, 2000, 2000,    0};
uint32_t outputFromClass_stepTime_ms[]           ={    0,    0,    0,    0};
//The <Step> is where you give the structure of your enum class to the ClassSequenceTiming: 
ClassSequenceTiming<Step> simple_1(Step::S0_DoNothing,  //S0_DoNothing is the very first Step to start. In this example it jumps to S1_Output_D0 at setup()
                            inputAtClass_earliestStartNextStep_ms,
                            inputAtClass_latestStartNextStep_ms,
                            inputAtClass_endDelay_ms,
                            outputFromClass_stepTime_ms);

//output pins:
const uint8_t D0_pin           {0};
const uint8_t LED_BUILTIN_pin  {LED_BUILTIN};


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

//Serial Monitor must be open.
void setup(){
  Serial.begin(115200);
  while( ! Serial){}
  delay(100);
  Serial.println();
  Serial.println(F( __DATE__"," __TIME__));

  pinMode(D0_pin,             OUTPUT);
  pinMode(LED_BUILTIN_pin,    OUTPUT);


  //The S0_DoNothing is active from the constructor of the class. But to start, we have to set it to step 1 (S1_Output_D0):
  simple_1.set_nextStep(Step::S1_Output_D0);  
}

void loop(){
   //This two calls are all you need in loop():
  simple_1.sequenceProcess(); 
  sequenceLoopSimple();

//This is only for Serial print:
  static Step oldStep = Step::VeryLastEnum;
  if(oldStep != simple_1.get_actualStep()){ //If the step change, print the actual step
    oldStep = simple_1.get_actualStep();
    Serial.print(F("Actual Step (int): "));
    Serial.println(uint32_t(simple_1.get_actualStep())); //to convert the type "Step" to int use uint32_t(...
  }
}