# Homework 5
## Due: December 6,2019
### Points: 100
---
#### Linux/Unix Questions

1. **(10 points)** The output from the command `ls -l /usr/bin/at` shows:

    `-rwsr-sr-x 1 daemon daemon 51464 Feb 19 2018 /usr/bin/at`

    What do the two “s”es in the permissions mean, and what is the effect on the process created when you run this program?
    
        The "at" built in command allows you to schedule a list of commands to be executed at a later time frame, it will prompt you to enter the commands in a separate prompt and will put them in queue to be executed later.

        When the setuid or setgid attributes are set on an executable file (In this case, the "at" built in), then any users able to execute the file will automatically execute the file with the privileges of the file's owner (commonly root) and/or the file's group, depending upon the flags set. Meaning, any commands scheduled to be run in the future under the "at" command will have the required privileges as when they are first typed in when they are scheduled.

2. *(10 points)* Give a Linux command to print dictionary words that contain the vowels `‘a’, ‘e’, ‘i’, ‘o’, ‘u’, and ‘y’`
in that order. Show your output.

    By using the command sequence `grep .*a.*e.*i.*o.*u.*y /usr/share/dict/words` you would find the word:
            
        facetiously

    *Hint: The file` /usr/share/dict/words` is a dictionary of English words.*

    