#include "mem.h"
#include "registers.h"

static uint8_t mem[0x10000] = {0};

uint8_t m_read(uint16_t loc, Mode m, reg_t* regs) {
    
    uint8_t value;

    switch(m) {
        case ACC:
            value = regs->A;
        break;

        case IMM:
            value = loc;
        break;

        case ZER:
            value = mem[loc];
        break;

        case ZEX:
            // addition wraps if result > 0xff
            value = mem[(loc+(regs->X)) % 0xff];
        break;

        case ZEY:
            // addition wraps if result > 0xff
            value = mem[(loc+(regs->Y)) % 0xff];
        break;

        case REL:
            value = mem[loc+(regs->PC)];
        break;
        
        case ABS:
            value = mem[loc];
        break;

        case ABX:
            value = mem[loc+(regs->X)];
        break;

        case ABY:
            value = mem[loc+(regs->Y)];
        break;

        case IND:
            // little endian
            value = mem[(mem[loc+1] << 8) + mem[loc]];
        break;

        case IDX:
            value = m_read((loc+(regs->X)) % 0xff, IND, regs);
        break;

        case IDY:
            value = mem[(mem[loc+1] << 8) + mem[loc]+(regs->Y)];
        break;
    }

    set_PC_NZ(regs, value);

    return value;
}

void m_write(uint16_t loc, Mode m, uint8_t value, const reg_t regs) {

    switch(m) {
        case ZER:
            mem[loc] = value;
        break;

        case ZEX:
            mem[(loc + (regs.X)) % 0xff] = value;
        break;

        case ZEY:
            mem[(loc + (regs.Y)) % 0xff] = value;
        break;

        case ABS:
            mem[loc] = value;
        break;

        case ABX:
            mem[loc + (regs.X)] = value;
        break;

        case ABY:
            mem[loc + (regs.Y)] = value;
        break;

        case IDX:
            mem[(mem[loc + (regs.X) + 1] << 8) + mem[loc + (regs.X)]] = value;
        break;

        case IDY:
            mem[(mem[loc+1] << 8) + mem[loc] + (regs.Y)] = value;
        break;

        default:
            // invalid Mode for writing to memory
        break;
    }
}

void LDA(uint16_t loc, Mode m, reg_t* regs) {
    regs->A = m_read(loc, m, regs);
    set_PC_NZ(regs->A);
}

void LDX(uint16_t loc, Mode m, reg_t* regs) {
    regs->X = m_read(loc, m, regs);
    set_PC_NZ(regs->X);
}

void LDY(uint16_t loc, Mode m, reg_t* regs) {
    regs->Y = m_read(loc, m, regs);
    set_PC_NZ(regs->Y);
}

void STA(uint16_t loc, Mode m, const reg_t regs) {
    m_write(loc, m, regs.A, regs);
}

void STX(uint16_t loc, Mode m, const reg_t regs) {
    m_write(loc, m, regs.X, regs);
}

void STY(uint16_t loc, Mode m, const reg_t regs) {
    m_write(loc, m, regs.Y, regs);
}