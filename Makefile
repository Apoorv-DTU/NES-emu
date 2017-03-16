P=tests/mem_test
OBJ=$(wildcard */*.c)
CFLAGS= -g -Wall -O3 -std=c99
CC=gcc

$(P): $(OBJ)