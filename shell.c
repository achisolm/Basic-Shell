/*
 * Authors: Adam Chisolm and Jon Sulcer
 * Date: 5 Feb. 2019
 * File: shell.c
 * Description: A basic implementation of the Unix shell.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

const int MAX_INPUT = 100;

void interactive();
void batch(char* file_name);
void parse_command(char* str, char** parsed_command);
int parse_line(char* line, char** parsed_line);
void execute_line(char* line);

int main(int argc, char* argv[])
{
    // Interactive Mode
    if (argc == 1) {
        interactive();
    }

    // Batch Mode
    else if (argc == 2) {
        batch(argv[1]);
    }

    // Error Mode
    else {
        printf("ERROR: Wrong number of arguments\n");
    }
    
    return 0;
}

void interactive() {
    char user_input [MAX_INPUT];

    while (1) {
        printf("prompt> ");
        fgets(user_input, MAX_INPUT, stdin);
        
        execute_line(user_input);
    }
}

void batch(char* file_name) {
    
    char line[MAX_INPUT];
    FILE *batch_file;
    batch_file = fopen(file_name, "r");

    if (batch_file == NULL) {
        printf("ERROR: Could not open file\n");
        exit(0);
    }

    while (fgets(line, MAX_INPUT, batch_file)) {
        execute_line(line);
    }

    fclose(batch_file);
}

void execute_line(char* line) {
    
    char* parsed_command [MAX_INPUT];
    char* parsed_line [MAX_INPUT];

    strtok(line, "\n");

    int num_commands = parse_line(line, parsed_line);

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