# Author: Adam Chisolm
# File: Makefile
# Description: Makefile for shell program


CC=gcc
CFLAGS=-c -Wall -g
TARGET=shell

all: $(TARGET)

$(TARGET): shell.o
	$(CC) shell.o -o $(TARGET)