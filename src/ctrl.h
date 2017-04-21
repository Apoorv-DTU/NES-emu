#ifndef CTRL_H
#define CTRL_H

#include <stdbool.h>
#include "cmd.h"
#include "registers.h"
#include "mem.h"
#include "stack.h"

#define INT_ADDR 0xffff

Status JMP_IMM(arg_t args, state_t *state);
Status JMP_ABS(arg_t args, state_t *state);

Status JSR_ABS(arg_t args, state_t *state);

Status RTS_IMP(arg_t args, state_t *state);

inline Status branch_flag(arg_t args, state_t* state, char bit, char set);
Status BCC_REL(arg_t args, state_t *state);
Status BCS_REL(arg_t args, state_t *state);
Status BNE_REL(arg_t args, state_t *state);
Status BEQ_REL(arg_t args, state_t *state);
Status BVC_REL(arg_t args, state_t *state);
Status BVS_REL(arg_t args, state_t *state);
Status BMI_REL(arg_t args, state_t *state);
Status BPL_REL(arg_t args, state_t *state);

Status BRK(arg_t args, state_t *state);
Status RTI(arg_t args, state_t *state);
Status NOP(arg_t args, state_t *state) {return SUCCESS;}

#endif