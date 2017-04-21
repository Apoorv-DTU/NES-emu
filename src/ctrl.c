#include "ctrl.h"

Status JMP_IMM(arg_t args, state_t *state) {
    state->PC = args;
    return SUCCESS;
}

Status JMP_ABS(arg_t args, state_t *state) {
    state->PC = state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)];
    return SUCCESS;
}


Status JSR(arg_t args, state_t* state) {
    push(G_HIGH8(state->PC+2));
    push(G_LOW8(state->PC+2));
    state->PC = args;
    return SUCCESS;
}

Status RTS(arg_t args, state_t* state) {
    uint8_t low = pop(state);
    uint8_t high = pop(state);
    state->PC = (high << 8) + low;
    return SUCCESS;
}

inline Status branch_flag(arg_t args, state_t* state, char bit, char set) {
    if(GETNBIT(state->P, bit) == set) {
        uint8_t addr = state->PC;
        state->PC += G_LOW8(args);
        if((addr % 0xfff) == (state->PC % 0xfff))return BRANCH; else return BRANCH_PAGE;
    } else return SUCCESS;
}

Status BCC(arg_t args, state_t* state) {
    return branch_flag(args, state, 0, 0);
}

void BCS(arg_t args, state_t* state) {
    return branch_flag(args, state, 0, 1);
}

void BNE(arg_t args, state_t* state) {
    return branch_flag(args, state, 1, 0);
}

void BEQ(arg_t args, state_t* state) {
    return branch_flag(args, state, 1, 1);
}

void BVC(arg_t args, state_t* state) {
    return branch_flag(args, state, 6, 0);
}

void BVS(arg_t args, state_t* state) {
    return branch_flag(args, state, 6, 1);
}

bool BPL(arg_t args, state_t* state) {
    return branch_flag(args, state, 7, 0);
}

void BMI(arg_t args, state_t* state) {
    return branch_flag(args, state, 7, 1);
}

Status BRK(arg_t args, state_t* state) {
    push(state->P, state);
    JSR(INT_ADDR, state);
    return SUCCESS;
}

Status RTI(arg_t args, state_t* state) {
    state->P = pop(state);
    RTS(0, state);
    return SUCCESS;
}