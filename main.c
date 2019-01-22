/*
 * Authors: Adam Chisolm and Jon Sulcer
 * Date: 5 Feb. 2019
 * File: main.c
 * Description: A basic implementation of the Unix shell.
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    int MAX_INPUT = 100;
    char user_input [MAX_INPUT];

    while (1) {
        printf("prompt> ");
        fgets(user_input, MAX_INPUT, stdin);
        printf("%s", user_input);
    }
    printf("hello\n");

    return 0;
}