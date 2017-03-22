#ifndef ALU_H
#define ALU_H

#include "mem.h"
#include "registers.h"

void AND(uint16_t loc, Mode m, reg_t* regs);
void EOR(uint16_t loc, Mode m, reg_t* regs);
void ORA(uint16_t loc, Mode m, reg_t* regs);

void BIT(uint16_t loc, Mode m, reg_t* regs);
void ADC(uint16_t loc, Mode m, reg_t* regs);
void SBC(uint16_t loc, Mode m, reg_t* regs);

static void compare(uint16_t loc, Mode m, reg_t* regs, uint8_t axy);
void CMP(uint16_t loc, Mode m, reg_t* regs);
void CPX(uint16_t loc, Mode m, reg_t* regs);
void CPY(uint16_t loc, Mode m, reg_t* regs);

void INC(uint16_t loc, Mode m, reg_t* regs);
void INX(uint16_t loc, Mode m, reg_t* regs);
void INY(uint16_t loc, Mode m, reg_t* regs);

void DEC(uint16_t loc, Mode m, reg_t* regs);
void DEX(uint16_t loc, Mode m, reg_t* regs);
void DEY(uint16_t loc, Mode m, reg_t* regs);

void ASR(uint16_t loc, Mode m, reg_t* regs);
void ASL(uint16_t loc, Mode m, reg_t* regs);
void ROR(uint16_t loc, Mode m, reg_t* regs);
void ROL(uint16_t loc, Mode m, reg_t* regs);

#endif