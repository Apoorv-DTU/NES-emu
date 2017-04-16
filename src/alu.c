#include "alu.h"

#define CHECK_PAGE_CROSS if((addr % 0xfff) == (state->PC % 0xfff))return SUCCESS; else return CROSS_PAGE

#define gen_AND(MODE, get_addr, ret) Status AND_##MODE (arg_t args, state_t* state) { \
                       uint16_t addr = get_addr; \
                       uint8_t value = state->mem[addr]; \
                       state->A &= value; \
                       set_PC_NZ(state, value); \
                       ret; }

#define gen_EOR(MODE, get_addr, ret) Status EOR_##MODE (arg_t args, state_t* state) { \
                       uint16_t addr = get_addr; \
                       uint8_t value = state->mem[addr]; \
                       state->A ^= value; \
                       set_PC_NZ(state, value); \
                       ret; }

#define gen_ORA(MODE, get_addr, ret) Status ORA_##MODE (arg_t args, state_t* state) { \
                       uint16_t addr = get_addr; \
                       uint8_t value = state->mem[addr]; \
                       state->A |= value; \
                       set_PC_NZ(state, value); \
                       ret; }
//AND commands
Status AND_IMM(arg_t args, state_t* state) {
    state->A &= G_LOW8(args);
    set_PC_NZ(state, state->A);
    return SUCCESS;
}

gen_AND(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)

gen_AND(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_AND(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_AND(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_AND(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_AND(IDX,
        resolv_indirect(G_LOW8(args), state, state->X, 0),
        return SUCCESS)

gen_AND(IDY,
        resolv_indirect(G_LOW8(args), state, 0, state->Y),
        CHECK_PAGE_CROSS)

//EOR commands
Status EOR_IMM(arg_t args, state_t* state) {
    state->A ^= G_LOW8(args);
    set_PC_NZ(state, state->A);
    return SUCCESS;
}

gen_EOR(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)

gen_EOR(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_EOR(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_EOR(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_EOR(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_EOR(IDX,
        resolv_indirect(G_LOW8(args), state, state->X, 0),
        return SUCCESS)

gen_EOR(IDY,
        resolv_indirect(G_LOW8(args), state, 0, state->Y),
        CHECK_PAGE_CROSS)

//ORA commands
Status ORA_IMM(arg_t args, state_t* state) {
    state->A |= G_LOW8(args);
    set_PC_NZ(state, state->A);
    return SUCCESS;
}

gen_ORA(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)

gen_ORA(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_ORA(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_ORA(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_ORA(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_ORA(IDX,
        resolv_indirect(G_LOW8(args), state, state->X, 0),
        return SUCCESS)

gen_ORA(IDY,
        resolv_indirect(G_LOW8(args), state, 0, state->Y),
        CHECK_PAGE_CROSS)

inline Status BIT(uint8_t value, state_t* state) {
    if((value & state->A) == 0)
        state->P |= 2;
    else state->P &= ~2;

    // setting N bit
    if(GETNBIT(value, 7) == 0)
        state->P &= ~(1 << 7);
    else state->P |= (1 << 7);

    // setting V bit
    if(GETNBIT(value, 6) == 0)
        state->P &= ~(1 << 6);
    else state->P |= (1 << 6);

    return SUCCESS;
}

Status BIT_ABS(arg_t args, state_t* state) {
    return BIT(state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)], state);
}

Status BIT_ZER(arg_t args, state_t* state) {
    return BIT(state->mem[resolv_zer(G_LOW8(args), 0)], state);
}

#define gen_ADC(MODE, get_addr, ret) Status ADC_##MODE(arg_t args, state_t* state) { \
                    uint8_t addr = get_addr; \
                    uint8_t value = state->mem[addr]; \
                    \
                    if(GETNBIT(state->P, 3)) { \
                        state->A += 10 * (value >> 4) + (value & 0x0f) + GETNBIT(state->P, 0); \
                    } else { \
                        state->A += value + GETNBIT(state->P, 0); \
                    } \
                    \
                    if (state->A > 0xff) \
                        state->P |= 1; \
                    else state->P &= ~1; \
                    set_PC_NZ(state, state->A); \
                    ret;\
                }

Status ADC_IMM(arg_t args, state_t* state) {
    uint8_t value = G_LOW8(args);
    if(GETNBIT(state->P, 3)) {
        state->A += 10 * (value >> 4) + (value & 0x0f) + GETNBIT(state->P, 0);
    } else {
        state->A += value + GETNBIT(state->P, 0);
    }

    if (state->A > 0xff)
        state->P |= 1;
    else state->P &= ~1;

    set_PC_NZ(state, state->A);
    return SUCCESS;
}

gen_ADC(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_ADC(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_ADC(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)

gen_ADC(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_ADC(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_ADC(IDX,
        resolv_indirect(G_LOW8(args), state, state->X, 0),
        return SUCCESS)

gen_ADC(IDY,
        resolv_indirect(G_LOW8(args), state, 0, state->Y),
        CHECK_PAGE_CROSS)

#define gen_SBC(MODE, get_addr, ret) Status SBC_##MODE(arg_t args, state_t* state) { \
                    uint8_t addr = get_addr; \
                    uint8_t value = state->mem[addr]; \
                    \
                    if(GETNBIT(state->P, 3)) { \
                        state->A += 10 * (value >> 4) + (value & 0x0f) + GETNBIT(state->P, 0); \
                    } else { \
                        state->A -= value + ~GETNBIT(state->P, 0); \
                    } \
                    \
                    if (state->A > 0xff) \
                        state->P |= 1; \
                    else state->P &= ~1; \
                    set_PC_NZ(state, state->A); \
                    ret;\
                }

Status SBC_IMM(arg_t args, state_t* state) {
    uint8_t value = G_LOW8(args);
    if(GETNBIT(state->P, 3)) {
        state->A += 10 * (value >> 4) + (value & 0x0f) + GETNBIT(state->P, 0);
    } else {
        state->A -= value + ~GETNBIT(state->P, 0);
    }

    if (state->A > 0xff)
        state->P |= 1;
    else state->P &= ~1;

    set_PC_NZ(state, state->A);
    return SUCCESS;
}

gen_SBC(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_SBC(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_SBC(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)

gen_SBC(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_SBC(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_SBC(IDX,
        resolv_indirect(G_LOW8(args), state, state->X, 0),
        return SUCCESS)

gen_SBC(IDY,
        resolv_indirect(G_LOW8(args), state, 0, state->Y),
        CHECK_PAGE_CROSS)


// comparison commands

#define gen_CMP(MODE, get_addr, ret) Status CMP_##MODE(arg_t args, state_t* state) { \
                                    uint8_t addr = get_addr; \
                                    uint8_t value = state->A - state->mem[addr]; \
                                    set_PC_NZ(state, value); \
                                    if(value > 0x80) \
                                        state->P &= ~1; \
                                    else state->P |= 1; \
                                    ret; \
                                    }

#define gen_CPX(MODE, get_addr, ret) Status CPX_##MODE(arg_t args, state_t* state) { \
                                    uint8_t addr = get_addr; \
                                    uint8_t value = state->X - state->mem[addr]; \
                                    set_PC_NZ(state, value); \
                                    if(value > 0x80) \
                                        state->P &= ~1; \
                                    else state->P |= 1; \
                                    ret; \
                                    }

#define gen_CPY(MODE, get_addr, __ret) Status CPY_##MODE(arg_t args, state_t* state) { \
                                    uint8_t addr = get_addr; \
                                    uint8_t value = state->Y - state->mem[addr]; \
                                    set_PC_NZ(state, value); \
                                    if(value > 0x80) \
                                        state->P &= ~1; \
                                    else state->P |= 1; \
                                    __ret; }

inline Status compare(uint8_t v, state_t* state, uint8_t axy) {
    uint8_t value = axy - v;
    set_PC_NZ(state, value);

    if(value > 0x80)
        state->P &= ~1;
    else state->P |= 1;
    return SUCCESS;
}

Status CMP_IMM(arg_t args, state_t* state) {
    return compare(G_LOW8(args), state, state->A);
}

gen_CMP(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_CMP(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_CMP(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)


gen_CMP(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_CMP(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_CMP(IDX,
        resolv_indirect(G_LOW8(args), state, state->X),
        return SUCCESS)

gen_CMP(IDY,
        resolv_indirect(G_LOW8(args), state, state->Y),
        CHECK_PAGE_CROSS)

Status CPX_IMM(arg_t args, state_t* state) {
    return compare(G_LOW8(args), state, state->X);
}

gen_CPX(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_CPX(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_CPX(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)


gen_CPX(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_CPX(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_CPX(IDX,
        resolv_indirect(G_LOW8(args), state, state->X),
        return SUCCESS)

gen_CPX(IDY,
        resolv_indirect(G_LOW8(args), state, state->Y),
        CHECK_PAGE_CROSS)


Status CPY_IMM(arg_t args, state_t* state) {
    return compare(G_LOW8(args), state, state->Y);
}

gen_CPY(ZER,
        resolv_zer(G_LOW8(args), 0),
        return SUCCESS)

gen_CPY(ZEX,
        resolv_zer(G_LOW8(args), state->X),
        return SUCCESS)

gen_CPY(ABS,
        resolv_abs(G_LOW8(args), G_HIGH8(args), 0),
        return SUCCESS)


gen_CPY(ABX,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->X),
        CHECK_PAGE_CROSS)

gen_CPY(ABY,
        resolv_abs(G_LOW8(args), G_HIGH8(args), state->Y),
        CHECK_PAGE_CROSS)

gen_CPY(IDX,
        resolv_indirect(G_LOW8(args), state, state->X),
        return SUCCESS)

gen_CPY(IDY,
        resolv_indirect(G_LOW8(args), state, state->Y),
        CHECK_PAGE_CROSS)

inline Status INC_ZER(arg_t args, state_t* state) {
    set_PC_NZ(state, ++state->mem[resolv_zer(G_LOW8(args), 0)]);
    return SUCCESS;
}

inline Status INC_ZEX(arg_t args, state_t* state) {
    set_PC_NZ(state, ++state->mem[resolv_zer(G_LOW8(args), state->X)]);
    return SUCCESS;
}

inline Status INC_ABS(arg_t args, state_t* state) {
    set_PC_NZ(state, ++state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)]);
    return SUCCESS;
}

inline Status INC_ABX(arg_t args, state_t* state) {
    set_PC_NZ(state, ++state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), state->X)]);
    return SUCCESS;
}


inline Status DEC_ZER(arg_t args, state_t* state) {
    set_PC_NZ(state, --state->mem[resolv_zer(G_LOW8(args), 0)]);
    return SUCCESS;
}

inline Status DEC_ZEX(arg_t args, state_t* state) {
    set_PC_NZ(state, --state->mem[resolv_zer(G_LOW8(args), state->X)]);
    return SUCCESS;
}

inline Status DEC_ABS(arg_t args, state_t* state) {
    set_PC_NZ(state, --state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)]);
    return SUCCESS;
}

inline Status DEC_ABX(arg_t args, state_t* state) {
    set_PC_NZ(state, --state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), state->X)]);
    return SUCCESS;
}

#define INCDECXY(XY, op) { state->XY op; \
                           set_PC_NZ(state, state->XY); \
                           return SUCCESS; }

Status INX(arg_t args, state_t* state)
    INCDECXY(X, ++)

Status INY(arg_t args, state_t* state)
    INCDECXY(Y, ++)

Status DEX(arg_t args, state_t* state)
    INCDECXY(X, --)

Status DEY(arg_t args, state_t* state)
    INCDECXY(Y, --)

inline Status shift_l(uint8_t* v, state_t* state) {
    SETNBIT(state->P, 0, GETNBIT((*v), 7));
    (*v) <<= 1;
    set_PC_NZ(state, (*v));
    return SUCCESS;
}

// shift and rotate commands
Status ASL_ACC(arg_t args, state_t* state) {
    return shift_l(&state->A, state);
}

Status ASL_ZER(arg_t args, state_t* state) {
    return shift_l(&state->mem[resolv_zer(G_LOW8(args), 0)], state);
}

Status ASL_ZEX(arg_t args, state_t* state) {
    return shift_l(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}

Status ASL_ABS(arg_t args, state_t* state) {
    return shift_l(&state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)], state);
}

Status ASL_ABX(arg_t args, state_t* state) {
    return shift_l(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}

inline Status shift_r(uint8_t* v, state_t* state) {
    SETNBIT(state->P, 0, GETNBIT((*v), 0));
    (*v) >>= 1;
    set_PC_NZ(state, (*v));
    return SUCCESS;
}

Status LSR_ACC(arg_t args, state_t* state) {
    return shift_r(&state->A, state);
}

Status LSR_ZER(arg_t args, state_t* state) {
    return shift_r(&state->mem[resolv_zer(G_LOW8(args), 0)], state);
}

Status LSR_ZEX(arg_t args, state_t* state) {
    return shift_r(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}

Status LSR_ABS(arg_t args, state_t* state) {
    return shift_r(&state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)], state);
}

Status LSR_ABX(arg_t args, state_t* state) {
    return shift_r(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}

inline Status rotate_l(uint8_t* v, state_t* state) {
    char c = GETNBIT((*v), 7);
    SETNBIT(state->P, 0, c);
    (*v) <<= 1;
    (*v) += c;
    return SUCCESS;
}

Status ROL_ACC(arg_t args, state_t* state) {
    return rotate_l(&state->A, state);
}

Status ROL_ZER(arg_t args, state_t* state) {
    return rotate_l(&state->mem[resolv_zer(G_LOW8(args), 0)], state);
}

Status ROL_ZEX(arg_t args, state_t* state) {
    return rotate_l(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}

Status ROL_ABS(arg_t args, state_t* state) {
    return rotate_l(&state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)], state);
}

Status ROL_ABX(arg_t args, state_t* state) {
    return rotate_l(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}


inline Status rotate_r(uint8_t* v, state_t* state) {
    char c = GETNBIT((*v), 0);
    SETNBIT(state->P, 0, c);
    (*v) >>= 1;
    SETNBIT((*v), 7, c);
    return SUCCESS;
}

Status ROR_ACC(arg_t args, state_t* state) {
    return rotate_r(&state->A, state);
}

Status ROR_ZER(arg_t args, state_t* state) {
    return rotate_r(&state->mem[resolv_zer(G_LOW8(args), 0)], state);
}

Status ROR_ZEX(arg_t args, state_t* state) {
    return rotate_r(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}

Status ROR_ABS(arg_t args, state_t* state) {
    return rotate_r(&state->mem[resolv_abs(G_LOW8(args), G_HIGH8(args), 0)], state);
}

Status ROR_ABX(arg_t args, state_t* state) {
    return rotate_r(&state->mem[resolv_zer(G_LOW8(args), state->X)], state);
}