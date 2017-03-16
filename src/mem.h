#ifndef MEM_H
#define MEM_H

#include "registers.h"

enum addr_mode { ACC, IMM, ZER, ZEX, ZEY, REL, 
            ABS, ABX, ABY, IND, IDX, IDY 
            };

typedef enum addr_mode Mode;

uint8_t m_read(uint16_t loc, Mode m, reg_t* regs);
void m_write(uint16_t loc, Mode m, uint8_t value, const reg_t regs);

// Load commands
void LDA(uint16_t loc, Mode m, reg_t* regs);
void LDX(uint16_t loc, Mode m, reg_t* regs);
void LDY(uint16_t loc, Mode m, reg_t* regs);

// Store commands
void STA(uint16_t loc, Mode m, const reg_t regs);
void STX(uint16_t loc, Mode m, const reg_t regs);
void STY(uint16_t loc, Mode m, const reg_t regs);

#endif