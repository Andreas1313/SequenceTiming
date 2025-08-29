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
    // Step is in time:
    if (_in_latestNextStep_ms[uint32_t(_actualStep)] != 0){ //if == 0, _in_latestNextStep_ms is not used
      if (millis() - _oldActiveStep_ms >= _in_latestNextStep_ms[uint32_t(_actualStep)]){
        sequenceTimingError = SequenceTimingError::LatestNextStepElapsed;


        //_error_latestNextStepElapsed = true;


        _event = Event::DoNothingBecauseOfError;
        return bool(sequenceTimingError); //returns 0 if no error
      }
    }
    if (_nextStep != _actualStep){
      if (millis() - _oldActiveStep_ms < _in_earliestNextStep_ms[uint32_t(_actualStep)]){
        sequenceTimingError = SequenceTimingError::EarliestNextStepNotElapsed;


        //_error_earliestNextStepNotElapsed = true;


        _event = Event::DoNothingBecauseOfError;
        return bool(sequenceTimingError);
      }
      //Only do this when there is no error AND _nextStep != _actualStep:
      _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
      _oldEndDelay_ms = millis();
      _event = Event::EndDelay;
    }
  }
  if (_event == Event::EndDelay){
    if(millis() - _oldEndDelay_ms >= _in_endDelay_ms[uint32_t(_actualStep)]){
      _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
      _actualStep = _nextStep;
      _oldActiveStep_ms = millis(); //Used for _in_latestNextStep_ms, _in_earliestNextStep_ms and _out_stepWasActive_ms
      _event = Event::EventIsActive;
    }
  }
  if (_event == Event::DoNothingBecauseOfError){ //You have to reset the error and set _event == Event::StartTimeForActiveStep
    _out_stepWasActive_ms[uint32_t(_actualStep)] = millis() - _oldActiveStep_ms;
  }
  return bool(sequenceTimingError);
}

template<typename StepType>
StepType ClassSequenceTiming<StepType>::getActualStep(){
  return _actualStep;
}

template<typename StepType>
void ClassSequenceTiming<StepType>::setForceStepImmediately(StepType forceStep){
  sequenceTimingError = SequenceTimingError::NoError;


  // _error_latestNextStepElapsed      = false;
  // _error_earliestNextStepNotElapsed = false;
  
  
  _actualStep = forceStep;
  _nextStep   = forceStep;
  _event      = Event::StartTimeForActiveStep;
}

template<typename StepType>
SequenceTimingError ClassSequenceTiming<StepType>::getError(){
  return sequenceTimingError;
}

// template<typename StepType>
// bool ClassSequenceTiming<StepType>::getError_earliestNextStepNotElapsed(){
//   return _error_earliestNextStepNotElapsed;
// }
// template<typename StepType>
// bool ClassSequenceTiming<StepType>::getError_latestNextStepElapsed(){
//   return _error_latestNextStepElapsed;
//}

template<typename StepType>
uint32_t ClassSequenceTiming<StepType>::get_pendingTimeOfEndDelay_ms(){
  return millis() - _oldEndDelay_ms;
}