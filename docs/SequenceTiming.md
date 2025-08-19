                #Step Sequence Timing               19 Aug 2025 Andreas1313

Example for a possible timing for the timing diagramm below:
![100_StepTimeTable](picturesFromDocument/100_StepTimeTable.jpg)



A force to the actual step make sense. Example: When you have an error, you can repeat the actual step.
The earliestStartNextStep of this step and the latestStartNextStep of this step also start from beginning.
example: "blink_1.set_nextStep(blink_1.get_actualStep());"

You can use latestStartNextStep not only for critical errors. Example: When you want a warning, you can use it:
Show a warning when you have the error and transfer to next step with a longer latestStartNextStep time.
When you do not have this error, you can skip the next step (with the longer latestStartNextStep time).

When the step after the next step should not be active immediately (which should be the normal case) you can use earliestStartNextStep: When you do not want to allow that the next transfer is already active, when the actual step getting active, than set earliestStartNextStep to a value a little bit more than your processor loop time. It will throw an error when the next step would be immediately activated.