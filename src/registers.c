#include "registers.h"

void set_PC_NZ(reg_t* regs, const uint8_t value) {
    
    if(value > 0x80)
        regs->P |= (1 << 7);
    else if (value == 0)
        regs->P |= 2;
    else {
        regs->P &= ~(1 << 7);
        regs->P &= ~2;
    }
}

void TAX(reg_t* regs) {
    regs->X = regs->A;
    set_PC_NZ(regs, regs->X);
}

void TAY(reg_t* regs) {
    regs->Y = regs->A;
    set_PC_NZ(regs, regs->Y);
}

void TXA(reg_t* regs) {
    regs->A = regs->X;
    set_PC_NZ(regs, regs->X);
}

void TYA(reg_t* regs) {
    regs->A = regs->Y;
    set_PC_NZ(regs, regs->Y);
}

void CLC(reg_t* regs) {
    regs->P &= ~1;
}

void CLI(reg_t* regs) {
    regs->P &= ~4;
}

void CLD(reg_t* regs) {
    regs->P &= ~8;
}

void CLV(reg_t* regs) {
    regs->P &= ~64;
}


void SEC(reg_t* regs) {
    regs->P |= 1;
}

void SEI(reg_t* regs) {
    regs->P |= 4;
}

void SED(reg_t* regs) {
    regs->P |= 8;
}