/*Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250803_sT_C_0_132
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.
-Credit required  -Share alike  -No warranty provided
-Free for private use.
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com.
-Contact for commercial use: andreas.rosenheim@gmail.com.(You only have to donate to "Doctors Without Borders",
 or similar institution. Which should be tax-deductible)*/

#pragma once
//Important: call sequenceProcess() at every loop.

//Instance example: ClassSequenceTiming<StepBoom> boom_1(StepBoom::Nothing, numberOfStepsForBoom);
//The <StepBoom> gives the structure of the "enum class(struct)"" to this class
template<typename StepType>
class ClassSequenceTiming {
 private:
  //Is the active _actualStep:
  StepType _actualStep;
  StepType _nextStep;
  //number of steps, this comes from the constructor:
  const uint32_t _numberOfSteps;
  //start delay before a step get active. (Onlly use this when reasonable):
  uint32_t * _startDelay_ms;
  //The next step must be before the _earliestStartNextStep_ms:
  uint32_t * _earliestStartNextStep_ms;
  //The next step must be after the  _latestStartNextStep elapsed:
  uint32_t * _latestStartNextStep_ms; 
  //Array. After the _endDelay of the _actualStep the _startDelay of the _nextStep is waiting:
  uint32_t * _endDelay_ms;
  //Array. Complete time a step is active. Within the _startDelay from _nextStep!:
  uint32_t * _stepWasActive_ms;

   //sequence-chain for one step in sequence-chain ;-) . I use the word "event" instead of "step" to have a difference.
  enum struct Event{startTimeForActiveStep, eventIsActive, endDelayAndBeginOfStartDelay, startNextStep, doNothingBecauseOfError};
  Event _event = Event::startTimeForActiveStep;

  //Array. When the _nextStep is called to early, you get the _error_earliestStartNextStepNotElapsed:
  bool _error_earliestStartNextStepNotElapsed = false;
  //Array. After this latestStartNextStep you get immediately the _error_latestStartNextStepReached. 0 is to switch it off:
  bool _error_latestStartNextStepReached = false;

  uint32_t _oldStartDelay_ms;
  //for _latestStartNextStep_ms, _earliestStartNextStep_ms and _stepWasActive_ms:
  uint32_t _oldActiveStep_ms;
  uint32_t _oldEndDelay_ms;

 public:
  //constructor. startStep: Step where to start.
  //numberOfSteps: Is necessary. It is not possible to get it from enum.
  //Instance example: ClassSequenceTiming<StepBoom> boom_1(StepBoom::Nothing, numberOfStepsForBoom);
  //The <StepBoom> gives the structure of the "enum class(struct)"" to this class
  ClassSequenceTiming(StepType startStep);

  //after _startDelay/_endDelay and no Error, this _nextStep will be the _actualStep:
  void set_nextStep(StepType nextStep);
  void set_nextStep(uint32_t nextStep_int);
  //call this in every loop:
  void sequenceProcess();
  //get the actual active step:
  StepType get_actualStep();
  //get the actual active step as uint32_t:
  uint32_t get_actualStep_int();

// - Reset Errors
// - Force _actualStep
// - Internal Information: Force _nextStep. For this: "if (_nextStep != _actualStep &&....){""
// - Internal Information: Go to Event:startTimeForActiveStep.
// - No startDelay:
  void set_forceStepImmediately(StepType forceStep);
  void set_forceStepImmediately(uint32_t forceStep_int);

  //get the number of the steps:
  uint32_t get_numberOfSteps();

  //set the _startDelay of one step:
  void set_startDelay_ms(uint32_t startDelay_ms, StepType step);
  void set_startDelay_ms(uint32_t startDelay_ms, uint32_t stepNumber_int);
  uint32_t get_startDelay_ms(StepType step);
  uint32_t get_startDelay_ms(uint32_t step_int);

  //set the minimum time until the next step must be activated:
  void set_earliestStartNextStep_ms(uint32_t earliestStartNextStep_ms, uint32_t step_int);
  void set_earliestStartNextStep_ms(uint32_t earliestStartNextStep_ms, StepType step);
  //get the minimum time until the next step will be activated:
  uint32_t get_earliestStartNextStep_ms(uint32_t step_int);
  uint32_t get_earliestStartNextStep_ms(StepType step);
  //get the error, when the next step was to fast:
  bool get_error_earliestStartNextStepNotElapsed();

  //set the maximum allowed time for a step:
  void set_latestStartNextStep_ms(uint32_t latestStartNextStep_ms, uint32_t step_int);
  void set_latestStartNextStep_ms(uint32_t latestStartNextStep_ms, StepType step);
  //get the maximum allowed time:
  uint32_t get_latestStartNextStep_ms(uint32_t step_int);
  uint32_t get_latestStartNextStep_ms(StepType step);
  //get the error, when the time is elapsed. See more information in info.adoc:
  bool get_error_latestStartNextStepElapsed();

  //set the end delay:
  void set_endDelay_ms(uint32_t endDelay_ms, uint32_t step_int);
  void set_endDelay_ms(uint32_t endDelay_ms, StepType step);
  //get the end delay:
  uint32_t get_endDelay_ms(uint32_t step_int);
  uint32_t get_endDelay_ms(StepType step);

  //get the time length the step was active
  uint32_t get_stepWasActive_ms(uint32_t step_int);
  uint32_t get_stepWasActive_ms(StepType step);
  //Only for debug:
  uint32_t getActualEvent_int();

  //convert from enumClass to uint32
  uint32_t eCToUi32(StepType step);
  //convert from uint32 to enumClass
  StepType ui32ToEC(uint32_t step_int);
};
#include "sequenceTiming.tpp"