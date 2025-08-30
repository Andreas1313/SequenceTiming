#include <SequenceTiming.h>

enum class Step{
  S0_DoNothing,
//Jump to this to start:
  S1_MoveCylinderToRight,
  S2_MoveCylinderToLeft,
//Not used at the moment:
  S3_DoNothing,
  VeryLastEnum
};
                                                  // S0_,  S1_,  S2_,  S3_
uint32_t inputAtClass_earliestStartNextStep_ms[] ={    0, 5000, 2000,    0};
uint32_t inputAtClass_latestStartNextStep_ms[]   ={    0,15000,10000,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelay_ms[]              ={    0, 2000, 3000,    0};
uint32_t outputFromClass_stepTime_ms[]           ={    0,    0,    0,    0};
//The <Step> is where you give the structure of your enum class to the ClassSequenceTiming: 
ClassSequenceTiming<Step> simple_1(Step::S0_DoNothing,  //Very first Step to start. In this example it jumps to S1_MoveCylinderToRight at setup()
                            inputAtClass_earliestStartNextStep_ms,
                            inputAtClass_latestStartNextStep_ms,
                            inputAtClass_endDelay_ms,
                            outputFromClass_stepTime_ms);

const char sequenceTimingError_char[][50] = {
  "SequenceTimingError::NoError",
  "SequenceTimingError::EarliestNextStepNotElapsed",
  "SequenceTimingError::LatestNextStepElapsed"
};

//input pins:
const uint8_t A0CylinderIsRight_pin{A0};
const uint8_t A1CylinderIsLeft_pin {A1};
const uint8_t A2Reset_pin          {A2};

//output pins:
const uint8_t D0MoveCylinderToRight_pin         {0};
const uint8_t LedBuiltin_MoveCylinderToLeft_pin {LED_BUILTIN};