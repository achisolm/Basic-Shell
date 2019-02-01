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

    //parsed[0] = "hello";
    /*
    char *cmd = "ls";
    char *str[3];
    str[0] = "ls";
    str[1] = "-la";
    str[2] = NULL;

    execvp(cmd, str);
    */
    while (1) {
        printf("prompt> ");
        fgets(user_input, MAX_INPUT, stdin);
        strtok(user_input, "\n");
        if (strcmp(user_input, "exit") == 0) {
            break;
        }

//printf("before func\n");
        int num_commands = parse_line(user_input, parsed_line);

        for (int i = 0; i <= num_commands; i++) {
            parse_command(parsed_line[i], parsed_command);

            pid_t pid;

            pid = fork();

            if (pid < 0) {
                printf("ERROR: Unable to execute!");
            }
            else if (pid == 0) {
                    execvp(parsed_command[0], parsed_command);
            }
            else {
                wait();
            }
        }
        
//printf("after func\n");
        //printf("%s", user_input);
        //printf("%s", parsed[0]);

        /*
        int i = 0;
        while (parsed[i] != NULL) {
            printf("%s\n", parsed[i]);
            i++;
        }
        */
    }

    

    return 0;
}

void parse_command(char* str, char** parsed_command) {
//printf("in finc");
    char* token;
    char splitter[2] = " ";
//printf("in finc");
    token = strtok(str, splitter);

    int i = 0;
    
    while(token != NULL) {
        parsed_command[i] = token;
        //printf("%s\n", token);
//printf("in while");
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