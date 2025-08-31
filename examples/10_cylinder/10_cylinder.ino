#include <SequenceTiming.h>

enum class Step{
  S0_DoNothing,
//Jump to this to start:
  S1_MoveCylinderToRight,//The cylinder needs approx 10 sec to move from Left to right. (5 to 15 sec)
  S2_MoveCylinderToLeft, //The cylinder needs approx  6 sec to move from right to left. (2 to 10 sec)
//Not used at the moment:
  S3_DoNothing,
//This is not used at my library, but my suggestion is to put it in for your future use:
  VeryLastEnum
};
                                                  // S0_,  S1_,  S2_,  S3_
uint32_t inputAtClass_earliestStartNextStep_ms[] ={    0, 5000, 2000,    0};
uint32_t inputAtClass_latestStartNextStep_ms[]   ={    0,15000,10000,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelay_ms[]              ={    0,    0,    0,    0};
uint32_t outputFromClass_stepTime_ms[]           ={    0,    0,    0,    0};
//The <Step> is where you give the structure of your enum class to the ClassSequenceTiming: 
ClassSequenceTiming<Step> cylinder(Step::S0_DoNothing,  //Very first Step. To start in this example start/reset with A2 to S1_MoveCylinderToRight.
                            inputAtClass_earliestStartNextStep_ms,
                            inputAtClass_latestStartNextStep_ms,
                            inputAtClass_endDelay_ms,
                            outputFromClass_stepTime_ms);

//Only necessary to print an error at serial monitor:
const char sequenceTimingError_char[][50] = {
  "SequenceTimingError::NoError",
  "SequenceTimingError::EarliestNextStepNotElapsed",
  "SequenceTimingError::LatestNextStepElapsed"
};

//input pins:
const uint8_t A0CylinderIsRight_pin{A0};
const uint8_t A1CylinderIsLeft_pin {A1};
const uint8_t A2StartReset_pin     {A2};

//output pins:
const uint8_t D0MoveCylinderToRight_pin         {0};
const uint8_t LedBuiltin_MoveCylinderToLeft_pin {LED_BUILTIN};