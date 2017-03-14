P=tests/mem_test
OBJ=src/mem.c tests/mem_test.c
CFLAGS= -g -Wall -O3
CC=c99

$(P): $(OBJ)