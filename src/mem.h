#ifndef MEM_H
#define MEM_H

#include "registers.h"

enum addr_mode { ACC, IMM, ZER, ZEX, ZEY, REL, 
            ABS, ABX, ABY, IND, IDX, IDY 
            };

typedef enum addr_mode Mode;

uint8_t m_read(uint16_t loc, Mode m, reg_t* regs);
void m_write(uint16_t loc, uint8_t value, Mode m, const reg_t regs);

#endif