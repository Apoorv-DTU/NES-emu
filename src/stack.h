#ifndef STACK_H
#define STACK_H

#include "registers.h"

void TSX(reg_t* regs);
void TXS(reg_t* regs);

void PHA(reg_t* regs);
void PLA(reg_t* regs);

void PHP(reg_t* regs);
void PLP(reg_t* regs);


#endif