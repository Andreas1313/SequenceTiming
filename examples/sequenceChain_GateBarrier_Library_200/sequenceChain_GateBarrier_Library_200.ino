#include "sequenceTiming.h"

enum class GateStep : uint32_t {
  S0_DoNothing,
//Jump to this to start the reference drive. When the bar is down already, skip the S2_SlowDownReference
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
ClassSequenceTiming<GateStep> gate_1(GateStep::S0_DoNothing);
                                     // S0_,  S1_,  S2_,  S3_,  S4_,  S5_,  S6_,  S7_,  S8_,  S9_, S10_
uint32_t startDelay_ms[]            ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};
uint32_t earliestStartNextStep_ms[] ={    2,    0,    2,    2,    2,    2,    2,    0,    2,    2,    2};
uint32_t latestStartNextStep_ms[]   ={    0,    0,30000,    0,10000, 4000,    0,    0,10000, 4000,    0}; // 0 is to switch it off
uint32_t endDelay_ms[]              ={    0,    0,    0,    0,    0,    0,    0, 5000,    0,    0,    0};


enum class BlinkLight : uint32_t {
  S0_DoNothing,
//Jump to this to start:
  S1_On,
  S2_Off,
//Not used:
  S3_DoNothing,
  VeryLastEnum
};
ClassSequenceTiming<BlinkLight> yellowLight(BlinkLight::S0_DoNothing);
ClassSequenceTiming<BlinkLight> errorLight(BlinkLight::S0_DoNothing);
                                     // S0_,  S1_,  S2_,  S3_
uint32_t endDelaySignalLight_ms[] =  {    0,  500,  500,    0};

//input pins:
const pin_size_t resetAndStartButton_pin  {A0};
const pin_size_t downSwitch_pin           {A1};
const pin_size_t requestSwitch_pin        {A2};
const pin_size_t nearlyUpSwitch_pin       {A3};
const pin_size_t upSwitch_pin             {A4};
const pin_size_t lightBarrier_pin         {A5};
const pin_size_t nearlyDown_pin           {A6};

//output pins:
const pin_size_t moveSlowDown_pin {0};
const pin_size_t moveUp_pin       {1};
const pin_size_t moveSlowUp_pin   {2};
const pin_size_t moveDown_pin     {3};
const pin_size_t blinkYellow_pin  {LED_BUILTIN};
const pin_size_t blinkError_pin   {4};

bool global_blinkYellowLight = false;