P=tests/mem_test
OBJ=$(wildcard */*.c)
CFLAGS= -g -Wno-overflow -O3 -std=c99
CC=gcc

$(P): $(OBJ)