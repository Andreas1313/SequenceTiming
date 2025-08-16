This is my first time I use github and release it to a arduino library. For any suggestions, please let me know. andreas.rosenheim@gmail.com.

Sequencer is the same as state machine and step chains. It has nothing to do with a sequencer for music.

If you want to use a sequence chain, you have very often to use timing. Than you should use "SequenceTiming".\

***Advantage***
- startDelay of every step (see End/Start-Delay below)
- endDelay of every step   (see End/Start-Delay below)
- Error when time is elapsed. It will give an error and block the next step. But this can also be used for normal function.
- Error when the next step was to fast. It will help to eliminate wrong handling.
- Measurement of step time (see Step Time below)
- All is "non blocking" timing code. No delay() is used.
- Change of timing at runtime is possible.

***Disadvantage***
- a little bit slower than self made switch-case sequence chains (µs-range)
- more memory is necessary, because of the timing for every step

***Information***
- You should be familiar with switch case with enum-class. This is still needed. You can have a look at:
  - https://forum.arduino.cc/t/yet-another-finite-state-machine-introduction/1198997
  or
  - https://forum.arduino.cc/t/state-machines-a-short-tutorial/580593
- Debounce of a switch-button is not included, but normally at a sequence chain only necessary when you force a step. For example at reset. But for simple debounce you can use the endDelay of this class.
- Timing over more steps is not included

***Advantage of sequencer (state machine, step chains) in general***
- Clarity: Sequencer enable a clear and concise representation of complex processes.
- Structuring: The division into individual steps simplifies programming and maintenance.
- Flexibility: step chains can be easily adapted to changing requirements.
- Efficiency: The use of step chains can optimize process sequences and increase efficiency. 

***Use of step chains***\
Step chains are used in a variety of areas.
- System control: Control of production systems, conveyor belts, robots, etc.
- Machine control: control of machine tools, injection molding machines, etc.
- Building technology: control of heating, ventilation and air conditioning systems, lighting, etc.
- Robotics: Control of robot movements and actions.
- Shake hand communication
Example step chain:\
Imagine a simple washing machine. One step could be "fill with water",\
followed by a transition that checks whether the desired amount of water has been reached.\
The next step could be "wash", followed by a transition that checks whether the set washing time has elapsed,\
and so on.

***Documentation of this SequenceTiming library***\
See docs folder.
***
***Key Words***\
step, sequence, sequencer, chain, state, machine, time, based, automation