#ifndef CMD_H
#define CMD_H

#define MEM_SIZE 0xffff;

union arg {
    uint8_t small_arg;
    uint16_t big_arg;
};

typedef union arg arg_t; 

enum stat {
    FAIL, BRANCH, CROSS_PAGE, BRANCH_PAGE
}; 

typedef enum stat Status;

struct state{
    uint8_t X;
    uint8_t Y;
    uint8_t A;
    uint8_t S;
    uint8_t P;
    uint16_t PC;

    uint8_t* mem;
};

typedef struct state state_t;

// template for implementation for all the commands
struct cmd {
    int cycles;
    int bytes;
    status (*func)(arg_t*, state_t*);
};

#endif