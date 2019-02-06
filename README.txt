Authors: Adam Chisolm and Jon Sulcer
Date: 5 Feb. 2019
Files: shell.c
Description: A basic implementation of the Unix shell.

Design Overview:

Upon running the code, the program prints a prompt for the user to enter a command. The command
is read in using standard input, and the input is then parsed using the parse line function. Parsed
line takes every command given in a line (commands may be separated by semicolons, or a single command
may be given) and separates multiple commands if necessary. After the input is passed through the parsed
line function, each command is individually ran through the parse command function which allows the command
to be ran by execvp. Both parse line and parse command use strtok to split the commands and command flags
respectively.

The program can also account for batch files, and performs a similar process except with replacing standard 
input with the commands found in the file.

Specifications:

As of now, the program simply displays the prompt after every input unless the user enters "exit". If the command
is not valid, nothing happens, and the prompt is displayed. If the command is valid, it successfully runs the command
and also displays the prompt. We simply leave it up to execvp to decide if the command is valid, if it is not valid, 
execvp doesn't do anything with that input (A large blank space does break the program, but single space will not).

Known Bugs/Problems:

1. Sometimes using "exit" to exit requires it to be entered twice in a row for the program to successfully close.

2. Our use of the wait() function produces a warning upon compilation.

3. Based on the way we implmented when our execvp runs, multiple commands do not run simultaneously.

4. 2 or more spaces between semicolons may crash the program.
