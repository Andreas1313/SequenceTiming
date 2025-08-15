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
uint32_t inputAtClass_startDelay_ms[]            ={    0,    0,    0,    0};
uint32_t inputAtClass_earliestStartNextStep_ms[] ={    0,    0,    0,    0};
uint32_t inputAtClass_latestStartNextStep_ms[]   ={    0,    0,    0,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelay_ms[]              ={    0, 2000, 2000,    0};
uint32_t outputFromClass_stepTime_ms[]           ={    0,    0,    0,    0};
//The <Step> is where you give the structure of your enum class to the ClassSequenceTiming: 
ClassSequenceTiming<Step> simple_1(Step::S0_DoNothing,  //Very first Step to start. In this example it jumps to S1_Output_D0 at setup()
                            inputAtClass_startDelay_ms,
                            inputAtClass_earliestStartNextStep_ms,
                            inputAtClass_latestStartNextStep_ms,
                            inputAtClass_endDelay_ms,
                            outputFromClass_stepTime_ms);

//output pins:
const pin_size_t D0_pin  {0};
const pin_size_t LED_BUILTIN_pin  {LED_BUILTIN};
