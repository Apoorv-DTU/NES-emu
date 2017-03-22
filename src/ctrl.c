#include "ctrl.h"

void JMP(uint16_t loc, Mode m, reg_t* regs) {
    uint16_t jmp_loc;
    
    if (m == ABS) {
        jmp_loc = loc;
    } else if (m == IND) {
        jmp_loc = m_read(loc, m, regs);
    } else {
        //Invalid! addressing mode
        jmp_loc = 0;
    }

    regs->PC = jmp_loc;
}

void JSR(uint16_t loc, reg_t* regs) {
    uint8_t high = ((regs->PC)+2) & 0b11110000;
    uint8_t low = ((regs->PC)+2) & 0b00001111;
    m_write(0x0100 + (regs->S--), ABS, high, *regs);
    m_write(0x0100 + (regs->S--), ABS, low, *regs);
    
    regs->PC = loc;

}

void RTS(reg_t* regs) {
    uint8_t low = m_read(0x100 + (regs->S++), ABS, regs);
    uint8_t high = m_read(0x100 + (regs->S++), ABS, regs);
    regs->PC = (high << 8) + low;
}

void BCC(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 0) == 0)
        regs->PC += offset;
}

void BCS(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 0) == 1)
        regs->PC += offset;
}

void BNE(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 1) == 0)
        regs->PC += offset;
}

void BEQ(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 1) == 1)
        regs->PC += offset;
}

void BVC(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 6) == 0)
        regs->PC += offset;
}

void BVS(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 6) == 1)
        regs->PC += offset;
}

void BPL(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 7) == 0)
        regs->PC += offset;
}

void BMI(uint8_t offset, reg_t* regs) {
    if(GETNBIT(regs->P, 7) == 1)
        regs->PC += offset;
}

void NOP() { /* do nothing */ }

void BRK(reg_t* regs) {
    JSR(0xffff, regs);
    m_write(0x100 + (regs->S--), ABS, regs->P ,*regs);
}

void RTI(reg_t* regs) {
    regs->P = m_read(0x100 + (regs->S++), ABS, regs);
    RTS(regs);
}