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
                    const uint32_t *const in_earliestNextStep_ms,
                    const uint32_t *const in_latestNextStep_ms,
                    const uint32_t *const in_endDelay_ms,
                    uint32_t *const out_stepTime_ms)
                  : _actualStep(startStep)
                  , _nextStep(startStep)
                  , _in_earliestNextStep_ms(in_earliestNextStep_ms)
                  , _in_latestNextStep_ms(in_latestNextStep_ms)
                  , _in_endDelay_ms(in_endDelay_ms)
                  , _out_stepWasActive_ms(out_stepTime_ms){
}

template<typename StepType>
void ClassSequenceTiming<StepType>::setNextStep(StepType nextStep){
  _nextStep = nextStep;
}

template<typename StepType>
bool ClassSequenceTiming<StepType>::sequenceProcess_error(){
  //Use "if" and not "switch case", because it must run through in one go.

  //for very first Step (from constructor) or for forceStepImmediately:
  if (_event == Event::StartTimeForActiveStep){
    _oldActiveStep_ms = millis(); //Used for _in_latestNextStep_ms, _in_earliestNextStep_ms and _out_stepWasActive_ms
    _event = Event::EventIsActive;
  }
  //This is called as long as the step is active:
  if (_event == Event::EventIsActive){
    _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
        // Step is in time:
    if (_in_latestNextStep_ms[uint32_t(_actualStep)] != 0){ //if == 0, _in_latestNextStep_ms is not used
      if (millis() - _oldActiveStep_ms >= _in_latestNextStep_ms[uint32_t(_actualStep)]){
        sequenceTimingError = SequenceTimingError::LatestNextStepElapsed;
        _event = Event::DoNothingBecauseOfError;
        return bool(sequenceTimingError); //returns 0 if no error
      }
    }
    if (_nextStep != _actualStep){
      if (millis() - _oldActiveStep_ms < _in_earliestNextStep_ms[uint32_t(_actualStep)]){
        sequenceTimingError = SequenceTimingError::EarliestNextStepNotElapsed;
        _event = Event::DoNothingBecauseOfError;
        return bool(sequenceTimingError);
      }
      //Only do this when there is no error AND _nextStep != _actualStep:
      _oldEndDelay_ms = millis();
      _event = Event::EndDelay;
    }
  }
  if (_event == Event::EndDelay){
    _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
    _deltaEndDelay_ms = millis() - _oldEndDelay_ms;
    if(_deltaEndDelay_ms >= _in_endDelay_ms[uint32_t(_actualStep)]){
      _deltaEndDelay_ms = 0;
      _actualStep = _nextStep;
      _oldActiveStep_ms = millis(); //Used for _in_latestNextStep_ms, _in_earliestNextStep_ms and _out_stepWasActive_ms
      _event = Event::EventIsActive;
    }
  }
  if (_event == Event::DoNothingBecauseOfError){ //If you want reset the error: setForceStep(..)
    _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
  }
  return bool(sequenceTimingError);
}

template<typename StepType>
StepType ClassSequenceTiming<StepType>::getActualStep(){
  return _actualStep;
}

template<typename StepType>
void ClassSequenceTiming<StepType>::setForceStep(StepType forceStep){
  sequenceTimingError = SequenceTimingError::NoError;
  _actualStep = forceStep;
  _nextStep   = forceStep;
  _event      = Event::StartTimeForActiveStep;
}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::getPendingEndDelay_ms(){
  return _in_endDelay_ms[uint32_t(_actualStep)] - _deltaEndDelay_ms;
}

template<typename StepType>
SequenceTimingError ClassSequenceTiming<StepType>::getError(){
  return sequenceTimingError;
}