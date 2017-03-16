#include "stack.h"
#include "mem.h"

void TSX(reg_t* regs) {
    regs->X = regs->S;
    set_PC_NZ(regs, regs->X);
}

void TXS(reg_t* regs) {
    regs->S = regs->X;
}

void PHA(reg_t* regs) {
    m_write(0x100 + regs->S, regs->A, ABS, *regs);
    regs->S--;
}

void PLA(reg_t* regs) {
    regs->A = m_read(0x100 + regs->S, ABS, regs);
    regs->S++;
}

void PHP(reg_t* regs) {
    m_write(0x100 + regs->S, regs->P, ABS, *regs);
    regs->S--;
}

void PLP(reg_t* regs) {
    regs->A = m_read(0x100 + regs->S, ABS, regs);
    regs->S++;
}