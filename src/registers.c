#include "registers.h"

void set_PC_NZ(state_t* state, const uint8_t value) {
    
    if(value > 0x80)
        state->P |= (1 << 7);
    else if (value == 0)
        state->P |= 2;
    else {
        state->P &= ~(1 << 7);
        state->P &= ~2;
    }
}

Status TAX(arg_t args, state_t* state) {
    state->X = state->A;
    set_PC_NZ(state, state->X);
    return SUCCESS;
}

Status TAY(arg_t args, state_t* state) {
    state->Y = state->A;
    set_PC_NZ(state, state->Y);
    return SUCCESS;
}

Status TXA(arg_t args, state_t* state) {
    state->A = state->X;
    set_PC_NZ(state, state->X);
    return SUCCESS;
}

Status TYA(arg_t args, state_t* state) {
    state->A = state->Y;
    set_PC_NZ(state, state->Y);
    return SUCCESS;
}

Status CLC(arg_t args, state_t* state) {
    state->P &= ~1;
    return SUCCESS;
}

Status CLI(arg_t args, state_t* state) {
    state->P &= ~4;
    return SUCCESS;
}

Status CLD(arg_t args, state_t* state) {
    state->P &= ~8;
    return SUCCESS;
}

Status CLV(arg_t args, state_t* state) {
    state->P &= ~64;
    return SUCCESS;
}

Status SEC(arg_t args, state_t* state) {
    state->P |= 1;
    return SUCCESS;
}

Status SEI(arg_t args, state_t* state) {
    state->P |= 4;
    return SUCCESS;
}

Status SED(arg_t args, state_t* state) {
    state->P |= 8;
    return SUCCESS;
}