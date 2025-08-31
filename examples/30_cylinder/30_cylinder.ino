#include <SequenceTiming.h>

enum class Step{
  S0_DoNothing,
//Jump to this to start:
  S1_MoveCylinderToRightAndWait2s,
  S2_MoveCylinderToLeftAndWait3s,
//Not used at the moment:
  S3_DoNothing,
//This is not used at the library, but my suggestion is to put it in for your future use. Example for-loop:
  VeryLastEnum
};
                                                  // S0_,  S1_,  S2_,  S3_
uint32_t inputAtClass_earliestStartNextStep_ms[] ={    0, 5000, 2000,    0};
uint32_t inputAtClass_latestStartNextStep_ms[]   ={    0,15000,10000,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelay_ms[]              ={    0, 2000, 3000,    0};
uint32_t outputFromClass_stepTime_ms[]           ={    0,    0,    0,    0};
//The <Step> is where you give the structure of your enum class to the ClassSequenceTiming: 
ClassSequenceTiming<Step> simple_1(Step::S0_DoNothing,  //Very first Step to start. In this example reset to S1_MoveCylinderToRightAndWait2s.
                            inputAtClass_earliestStartNextStep_ms,
                            inputAtClass_latestStartNextStep_ms,
                            inputAtClass_endDelay_ms,
                            outputFromClass_stepTime_ms);

const char sequenceTimingError_char[][50] = {
  "SequenceTimingError::NoError",
  "SequenceTimingError::EarliestNextStepNotElapsed",
  "SequenceTimingError::LatestNextStepElapsed"
};
const char step_char[][50] = {
  "Step::S0_DoNothing",
  "Step::S1_MoveCylinderToRightAndWait2s",
  "Step::S2_MoveCylinderToLeftAndWait3s",
  "Step::S3_DoNothing"
};

//input pins:
const uint8_t A0CylinderIsRight_pin{A0};
const uint8_t A1CylinderIsLeft_pin {A1};
const uint8_t A2Reset_pin          {A2};

//output pins:
const uint8_t D0MoveCylinderToRight_pin         {0};
const uint8_t LedBuiltin_MoveCylinderToLeft_pin {LED_BUILTIN};