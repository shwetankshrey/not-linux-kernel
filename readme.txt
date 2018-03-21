OS Assignment 2 Write Up

Authors:

Rohan Chhokra(2016080)
Shwetank Shrey(2016095)

Syscall + CFS Code Description:

We introduce a new parameter within the sched_entity called nr_rt_guarantees, which denotes the number of real time guarantees remaining for the process. Every guarantee denotes that the process must execute for atleast one timeslice, which has again been defined as is in the real time scheduler. Every time we create a new process using fork, we first call a syscall that updates the value of this new parameter. The arguments for this syscall are the PID of the process and the number of guarantees to be given to the process. Next the scheduler is called to call the CFS scheduler. We have also changed the CFS scheduler in the following ways. In the function, pick_next_task_fair which looks for the next task to execute, we first traverse through the sched_entites and find the first such process that has real time guarantees left. Then this process is called for execution. While the scheduler runs, the statistics for the current process are also updated using the update_curr function. We have also changed this by updating the nr_rt_guarantees, subtracting the timeslices for which the process has run. Thus, we can ensure that the process has run for atleast nr_rt_guarantees number of timeslices.

Test Program Code Description:

We test our modifications to the CFS scheduler by making a program in the user space which forks the process. If it is a child process, the syscall is called using the corresponding PID and allots it a fixed number of real time guarantees. The child process then again forks and creates new processes with a different number of guarantees. Another process is run with no real time guarantees. We have taken the different number of guarantees as none, 10, 20, 50 and 100; and have run this test program 5 times and plotted the output.

Expected Output:

We output the time taken to run a certain method in all the different processes and output them. Next, a plot has been created to record and visualise the observations.

Error Values:

An error is thrown in case the PID for which we call the syscall doesn't have a corresponding task_struct. However, this error will never be thrown as the syscall is called right after creating the process. All the possible cases within the CFS code have been handled and there cannot be an error.

Observation:

We see that in comparison to the process with no real time schedules, the one with 10 guarantees is as fast. Giving 20 guarantees works the fastest out of our test cases, after which the time taken slowly increases.
