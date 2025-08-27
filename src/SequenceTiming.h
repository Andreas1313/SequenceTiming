/*Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250815_sT_C_0_132
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.
-Credit required  -Share alike  -No warranty provided
-Free for private use.
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com. You can directly start. You do not have to wait for an answer.
-Contact for commercial use: andreas.rosenheim@gmail.com.(You only have to donate to "Doctors Without Borders",
 or similar institution. Which should be tax-deductible)*/

#pragma once
//Important: call sequenceProcess() at every loop.

template<typename StepType>
class ClassSequenceTiming {
 private:
  //Is the active _actualStep:
  StepType _actualStep;
  StepType _nextStep;
  //The next step must be after the _in_earliestStartNextStep_ms elapsed:
  const uint32_t *const _in_earliestStartNextStep_ms;
  //The next step must be before the _latestStartNextStep elapsed.
  // 0 is to wait forever without error:
  const uint32_t *const _in_latestStartNextStep_ms; 
  //Array. For the time of _endDelay the _actualStep is active and the _nextStep is waiting:
  const uint32_t *const _in_endDelay_ms;
  //Array. Complete time a step is active. Within the _endDelay:
  uint32_t *const _out_stepWasActive_ms;

   //sequence-chain for one step in sequence-chain ;-) . I use the word "event" instead of "step" to have a difference.
  enum struct Event{StartTimeForActiveStep, EventIsActive, EndDelay, DoNothingBecauseOfError};
  Event _event = Event::StartTimeForActiveStep;

  //When the _nextStep is called to early, you get the _error_earliestStartNextStepNotElapsed:
  bool _error_earliestStartNextStepNotElapsed = false;
  //After this latestStartNextStep you get immediately the _error_latestStartNextStepReached. 0 is to switch it off:
  bool _error_latestStartNextStepReached = false;

  //for _in_latestStartNextStep_ms, _in_earliestStartNextStep_ms and _out_stepWasActive_ms:
  uint32_t _oldActiveStep_ms;
  uint32_t _oldEndDelay_ms;

  //Only for debug:
  uint32_t getActualEvent();

 public:
  ClassSequenceTiming(StepType startStep,
                      const uint32_t *const in_earliestStartNextStep_ms, //Pointer to array
                      const uint32_t *const in_latestStartNextStep_ms, //Pointer to array
                      const uint32_t *const in_endDelay_ms, //Pointer to array
                      uint32_t *const       out_stepTime_ms); //Pointer to array

  //after _endDelay and no Error, this _nextStep will be the _actualStep:
  void set_nextStep(StepType nextStep);
  //call this in every loop:
  void sequenceProcess();
  //get the actual active step:
  StepType get_actualStep();

// - Reset Errors
// - Force _actualStep
// - Internal Information: Force _nextStep. For this: "if (_nextStep != _actualStep &&....){""
// - Internal Information: Go to Event:StartTimeForActiveStep:
  void set_forceStepImmediately(StepType forceStep);

  //get the error, when the next step was to fast:
  bool get_error_earliestStartNextStepNotElapsed();
  //get the error, when the time is elapsed. See more information in info.adoc:
  bool get_error_latestStartNextStepElapsed();
};
#include "SequenceTiming.tpp"