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