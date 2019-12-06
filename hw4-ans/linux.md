# Homework 4
## Due: November 25 2019
### Points: 100
---

#### **Linux/Unix Questions**

1. **(20 points)** On December 25, 2019, at 00:00:00 PST, how many seconds since January 1, 1970, 00:00:00 UTC,
have passed?

    **Dec 25 2019 00:00:00 PST** is <span style="color:orange">**1577260800s**</span> since epoch time. By entering the following command, you will get the time difference in seconds:

        `date -d "Dec 25 2019" +%s`

2. **(20 points)** How do I find the login names and times of the people currently logged into the system“pc12.cs.ucdavis.edu”,
and also where they logged in from?

    By using the command `who -a` , one can look at currently logged in users and their IP addresses, hence their location. You can also look at what programs they are using via the PIDs listed under their usernames.


3. **(10 points)** How do I delete a file named -i?
    
    To delete a file exclusively called *i*, one can use `rm ./-i` to delete it.