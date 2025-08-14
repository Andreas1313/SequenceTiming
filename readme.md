
If you want to use a sequence chain, you have very often to use timing. Than you should use "sequenceTiming".\
Advantage:
- startDelay of every step (see End/Start-Delay below)
- endDelay of every step   (see End/Start-Delay below)
- Error when time is elapsed. It will give an error and block the next step. But this can also be used for normal function.
- Error when the next step was to fast. I like this, it will help to eliminate a lot of wrong handling.
- Measurement of step time (see Step Time below)
- Of course all is "non blocking" timing code. No delay is used.

Disadvantage:
- a little bit slower than self made switch-case sequence chains
- more memory is necessary, because of the timing for every step

Information:
- You still need the switch case (or if) structure.
- in general a sequence chain is complex for small chains, but when you have larger chains it is getting structurated
- Debounce of a switch-button is not included, but normally at a sequence chain only necessary when you do not have a following step.
  Example where you need it: To activate something very fast or when you -release- a button, you should use debounce.
- Timing over more steps is not included

***start/endDelay***
The delay between two steps is always endDelay + startDelay. Use it where it is more reasonable.\
Example for start delay: Before a cylinder moves, you want to wait a vibration time. So use the startDelay\
Expamle for end delay: After you send some text to a display, the user should have some time read, but than you want to proceed.

***stepTime***\
The stepTime is the time the step is active. So it starts afte the end delay and ends after the start delay of the next step.

You can use it for
- Time tracking
- First measurement, and than set the start/end delay, Error when time is elapsed, Error when the next step was to fast

***suggestion to use a sequence chain in general***\
In one sequence chain always only one step can be active.\
So at smaller projects, use one sequence chain where you want that only one step is active.\
If you really want to split a sequence chain (where only one reasonable step is active):\
At larger projects, it can be clearely arranged to separate in "after power up", "normal run", "before power down" sequence chain.\
Strongly recommended: Use at the end of "after power up" and "normal run" a step where you really do nothing (also not jump to other step).\
Only a complete reset should start from beginning. If you do a complete reset per software, be aware which steps you activate in which order.

***Just for information***
- If you want to restart the actual step, just do as an example: "blink_1.set_nextStep(blink_1.get_actualStep());"

***get_error_latestStartNextStepElapsed***\
You can use this as fatal error (restart of device, or reset button press).\
You can use this to try the last step again.\
You can use this for a warning message and proceed with next step, where you have long time to proceed.\
You can use this to proceed with half speed.\
...

***Key Words***\
step, sequence, sequencer, chain, state, machine, time, based, automation\
German words: Schrittkette, Automat, Zustandsautomat, Ereignisgesteuert, Zeitgesteuert\

***General sequence chain information*** (from KI Gemini)\
Step-chain programming is a programming paradigm that divides a process into a series of steps and transitions.\
Each step represents an action or state, while transitions define conditions that must be met to move from the current step to the next.\
This type of programming provides clarity, structure, flexibility and efficiency when controlling complex processes in various automation areas. 

Basics of step chain programming:\
Steps:\
A step is a defined state or action that is executed in a process.

***Transitions***\
A transition is a condition that must be met for the process to move from the current step to the next.

***Sequence***\
The step chain consists of a sequence of steps and transitions, where each step triggers actions and each transition enables the transition to the next step.\
Advantages of step chain programming:

***Clarity***\
Step chains enable a clear and concise representation of complex processes.

***Structuring***\
The division into individual steps simplifies programming and maintenance.

***Flexibility***\
step chains can be easily adapted to changing requirements.

***Efficiency***\
The use of step chains can optimize process sequences and increase efficiency. 

***Use of step chains***\
Step chains are used in a variety of areas.

Application, e.g:
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