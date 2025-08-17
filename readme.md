This is my first time I use github and release it to a arduino library. For any suggestions, please let me know. andreas.rosenheim@gmail.com.

Sequencer is the same as state machine and step chains. It has nothing to do with a sequencer for music.

If you want to use a sequence chain, you have very often to use timing. Then you need to use "SequenceTiming."\

***Advantage***
- startDelay of every step
- endDelay of every step
- Error when time of one step is elapsed.
- Error when the next step was to early activated.
- It is possible to force a step, this will reset the errors.
- Measurement how long a step was active.
- All is "non blocking" timing code. No delay() is used.
- Change of timing at runtime is possible.

***Disadvantage***
- a little bit slower than self-made switch-case sequence chains (µs-range)
- more memory is necessary, because of the timing for every step

***Information***
- You should be familiar with switch case with enum-class. This is still needed. You can have a look at:
  - https://forum.arduino.cc/t/yet-another-finite-state-machine-introduction/1198997 or
  - https://forum.arduino.cc/t/state-machines-a-short-tutorial/580593
- Debounce of a switch-button is not included, but normally at a sequence chain, only necessary when you force a step. For example at reset. But for simple debounce, you can use the endDelay of this class.
- Timing over more steps is not included
***
***Documentation of this SequenceTiming library***\
See docs folder at https://github.com/Andreas1313/SequenceTiming
***
***Keywords***\
step, sequence, sequencer, chain, state, machine, time, based, automation