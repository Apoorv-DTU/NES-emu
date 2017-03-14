#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

struct reg{
    uint8_t X;
    uint8_t Y;
    uint8_t A;
    uint8_t S;
    uint8_t P;
    uint8_t PC;
};

typedef struct reg reg_t;

#endif