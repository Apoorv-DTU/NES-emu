#include "alu.h"

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
    if((value & regs->A) == 0)
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

    if (regs->A > 0xff)
        regs->P |= 1;
    else regs->P &= ~1;

    set_PC_NZ(regs, regs->A);

    // ignore decimal mode
}

void SBC(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs);
    regs->A -= value + ~GETNBIT(regs->P, 0);

    if (regs->A > 0xff)
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

void INC(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs) + 1;
    set_PC_NZ(regs, value);
    m_write(loc, m, value, *regs);
}

void INX(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs) + 1;
    set_PC_NZ(regs, value);
    regs->X = value;
}

void INY(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs) + 1;
    set_PC_NZ(regs, value);
    regs->Y = value;
}

void DEC(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs) - 1;
    set_PC_NZ(regs, value);
    m_write(loc, m, value, *regs);
}

void DEX(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs) - 1;
    set_PC_NZ(regs, value);
    regs->X = value;
}

void DEY(uint16_t loc, Mode m, reg_t* regs) {
    uint8_t value = m_read(loc, m, regs) - 1;
    set_PC_NZ(regs, value);
    regs->Y = value;
}

// shift and rotate commands
void ASL(uint16_t loc, Mode m, reg_t* regs) {
    
    char b;
    
    if(m == ACC) {
        b = GETNBIT(regs->A, 7);
        regs->A <<= 1;
        set_PC_NZ(regs, regs->A);
    } else {
        uint8_t value = m_read(loc, m, regs) << 1;
        b = GETNBIT(value, 7);
        m_write(loc, m, value, *regs);
        set_PC_NZ(regs, value);
    }

    SETNBIT(regs->P, 0, b);
}

void ASR(uint16_t loc, Mode m, reg_t* regs) {
    
    char b;

    if(m == ACC) {
        b = GETNBIT(regs->A, 0);
        regs->A >>= 1;
        set_PC_NZ(regs, regs->A);
    } else {
        uint8_t value = m_read(loc, m, regs) >> 1;
        b = GETNBIT(value, 0);
        m_write(loc, m, value, *regs);
        set_PC_NZ(regs, value);
    }

    SETNBIT(regs->P, 0, b);
}

static uint8_t rotate_l(uint8_t x) {
    char b = GETNBIT(x, 7);
    uint8_t r = x << 1;

    if(b == 1)
        r |= 1;
    else r &= ~1;

    return r;
}

static uint8_t rotate_r(uint8_t x) {
    char b = GETNBIT(x, 0);
    uint8_t r = x >> 1;

    if(b == 1)
        r |= (1 << 7);
    else r &= ~(1 << 7);

    return r;
}

void ROL(uint16_t loc, Mode m, reg_t* regs) {
    
    char b;
    
    if(m == ACC) {
        b = GETNBIT(regs->A, 7);
        regs->A = rotate_l(regs->A);
        set_PC_NZ(regs, regs->A);
    } else {
        uint8_t value = rotate_l(m_read(loc, m, regs));
        b = GETNBIT(value, 7);
        m_write(loc, m, value, *regs);
        set_PC_NZ(regs, value);
    }

    SETNBIT(regs->P, 0, b);
}

void ROR(uint16_t loc, Mode m, reg_t* regs) {
    
    char b;

    if(m == ACC) {
        b = GETNBIT(regs->A, 0);
        regs->A = rotate_r(regs->A);
        set_PC_NZ(regs, regs->A);
    } else {
        uint8_t value = rotate_r(m_read(loc, m, regs));
        b = GETNBIT(value, 0);
        m_write(loc, m, value, *regs);
        set_PC_NZ(regs, value);
    }

    SETNBIT(regs->P, 0, b);
}