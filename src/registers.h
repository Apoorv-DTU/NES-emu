#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

struct reg{
    uint8_t X;
    uint8_t Y;
    uint8_t A;
    uint8_t S;
    uint8_t P;
    uint16_t PC;
};

typedef struct reg reg_t;

void set_PC_NZ(reg_t* regs, const uint8_t value);

#endif