#ifndef MEM_H
#define MEM_H

#include "registers.h"
#include "cmd.h"

enum addr_mode { ACC, IMM, ZER, ZEX, ZEY, REL, 
            ABS, ABX, ABY, IND, IDX, IDY 
            };

typedef enum addr_mode Mode;

uint16_t resolv_indirect(uint8_t addr, state_t* state, uint8_t x, uint8_t y);

uint16_t resolv_abs(uint8_t addr_l, uint8_t addr_h, uint8_t offset);
uint16_t resolv_zer(uint8_t addr_l, uint8_t offset);

// LDA commands
Status LDA_IMM(arg_t args, state_t* state);

Status LDA_ABS(arg_t args, state_t* state);
Status LDA_ABX(arg_t args, state_t* state);
Status LDA_ABY(arg_t args, state_t* state);

Status LDA_ZER(arg_t args, state_t* state);
Status LDA_ZEX(arg_t args, state_t* state);
Status LDA_ZEY(arg_t args, state_t* state);

Status LDA_IND(arg_t args, state_t* state);
Status LDA_IDY(arg_t args, state_t* state);
Status LDA_IDX(arg_t args, state_t* state);

// LDX commands
Status LDX_IMM(arg_t args, state_t* state);

Status LDX_ZER(arg_t args, state_t* state);
Status LDX_ZEY(arg_t args, state_t* state);

Status LDX_ABS(arg_t args, state_t* state);
Status LDX_ABY(arg_t args, state_t* state);

// LDY commands
Status LDY_IMM(arg_t args, state_t* state);

Status LDY_ZER(arg_t args, state_t* state);
Status LDY_ZEX(arg_t args, state_t* state);

Status LDY_ABS(arg_t args, state_t* state);
Status LDY_ABX(arg_t args, state_t* state);

// STA commands
Status STA_ZER(arg_t args, state_t* state);
Status STA_ZEX(arg_t args, state_t* state);

Status STA_ABS(arg_t args, state_t* state);
Status STA_ABX(arg_t args, state_t* state);
Status STA_ABY(arg_t args, state_t* state);

Status STA_IDX(arg_t args, state_t* state);
Status STA_IDY(arg_t args, state_t* state);

// STX commands
Status STX_ABS(arg_t args, state_t* state);
Status STX_ZEY(arg_t args, state_t* state);
Status STX_ZER(arg_t args, state_t* state);

// STY commands
Status STY_ABS(arg_t args, state_t* state);
Status STY_ZER(arg_t args, state_t* state);
Status STY_ZEX(arg_t args, state_t* state);

#endif