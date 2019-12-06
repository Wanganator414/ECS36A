# Homework 3
## Due: November 8, 2019
### Points: 100
---
#### **UNIX/Linux Questions**

1. *(10 pts)* What Linux program could I use to generate a random number?

    One way to generate a random number in bash is to simply print out built in variables, such as using `echo $RANDOM` or `echo` its seeded counter part `RANDOM=$$`. Alternatively,the `shuf` command will also the do trick. For example:
        
        shuf -i 100-999 -n1

    The above command will return a single number between the range (100-999 inclusive) specified by the '-i' flag.

2. *10 pts* What is the name of the process with PID 4?

    In *CSIF*, after running `ps -aux`, the process *kworker* is listed for PID 4. Which is a placeholder process to denote that some process is being run on one of a device's CPU cores.

