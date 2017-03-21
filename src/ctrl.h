#ifndef CTRL_H
#define CTRL_H

#include "registers.h"
#include "mem.h"

void JMP(uint16_t loc, Mode m, reg_t *regs);
void JSR(uint16_t loc, reg_t* regs);
void RTS(reg_t* regs);

void BCC(uint8_t offset, reg_t* regs);
void BCS(uint8_t offset, reg_t* regs);
void BNE(uint8_t offset, reg_t* regs);
void BEQ(uint8_t offset, reg_t* regs);
void BVC(uint8_t offset, reg_t* regs);
void BVS(uint8_t offset, reg_t* regs);
void BMI(uint8_t offset, reg_t* regs);
void BPL(uint8_t offset, reg_t* regs);

void BRK(reg_t* regs);
void RTI(reg_t* regs);
void NOP();

#endif