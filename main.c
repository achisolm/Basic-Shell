/*
 * Authors: Adam Chisolm and Jon Sulcer
 * Date: 5 Feb. 2019
 * File: main.c
 * Description: A basic implementation of the Unix shell.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void parse(char* str, char** parsed);

int main(int argc, char* argv[])
{
    int MAX_INPUT = 100;
    char user_input [MAX_INPUT];
    char* parsed [MAX_INPUT];

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
        printf("%s", user_input);

printf("before func\n");
        parse(user_input, parsed);
printf("after func\n");
        printf("%s", user_input);
        printf("%s", parsed[0]);

        //execvp(user_input, );
    }

    return 0;
}

void parse(char* str, char** parsed) {
printf("in finc");
    char* token;
    char splitter[2] = " ";
printf("in finc");
    token = strtok(str, splitter);

    int i = 0;
    while(token != NULL) {
        parsed[i] = token;
printf("in while");
        token = strtok(str, splitter);

        i++;
    }

    //parsed[i] = NULL;
}