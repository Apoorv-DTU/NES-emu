P=tests/mem_test
OBJ=$(wildcard */*.c)
CFLAGS= -g -w -O3 -std=c99
CC=gcc

$(P): $(OBJ)