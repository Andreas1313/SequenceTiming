/*Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250815_sT_C_0_132
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.
-Credit required  -Share alike  -No warranty provided
-Free for private use.
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com. You can directly start. You do not have to wait for an answer.
-Contact for commercial use: andreas.rosenheim@gmail.com.(You only have to donate to "Doctors Without Borders",
 or similar institution. Which should be tax-deductible)*/

#pragma once
//Important: call sequenceProcess() at every loop.

//global:
enum class SequenceTimingError{
  NoError,
  EarliestNextStepNotElapsed, //When the next step was to fast
  LatestNextStepElapsed       //When the time is elapsed
};

template<typename StepType>
class ClassSequenceTiming {
 private:
  //Is the active _actualStep:
  StepType _actualStep;
  StepType _nextStep;
  //The next step must be after the _in_earliestNextStep_ms elapsed:
  const uint32_t *const _in_earliestNextStep_ms;
  //The next step must be before the _latestNextStep elapsed.
  // 0 is to wait forever without error:
  const uint32_t *const _in_latestNextStep_ms; 
  //Array. For the time of _endDelay the _actualStep is active and the _nextStep is waiting:
  const uint32_t *const _in_endDelay_ms;
  //Array. Complete time a step is active. Within the _endDelay:
  uint32_t *const _out_stepWasActive_ms;

   //sequence-chain for one step in sequence-chain ;-) . I use the word "event" instead of "step" to have a difference.
  enum class Event{StartTimeForActiveStep, EventIsActive, EndDelay, DoNothingBecauseOfError};
  Event _event = Event::StartTimeForActiveStep;

  SequenceTimingError sequenceTimingError = SequenceTimingError::NoError;

  //for _in_latestNextStep_ms, _in_earliestNextStep_ms and _out_stepWasActive_ms:
  uint32_t _oldActiveStep_ms;
  uint32_t _oldEndDelay_ms;

  uint32_t _deltaEndDelay_ms;

  //Only for debug:
  uint32_t getActualEvent();

 public:
  ClassSequenceTiming(StepType startStep,
                      const uint32_t *const in_earliestNextStep_ms, //Pointer to array
                      const uint32_t *const in_latestNextStep_ms, //Pointer to array
                      const uint32_t *const in_endDelay_ms, //Pointer to array
                      uint32_t *const       out_stepTime_ms); //Pointer to array

  //after _endDelay and no Error, this _nextStep will be the _actualStep:
  void setNextStep(StepType nextStep);
  //call this in every loop:
  bool sequenceProcess_error();
  //get the actual active step:
  StepType getActualStep();

// - Reset Errors
// - Force _actualStep
// - Internal Information: Go to Event:StartTimeForActiveStep:
  void setForceStep(StepType forceStep);
//Rest of the endDelay:
  uint32_t getPendingEndDelay_ms();
//See global enum class SequenceTimingError:
  SequenceTimingError getError();
};
#include "SequenceTiming.tpp"