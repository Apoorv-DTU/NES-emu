#ifndef CMD_H
#define CMD_H

#define MEM_SIZE 0xffff;

#define G_HIGH8(a) (a & ~(0xff))
#define G_LOW8(a) (a & 0xff)

#define S_HIGH8(a, v) ((v << 8) + G_LOW8(a))
#define S_LOW8(a, v) ((G_HIGH8(a) << 8) + v)

typedef uint16_t arg_t; 

enum stat {
    SUCCESS, FAIL, BRANCH, CROSS_PAGE, BRANCH_PAGE
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
    Status (*func)(arg_t*, state_t*);
};

#endif