#include <SequenceTiming.h>

enum class GateStep{
  S0_DoNothing,
//Jump to this to start the reference drive. When the bar is down already, skip tc:\Users\andre\Desktop\Andi\2025\109_TortoiseGit\101_SequenceTiming\SequenceTiming\examples\40_boomBar\src\SequenceTiming.hhe S2_SlowDownReference
  S1_StartReference,
//At the very first reference, the speed must be slow:
  S2_SlowDownReference,
//Wait until the customer press the open button:
  S3_WaitDown,
  S4_FastUp,
//When the nearlyUpSwitch is reached, move softly to end position:
  S5_SlowUp,
//Wait until the customer passed the gate:
  S6_WaitUp,
//
  S7_StartBlinkForClosingAndDelay,
  S8_FastDown,
//When the nearlyDownSwitch is reached, close the gate softly:
  S9_SlowDown,
//Not used at the moment. When you have an error, you can jump to this to doNothing.
  S10_DoNothing,
  VeryLastEnum
};
                                                  // S0_,  S1_,  S2_,  S3_,  S4_,  S5_,  S6_,  S7_,  S8_,  S9_, S10_
uint32_t inputAtClass_earliestStartNextStep_ms[] ={    2,    0,    2,    2,    2,    2,    2,    0,    2,    2,    2};
uint32_t inputAtClass_latestStartNextStep_ms[]   ={    0,    0,30000,    0,10000, 4000,    0,    0,10000, 4000,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelay_ms[]              ={    0,  200,    0,    0,    0,    0,    0, 5000,    0,    0,    0};
uint32_t outputFromClass_stepTime_ms[]           ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};
ClassSequenceTiming<GateStep> gate_1(GateStep::S0_DoNothing,
                            inputAtClass_earliestStartNextStep_ms,
                            inputAtClass_latestStartNextStep_ms,
                            inputAtClass_endDelay_ms,
                            outputFromClass_stepTime_ms);


enum class BlinkLight{
  S0_DoNothing,
//Jump to this to start:
  S1_On,
  S2_Off,
//Not used:
  S3_DoNothing,
  VeryLastEnum
};
                                                             // S0_,  S1_,  S2_,  S3_
uint32_t inputAtClass_earliestStartNextStepSignalLight_ms[] ={    0,    0,    0,    0};
uint32_t inputAtClass_latestStartNextStepSignalLight_ms[]   ={    0,    0,    0,    0}; // 0 is to wait forever without error
uint32_t inputAtClass_endDelaySignalLight_ms[]              ={    0,  500,  500,    0};
uint32_t outputFromClass_stepTimeSignalLight_ms[]           ={    0,    0,    0,    0};
ClassSequenceTiming<BlinkLight> signalLight(BlinkLight::S0_DoNothing,
                            inputAtClass_earliestStartNextStepSignalLight_ms,
                            inputAtClass_latestStartNextStepSignalLight_ms,
                            inputAtClass_endDelaySignalLight_ms,
                            outputFromClass_stepTimeSignalLight_ms);

//input pins:
const uint8_t resetAndStartButton_pin  {A0};
const uint8_t downSwitch_pin           {A1};
const uint8_t requestSwitch_pin        {A2};
const uint8_t nearlyUpSwitch_pin       {A3};
const uint8_t upSwitch_pin             {A4};
const uint8_t lightBarrier_pin         {A5};
const uint8_t nearlyDown_pin           {A6};

//output pins:
const uint8_t moveSlowDown_pin {0};
const uint8_t moveUp_pin       {1};
const uint8_t moveSlowUp_pin   {2};
const uint8_t moveDown_pin     {3};
const uint8_t blinkYellow_pin  {LED_BUILTIN};
const uint8_t blinkError_pin   {4};
