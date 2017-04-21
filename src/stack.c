#include "stack.h"

inline void push(state_t* state, uint8_t value) {
    mem[state->S--] = value;
}

inline uint8_t pop(state_t* state) {
    return mem[state->S++];
}

Status TSX(arg_t args, state_t* state) {
    state->X = state->S;
    set_PC_NZ(state, state->X);
    return SUCCESS;
}

Status TXS(arg_t args, state_t* state) {
    state->S = state->X;
    return SUCCESS;
}

Status PHA(arg_t args, state_t* state) {
    state->mem[0x100 + state->S] = state->A;
    state->S--;
    return SUCCESS;
}

Status PLA(arg_t args, state_t* state) {
    state->A = state->mem[0x100 + state->S];
    state->S++;
    return SUCCESS;
}

Status PHP(arg_t args, state_t* state) {
    state->mem[0x100 + state->S] = state->P;
    state->S--;
    return SUCCESS;
}

Status PLP(arg_t args, state_t* state) {
    state->P = state->mem[0x100 + state->S];
    state->S++;
    return SUCCESS;
}