# CPU_Scheduling_Simulator

COMPILATION: run: g++ simulator.cpp ./a.out

This program simulates the following CPU scheduling algorithms:

First Come First Serve (FCFS)

Shortest Job First (SJF)

Preemptive Priority Scheduling

Round Robin (RR)

The task information will be read from an input file (input.txt) with the following format:

Pid Arrival_Time Burst_Time Priority

All of fields are integer type where

Pid is a unique numeric process ID

Arrival_Time is the time when the task arrives in the unit of milliseconds

Burst_Time is the CPU time requested by a task, in the unit of milliseconds

Priority is the priority associated with each task with low numbers representing high priority.

Note: for RR algorithm you need to define a Time-quantum.

It creates a simple user interface to ask user for input.txt file, a scheduling algorithm and Time-quantum if RR is chosen.

Print progress of task every unit time (millisecond). Once all tasks are completed, the program should compute and print : Average waiting time Average response time Average turnaround time CPU utilization rate

NOTE: the program asks the user which algorithm to choose for the scheduling. Choose between 1 and 4.

If 4 is chosen, the user needs to input a time quantum for the Round Robin algorithm.

input.txt file must be in the same folder as the program. The info has to be in a matrix form.

Below is the report I did for the example implementations of the data. input.txt can be edited for other data.

[CPU_SIMULATOR.pdf](https://github.com/Roshen98/CPU_Scheduling_Simulator/files/8456181/CPU_SIMULATOR.pdf)


