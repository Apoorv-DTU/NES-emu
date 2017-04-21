#ifndef STACK_H
#define STACK_H

#include "registers.h"
#include "mem.h"

extern void push(uint8_t value, state_t* state);
extern uint8_t pop(state_t* state);

Status TSX(arg_t args, state_t* state);
Status TXS(arg_t args, state_t* state);

Status PHA(arg_t args, state_t* state);
Status PLA(arg_t args, state_t* state);

Status PHP(arg_t args, state_t* state);
Status PLP(arg_t args, state_t* state);

#endif