#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include "cmd.h"

#define GETNBIT(val, n) ((val >> n) & 1)
#define SETNBIT(val, n, b) (b==0?(val &= ~(1 << n)):(val |= (1 << n)))


void set_PC_NZ(state_t* regs, const uint8_t value);

// Register transform commands
Status TAX(arg_t args, state_t* regs);
Status TAY(arg_t args, state_t* regs);
Status TXA(arg_t args, state_t* regs);
Status TYA(arg_t args, state_t* regs);

// Status flag commands
Status CLC(arg_t args, state_t* regs);
Status CLD(arg_t args, state_t* regs);
Status CLI(arg_t args, state_t* regs);
Status CLV(arg_t args, state_t* regs);

Status SEC(arg_t args, state_t* regs);
Status SED(arg_t args, state_t* regs);
Status SEI(arg_t args, state_t* regs);

#endif