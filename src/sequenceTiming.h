/*Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250803_sT_C_0_132
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.
-Credit required  -Share alike  -No warranty provided
-Free for private use.
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com. You can start immediately, you do not have to wait for a answer.
-Contact for commercial use: andreas.rosenheim@gmail.com.
 (You only have to donate to "Doctors Without Borders", or similar institution. Which should be tax-deductible)*/

#pragma once
//Important: call sequenceProcess() at every loop.

template<typename StepType>
class ClassSequenceTiming {
 private:
  //Is the active _actualStep:
  StepType _actualStep;
  StepType _nextStep;
  //start delay before a step get active. (Only use this when reasonable. Normal use is _in_endDelay_ms):
  const uint32_t *const _in_startDelay_ms;
  //The next step must be after the _in_earliestStartNextStep_ms elapsed:
  const uint32_t *const _in_earliestStartNextStep_ms;
  //The next step must be before the _latestStartNextStep elapsed.
  // 0 is to wait forever without error:
  const uint32_t *const _in_latestStartNextStep_ms; 
  //Array. After the _endDelay of the _actualStep the _startDelay of the _nextStep is waiting:
  const uint32_t *const _in_endDelay_ms;
  //Array. Complete time a step is active. Within the _startDelay from _nextStep!:
  uint32_t *const _out_stepWasActive_ms;

   //sequence-chain for one step in sequence-chain ;-) . I use the word "event" instead of "step" to have a difference.
  enum struct Event{startTimeForActiveStep, eventIsActive, endDelayAndBeginOfStartDelay, startNextStep, doNothingBecauseOfError};
  Event _event = Event::startTimeForActiveStep;

  //When the _nextStep is called to early, you get the _error_earliestStartNextStepNotElapsed:
  bool _error_earliestStartNextStepNotElapsed = false;
  //After this latestStartNextStep you get immediately the _error_latestStartNextStepReached. 0 is to switch it off:
  bool _error_latestStartNextStepReached = false;

  uint32_t _oldStartDelay_ms;
  //for _in_latestStartNextStep_ms, _in_earliestStartNextStep_ms and _out_stepWasActive_ms:
  uint32_t _oldActiveStep_ms;
  uint32_t _oldEndDelay_ms;

  //Only for debug:
  uint32_t getActualEvent();

 public:
  ClassSequenceTiming(StepType startStep,
                      const uint32_t *const in_startDelay_ms, //Pointer to array
                      const uint32_t *const in_earliestStartNextStep_ms, //Pointer to array
                      const uint32_t *const in_latestStartNextStep_ms, //Pointer to array
                      const uint32_t *const in_endDelay_ms, //Pointer to array
                      uint32_t *const       out_stepTime_ms); //Pointer to array

  //after _startDelay/_endDelay and no Error, this _nextStep will be the _actualStep:
  void set_nextStep(StepType nextStep);
  //call this in every loop:
  void sequenceProcess();
  //get the actual active step:
  StepType get_actualStep();

// - Reset Errors
// - Force _actualStep
// - No startDelay.
// - Internal Information: Force _nextStep. For this: "if (_nextStep != _actualStep &&....){""
// - Internal Information: Go to Event:startTimeForActiveStep:
  void set_forceStepImmediately(StepType forceStep);

  //get the error, when the next step was to fast:
  bool get_error_earliestStartNextStepNotElapsed();
  //get the error, when the time is elapsed. See more information in info.adoc:
  bool get_error_latestStartNextStepElapsed();
};
#include "sequenceTiming.tpp"