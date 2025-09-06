# Application1_JC2025
Real Time Systems Application 1

John Crawford

5286620

Context: Space Station / Satellite Beacon


# Analysis & Exploration

## Q1. Vary Priorities:

Change the print task’s priority to 2 (higher than blink’s 1). With such short tasks and delays, you may not notice a big difference, but in principle the print task would preempt the blink task if it were ready. Given both tasks spend most time sleeping, the effect is minimal. In later projects with CPU-bound tasks, priority will matter more. 

Does anything happen to the LED if you increase the delay within the print task? What if you increase the number of characters printed? 


### Answer 1: 
![alt text](<Screenshot 2025-09-06 021311.png>)
After changing priority, I didnt notice much change... specifically because with the timing info in the console, I can see them coming through at the exact same time (see screenshot attached). Increasing the delay in the print task did nothing either. 

However! Increasing the characters in the print function, caused a 20ms delay before the LED even began blinking. On subsequent prints, there was no issue, as the tasks are now running independently. It only mattered on startup, as the tasks are created serially.

![alt text](<Screenshot 2025-09-06 022149-1.png>)


## Q2. Increase Load:
Remove the vTaskDelay in the print task (making it a tight loop printing continuously). Be careful – this will flood the console. But it illustrates a point: if one task never yields, it can starve the other. In this case, the LED might stop blinking on schedule because the print task hogs the CPU. This is a starvation scenario, leading into Project 2. If you try this, reset it back after observing a few lines, to avoid crashing your serial output. 

Describe the behavior you observed.

### Answer 2: 
![alt text](<Screenshot 2025-09-06 022400-1.png>)

As you can see in the screenshot - there is only print timing logs being shown in the console. The LED did not blink even once, as the print task was hogging all the CPU.



## Q3. Thematic Customization:
If you chose the space context, perhaps change the printed message to “Telemetry OK” or similar. In healthcare, print a pseudo heart rate. In security, print sensor status.  

Assume you were a developer of one of these applications - might there be some considerations that you would want to take into consideration in how verbose (or not) you want your messages to be? Additionally, explain why this system benefits from having correct functionality at predictable times.

### Answer 3:
definitely. I think verbiage is important for crucial status messages, as you want to strike a balance between being too much to read, making it hard to stay on top of the messages, or too little, causing eye fatigue. 

In my context (space station), the beacon status messages should be short and uniform, making it easy to identify a missing message or bad output, whereas the print messages can be a bit longer, as they are transmitted less frequently and convey a bit more info to verify that everything is ok.

# Real Time Concept Check

## Q4. 

Identify/Verify the period of each task; you can try to do this via the simulator, or perhaps by printing data to the console, or connect the outputs to the logic analyzer.

- Describe how you measure the periods:

- LED blink task period:

- Print task period:


Because we used vTaskDelay, these periods are maintained fairly accurately. In a hard real-time requirement, missing a period (e.g., LED not toggling on time) might be a system failure.

### Answer 4:
I measured the period by printing uptime for each task, and to find exact periodx you can just subtract the last one from the current one to find the period between. This methodology works for both LED and print tasks. A better method for more rigorous applications may be to print the exact period to the console for each task rather than just uptime.

## Q5.

Did our system tasks meet the timing requirements?

- How do you know?
- How did you verify it?

### Answer 5:
Yes it did, as the console outputs are very consistent, and I have not yet seen an LED over 250ms per state, and a print over 10s. The vTaskDelay is very accurate.

## Q6. 

If the LED task had been written in a single-loop with the print (see baseline super-loop code), you might have seen the LED timing disturbed by printing (especially if printing took variable time).

- Did you try running the code?
- Can you cause the LED to miss it's timing requirements?
- If yes, how?
- If no, what did you try?

### Answer 6:
Yes, i did try running the code, and it was very shaky on timing, because as the print task was completing, the LED had to wait to blink. Additional characters & longer longprint() arguments both created issues. This is due to the CPU having to fully focus on print before moving back to the blink task. 

The way i kinda understand this concept is like a circuit, and a single loop is components in series, while the FreeRTOS tasks are in parallel. The 'voltage' (CPU) is shared when they are in 'parallel' (FreeRTOS tasks). 


## Q7. 
Do you agree or disagree: By using multitasking, we were able to achieve timing determinism for the LED blink. Why or why not?

### Answer 7:
No, determinism was not quite acheived. We are close, but the reliability is still not 100% due to our use of vTaskDelay, meaning the CPU is asleep most of the time, not tracking the exact timing of the delay! Additionally, if the print had a higher priority, and for some reason the CPU were to get choked up on that task, it could cause the LED to miss a cylce, making it not deterministic.
