/*
 * Authors: Adam Chisolm and Jon Sulcer
 * Date: 5 Feb. 2019
 * File: main.c
 * Description: A basic implementation of the Unix shell.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void parse_command(char* str, char** parsed_command);
int parse_line(char* line, char** parsed_line);

int main(int argc, char* argv[])
{
    int MAX_INPUT = 100;
    char user_input [MAX_INPUT];
    char* parsed_command [MAX_INPUT];
    char* parsed_line [MAX_INPUT];

    while (1) {
        printf("prompt> ");
        fgets(user_input, MAX_INPUT, stdin);
        strtok(user_input, "\n");
        /*
        if (strcmp(user_input, "exit") == 0) {
            break;
        }
        */


        int num_commands = parse_line(user_input, parsed_line);

        for (int i = 0; i < num_commands; i++) {
            parse_command(parsed_line[i], parsed_command);

            if (strcmp(parsed_command[0], "exit") == 0) {
                exit(0);
            }

            pid_t pid;
            int status;

            pid = fork();

            if (pid < 0) {
                printf("ERROR: Unable to execute!");
            }
            else if (pid == 0) {
                execvp(parsed_command[0], parsed_command);
            }
            else {
                while (wait(&status) != pid);
            }
        }
        
    }

    

    return 0;
}

void parse_command(char* str, char** parsed_command) {
    char* token;
    char splitter[2] = " ";
    token = strtok(str, splitter);

    int i = 0;
    
    while(token != NULL) {
        parsed_command[i] = token;

        token = strtok(NULL, splitter);

        i++;
    }
    

    parsed_command[i] = NULL;
}

int parse_line(char* line, char** parsed_line) {
    char* token;
    char splitter[2] = ";";

    token = strtok(line, splitter);

    int i = 0;

    while(token != NULL) {
        parsed_line[i] = token;
        token = strtok(NULL, splitter);
        i++;
    }

    return i;
}