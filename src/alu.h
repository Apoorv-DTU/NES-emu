#include "mem.h"
#include "registers.h"

void AND(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    regs->A &= value;
    set_PC_NZ(regs, value);
}

void EOR(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    regs->A ^= value;
    set_PC_NZ(regs, value);
}

void ORA(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    regs->A |= value;
    set_PC_NZ(regs, value);
}

void BIT(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    if(value & self->A == 0)
        regs->P |= 2;
    else regs->P &= ~2;

    // setting N bit
    if(GETNBIT(value, 7) == 0)
        regs->P &= ~(1 << 7);
    else regs->P |= (1 << 7);

    // setting V bit
    if(GETNBIT(value, 6) == 0)
        regs->P &= ~(1 << 6);
    else regs->P |= (1 << 6);
}

void ADC(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    regs->A += value + GETNBIT(regs->P, 0);

    if (regs->A >> 0xff)
        regs->P |= 1;
    else regs->P &= ~1;

    set_PC_NZ(regs, regs->A);

    // ignore decimal mode
}

void SBC(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    regs->A -= value + ~GETNBIT(regs->P, 0);

    if (regs->A >> 0xff)
        regs->P |= 1;
    else regs->P &= ~1;

    set_PC_NZ(regs, regs->A);

    // ignore decimal mode
}

// comparison commands

static void compare(uint16_t loc, Mode m, reg_t* regs, uint8_t axy) {
    uint8_t value = axy - m_read(loc, m, regs);
    set_PC_NZ(regs, value);

    if(value > 0x80)
        regs->P &= ~1;
    else regs->P |= 1;
}

void CMP(uint16_t loc, Mode m, reg_t* regs) {
    compare(loc, m, regs, regs->A);
}

void CPX(uint16_t loc, Mode m, reg_t* regs) {
    compare(loc, m, regs, regs->X);
}

void CPY(uint16_t loc, Mode m, reg_t* regs) {
    compare(loc, m, regs, regs->Y);
}