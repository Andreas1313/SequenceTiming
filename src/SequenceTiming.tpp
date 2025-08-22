/*Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250815_sT_C_0_132
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.
-Credit required  -Share alike  -No warranty provided
-Free for private use.
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com. You can directly start. You do not have to wait for an answer.
-Contact for commercial use: andreas.rosenheim@gmail.com.(You only have to donate to "Doctors Without Borders",
 or similar institution. Which should be tax-deductible)*/

#pragma once

//private:
//Only for debug:
template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::getActualEvent() {
  return static_cast<int>(_event);
}

//public:
template<typename StepType>
ClassSequenceTiming<StepType>::ClassSequenceTiming(StepType startStep,
                      const uint32_t *const in_startDelay_ms,
                      const uint32_t *const in_earliestStartNextStep_ms,
                      const uint32_t *const in_latestStartNextStep_ms,
                      const uint32_t *const in_endDelay_ms,
                      uint32_t *const out_stepTime_ms):
                      _actualStep(startStep),
                      _nextStep(startStep),
                      //With the "new" the array is enlarged, because it is in "constuctor initializer list" it is done at compile time:
                      _in_startDelay_ms(in_startDelay_ms),
                      _in_earliestStartNextStep_ms(in_earliestStartNextStep_ms),
                      _in_latestStartNextStep_ms(in_latestStartNextStep_ms),
                      _in_endDelay_ms(in_endDelay_ms),
                      _out_stepWasActive_ms(out_stepTime_ms){
}

template<typename StepType>
void ClassSequenceTiming<StepType>::set_nextStep(StepType nextStep){
  _nextStep = nextStep;
}

template<typename StepType>
void ClassSequenceTiming<StepType>::sequenceProcess(){
  //Use "if" and not "switch case", because it must run through in one go.

  //for very first Step (from constructor) or for forceStepImmediately:
  if (_event == Event::startTimeForActiveStep){
    _oldActiveStep_ms = millis(); //Used for _in_latestStartNextStep_ms, _in_earliestStartNextStep_ms and _out_stepWasActive_ms
    _event = Event::eventIsActive;
  }
  //This is called as long as the step is active:
  if (_event == Event::eventIsActive){
    // Step is in time:
    if (_in_latestStartNextStep_ms[uint32_t(_actualStep)] != 0){ //if == 0, _in_latestStartNextStep_ms is not used
      if (millis() - _oldActiveStep_ms >= _in_latestStartNextStep_ms[uint32_t(_actualStep)]){
        _error_latestStartNextStepReached = true;
        _event = Event::doNothingBecauseOfError;
        return;
      }
    }
    if (_nextStep != _actualStep){
      if (millis() - _oldActiveStep_ms < _in_earliestStartNextStep_ms[uint32_t(_actualStep)]){
        _error_earliestStartNextStepNotElapsed = true;
        _event = Event::doNothingBecauseOfError;
        return;
      }
      //Only do this when there is no error AND _nextStep != _actualStep:
      _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
      _oldEndDelay_ms = millis();
      _event = Event::endDelayAndBeginOfStartDelay;
    }
  }
  if (_event == Event::endDelayAndBeginOfStartDelay){
    if(millis() - _oldEndDelay_ms >= _in_endDelay_ms[uint32_t(_actualStep)]){
      _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
      _oldStartDelay_ms = millis();
      _event = Event::startNextStep;
    }
  }
  if (_event == Event::startNextStep){
    if (millis() - _oldStartDelay_ms >= _in_startDelay_ms[uint32_t(_nextStep)]){
      _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
      _actualStep = _nextStep;
      _oldActiveStep_ms = millis(); //Used for _in_latestStartNextStep_ms, _in_earliestStartNextStep_ms and _out_stepWasActive_ms
      _event = Event::eventIsActive;
    }
  }
  if (_event == Event::doNothingBecauseOfError){ //You have to reset the error and set _event == Event::startTimeForActiveStep
    _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
  }
}

template<typename StepType>
StepType ClassSequenceTiming<StepType>::get_actualStep(){
  return _actualStep;
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
bool ClassSequenceTiming<StepType>::get_error_earliestStartNextStepNotElapsed(){
  return _error_earliestStartNextStepNotElapsed;
}
template<typename StepType>
bool ClassSequenceTiming<StepType>::get_error_latestStartNextStepElapsed(){
  return _error_latestStartNextStepReached;
}