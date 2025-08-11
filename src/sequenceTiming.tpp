/*Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250803_sT_C_0_132
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.
-Credit required  -Share alike  -No warranty provided
-Free for private use.
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com.
-Contact for commercial use: andreas.rosenheim@gmail.com.
(You only have to donate to "Doctors Without Borders", or similar institution. Which should be tax-deductible)*/

#pragma once
#include "Arduino.h"

template<typename StepType> 
ClassSequenceTiming<StepType>::ClassSequenceTiming(StepType startStep):
          _actualStep(startStep),
          _nextStep(startStep),
          _numberOfSteps(static_cast<int>(StepType::VeryLastEnum)),
          //With the "new" the array is enlarged, because it is in "constuctor initializer list" it is done at compile time:
          _startDelay_ms(new uint32_t[_numberOfSteps]),
          _earliestStartNextStep_ms(new uint32_t[_numberOfSteps]),
          _latestStartNextStep_ms(new uint32_t[_numberOfSteps]),
          _endDelay_ms(new uint32_t[_numberOfSteps]),
          _stepWasActive_ms(new uint32_t[_numberOfSteps]){
  //initialize all time values with 0. At _latestStartNextStep_ms the 0 is switching it off:
  for (uint32_t deleteLoop = 0; deleteLoop < _numberOfSteps; deleteLoop++){
    _startDelay_ms[deleteLoop] = 0;
    _latestStartNextStep_ms[deleteLoop] = 0;
    _earliestStartNextStep_ms[deleteLoop] = 0;
    _endDelay_ms[deleteLoop] = 0;
    _stepWasActive_ms[deleteLoop] = 0;
  }
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_nextStep(StepType nextStep) {
  _nextStep = nextStep;
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_nextStep(uint32_t nextStep_int){
  set_nextStep((StepType)nextStep_int);
}

template<typename StepType>
void ClassSequenceTiming<StepType>::sequenceProcess(){
  //I use "if" and not "switch case", because it must run through in one go.

  //for very first Step (from constructor) or for forceStepImmediately:
  if (_event == Event::startTimeForActiveStep){
    _oldActiveStep_ms = millis(); //Used for _latestStartNextStep_ms, _earliestStartNextStep_ms and _stepWasActive_ms
    _event = Event::eventIsActive;
  }
  //This is called as long as the step is active:
  if (_event == Event::eventIsActive){
    // Step is in time:
    if (_latestStartNextStep_ms[uint32_t(_actualStep)] != 0){ //if == 0, _latestStartNextStep_ms is not used
      if (millis() - _oldActiveStep_ms >= _latestStartNextStep_ms[uint32_t(_actualStep)]){
        _error_latestStartNextStepReached = true;
        _event = Event::doNothingBecauseOfError;
        return;
      }
    }// "else" allone is not enough, because of millis() overrun.(approx 50 days):
    if (_nextStep != _actualStep){
      if (millis() - _oldActiveStep_ms < _earliestStartNextStep_ms[uint32_t(_actualStep)]){
        _error_earliestStartNextStepNotElapsed = true;
        _event = Event::doNothingBecauseOfError;
        return;
      }
      //Only do this when there is no error AND _nextStep != _actualStep:
      _oldEndDelay_ms = millis();
      _event = Event::endDelayAndBeginOfStartDelay;
    }
  }
  if (_event == Event::endDelayAndBeginOfStartDelay){
    if(millis() - _oldEndDelay_ms >= _endDelay_ms[uint32_t(_actualStep)]){
      _oldStartDelay_ms = millis();
      _event = Event::startNextStep;
    }
  }
  if (_event == Event::startNextStep){
    if (millis() - _oldStartDelay_ms >= _startDelay_ms[uint32_t(_nextStep)]){
      _stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
      _actualStep = _nextStep;
      _oldActiveStep_ms = millis(); //Used for _latestStartNextStep_ms, _earliestStartNextStep_ms and _stepWasActive_ms
      _event = Event::eventIsActive;
    }
  }
  if (_event == Event::doNothingBecauseOfError){ //You have to reset the error and set _event == Event::startTimeForActiveStep
  }
}

template<typename StepType>
StepType ClassSequenceTiming<StepType>::get_actualStep(){
  return _actualStep;
}
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_actualStep_int() {
  return static_cast<int>(_actualStep);
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_forceStepImmediately(StepType forceStep){
  _error_latestStartNextStepReached      = false;
  _error_earliestStartNextStepNotElapsed = false;
  _actualStep = forceStep;
  _nextStep   = forceStep;
  _event      = Event::startTimeForActiveStep;
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_forceStepImmediately(uint32_t forceStep_int){
  set_forceStepImmediately((StepType)forceStep_int);
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_numberOfSteps(){
  return _numberOfSteps;
}

template<typename StepType>
void ClassSequenceTiming<StepType>::set_startDelay_ms(uint32_t startDelay_ms, StepType step){
  set_startDelay_ms(startDelay_ms, static_cast<int>(step));
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_startDelay_ms(uint32_t startDelay_ms, uint32_t stepNumber_int){
  _startDelay_ms[stepNumber_int] = startDelay_ms;
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_startDelay_ms(StepType step){
  return get_startDelay_ms(static_cast<int>(step));
}
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_startDelay_ms(uint32_t step_int){
  return _startDelay_ms[step_int];
}

template<typename StepType>
void ClassSequenceTiming<StepType>::set_earliestStartNextStep_ms(uint32_t earliestStartNextStep_ms, uint32_t step_int){
  _earliestStartNextStep_ms[step_int] = earliestStartNextStep_ms;
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_earliestStartNextStep_ms(uint32_t earliestStartNextStep_ms, StepType step){
  set_earliestStartNextStep_ms(static_cast<int>(step),earliestStartNextStep_ms);
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_earliestStartNextStep_ms(uint32_t step_int){
  return _earliestStartNextStep_ms[step_int];
}
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_earliestStartNextStep_ms(StepType step){
  return get_earliestStartNextStep_ms(static_cast<int>(step));
}

template<typename StepType>
bool ClassSequenceTiming<StepType>::get_error_earliestStartNextStepNotElapsed(){
  return _error_earliestStartNextStepNotElapsed;
}

template<typename StepType>
void ClassSequenceTiming<StepType>::set_latestStartNextStep_ms(uint32_t latestStartNextStep_ms, uint32_t step_int){
  _latestStartNextStep_ms[step_int] = latestStartNextStep_ms;
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_latestStartNextStep_ms(uint32_t latestStartNextStep_ms, StepType step){
  set_latestStartNextStep_ms(latestStartNextStep_ms, static_cast<int>(step));
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_latestStartNextStep_ms(uint32_t step_int){
  return _latestStartNextStep_ms[step_int];
}
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_latestStartNextStep_ms(StepType step){
  get_latestStartNextStep_ms(static_cast<int>(step));
}

template<typename StepType>
bool ClassSequenceTiming<StepType>::get_error_latestStartNextStepElapsed(){
  return _error_latestStartNextStepReached;
}

template<typename StepType>
void ClassSequenceTiming<StepType>::set_endDelay_ms(uint32_t endDelay_ms, uint32_t step_int){
  _endDelay_ms[step_int] = endDelay_ms;
}
template<typename StepType>
void ClassSequenceTiming<StepType>::set_endDelay_ms(uint32_t endDelay_ms, StepType step){
  set_endDelay_ms(endDelay_ms, static_cast<int>(step));
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_endDelay_ms(uint32_t step_int){
  return _endDelay_ms[step_int];
}
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_endDelay_ms(StepType step){
  get_endDelay_ms(static_cast<int>(step));
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_stepWasActive_ms(uint32_t step_int){
  return _stepWasActive_ms[step_int];
}
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_stepWasActive_ms(StepType step){
  get_stepWasActive_ms(static_cast<int>(step));
}

//Only for debug:
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::getActualEvent_int() {
  return static_cast<int>(_event);
}


//convert  enumClass to uint32
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::eCToUi32(StepType step){
 return static_cast<int>(step);
}
//convert uint32 to enumClass
template<typename StepType>
StepType ClassSequenceTiming<StepType>::ui32ToEC(uint32_t step_int){
  return (StepType)step_int;
}
