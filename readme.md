This is my first time I use github and release it to a arduino library. For any suggestions, please let me know. andreas.rosenheim@gmail.com.

Sequencer is the same as state machine and step chains. It has nothing to do with a sequencer for music.

If you want to use a sequence chain, you have very often to use timing. Then you need to use "SequenceTiming."

***Advantage***
- startDelay of every step
- endDelay of every step
- Error when time of one step is elapsed is possible.
- Error when the next step was to early activated is possible.
- It is possible to force a step, this will also reset the errors.
- Measurement how long a step was active.
- All is "non blocking" timing code.
- Change of timing at runtime is possible.

***Disadvantage***
- a little bit slower than self-made switch-case sequence chains (µs-range)
- more memory is necessary, because of the timing for every step

***Information***
- You should be familiar with switch case with enum-class. This is still needed. You can have a look at:
  - https://forum.arduino.cc/t/yet-another-finite-state-machine-introduction/1198997
  - https://forum.arduino.cc/t/transisiton-from-enum-to-enum-class/1284063/9
- Debounce of a switch-button is not included, but normally at a sequence chain not necessary.
- Timing over more steps is not included
***
***Documentation of this SequenceTiming library***\
https://github.com/Andreas1313/SequenceTiming/docs
***
***Keywords***\
step, sequence, sequencer, chain, state, machine, time, based, automation