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

// Register transform commands
void TAX(reg_t* regs);
void TAY(reg_t* regs);
void TXA(reg_t* regs);
void TYA(reg_t* regs);

// Status flag commands
void CLC(reg_t* regs);
void CLD(reg_t* regs);
void CLI(reg_t* regs);
void CLV(reg_t* regs);

void SEC(reg_t* regs);
void SED(reg_t* regs);
void SEI(reg_t* regs);




#endif