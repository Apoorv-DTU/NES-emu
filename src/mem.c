#include "mem.h"

uint16_t resolv_indirect(uint8_t addr, state_t* state, uint8_t x, uint8_t y) {
    uint16_t low_addr = (addr + x) % 0xff; 
    
    uint8_t low = state->mem[low_addr];
    uint8_t high = state->mem[low_addr+1];
    
    uint8_t norm_addr = (high << 8) + low;

    return norm_addr + y;
}

uint16_t resolv_abs(uint8_t addr_l, uint8_t addr_h, uint8_t offset) {
    return addr_l + (addr_h << 8) + offset;
}

uint16_t resolv_zer(uint8_t addr, uint8_t offset) {
    return (uint16_t)((addr + offset) % 0xff);
}

#define LD_AB(__Reg, __Off) uint16_t addr = resolv_abs(G_LOW8(args), G_HIGH8(args), __Off); \
                            state->__Reg = state->mem[addr];                                \
                                                                                            \
                            if((addr % 0x0fff) == (state->PC % 0x0fff))                     \
                                return SUCCESS;                                             \
                            else return CROSS_PAGE;             

#define LD_ZE(__Reg, __Off) uint16_t addr = resolv_zer(G_LOW8(args), __Off);  \
                            state->__Reg = state->mem[addr];                  \
                            return SUCCESS;

#define LD_IN(__Reg, __OffX, __OffY) uint16_t addr = resolv_indirect(G_LOW8(args), state , __OffX, __OffY); \
                                     state->__Reg = state->mem[addr];                                       \
                                                                                                            \
                                     if((addr % 0x0fff) == (state->PC % 0x0fff))                            \
                                         return SUCCESS;                                                    \
                                     else return CROSS_PAGE;

#define ST_AB(__Reg, __Off) uint16_t addr = resolv_abs(G_LOW8(args), G_HIGH8(args), __Off); \
                            state->mem[addr] = state->__Reg;                                \
                            return SUCCESS;

#define ST_ZE(__Reg, __Off) uint16_t addr = resolv_zer(G_LOW8(args), __Off); \
                            state->mem[addr] = state->__Reg;                \
                            return SUCCESS;

Status LDA_IMM(arg_t args, state_t* state) {
    state->A = G_LOW8(args);
    return SUCCESS;
}
Status LDA_ABS(arg_t args, state_t* state) { LD_AB(A, 0) }
Status LDA_ABX(arg_t args, state_t* state) { LD_AB(A, state->X) }
Status LDA_ABY(arg_t args, state_t* state) { LD_AB(A, state->Y) }
Status LDA_ZER(arg_t args, state_t* state) { LD_ZE(A, 0) }
Status LDA_ZEX(arg_t args, state_t* state) { LD_ZE(A, state->X) }
Status LDA_ZEY(arg_t args, state_t* state) { LD_ZE(A, state->Y) }
Status LDA_IND(arg_t args, state_t* state) { LD_IN(A, 0, 0) }
Status LDA_IDX(arg_t args, state_t* state) { LD_IN(A, state->X, 0) }
Status LDA_IDY(arg_t args, state_t* state) { LD_IN(A, 0, state->Y) }

Status LDX_IMM(arg_t args, state_t* state) {
    state->X = G_LOW8(args);
    return SUCCESS;
}
Status LDX_ABS(arg_t args, state_t* state) { LD_AB(X, 0) }
Status LDX_ABY(arg_t args, state_t* state) { LD_AB(X, state->Y) }
Status LDX_ZER(arg_t args, state_t* state) { LD_ZE(X, 0) }
Status LDX_ZEY(arg_t args, state_t* state) { LD_ZE(X, state->Y) }

Status LDY_IMM(arg_t args, state_t* state) {
    state->Y = G_LOW8(args);
    return SUCCESS;
}
Status LDY_ABS(arg_t args, state_t* state) { LD_AB(Y, 0) }
Status LDY_ABX(arg_t args, state_t* state) { LD_AB(Y, state->X) }
Status LDY_ZER(arg_t args, state_t* state) { LD_ZE(Y, 0) }
Status LDY_ZEX(arg_t args, state_t* state) { LD_ZE(Y, state->X) }


Status STA_ABS(arg_t args, state_t* state) { ST_AB(A, 0) }
Status STA_ABX(arg_t args, state_t* state) { ST_AB(A, state->X) }
Status STA_ABY(arg_t args, state_t* state) { ST_AB(A, state->Y) }
Status STA_ZER(arg_t args, state_t* state) { ST_ZE(A, 0) }
Status STA_ZEX(arg_t args, state_t* state) { ST_ZE(A, state->X) }
Status STA_IDX(arg_t args, state_t* state) {
    uint16_t addr = resolv_indirect(G_LOW8(args), state, state->X, 0);
    state->mem[addr] = state->A;
    return SUCCESS;
}
Status STA_IDY(arg_t args, state_t* state) {
    uint16_t addr = resolv_indirect(G_LOW8(args), state, 0, state->Y);
    state->mem[addr] = state->A;
    return SUCCESS;
}

Status STX_ABS(arg_t args, state_t* state) { ST_AB(X, 0) }
Status STX_ZER(arg_t args, state_t* state) { ST_ZE(X, 0) }
Status STX_ZEY(arg_t args, state_t* state) { ST_ZE(X, state->Y) }

Status STY_ABS(arg_t args, state_t* state) { ST_AB(Y, 0) }
Status STY_ZER(arg_t args, state_t* state) { ST_ZE(Y, 0) }
Status STY_ZEX(arg_t args, state_t* state) { ST_ZE(Y, state->X) }