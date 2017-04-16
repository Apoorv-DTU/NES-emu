#ifndef ALU_H
#define ALU_H

#include "cmd.h"
#include "registers.h"

Status AND_IMM(arg_t args, state_t* state);
Status AND_ZER(arg_t args, state_t* state);
Status AND_ZEX(arg_t args, state_t* state);
Status AND_ABS(arg_t args, state_t* state);
Status AND_ABX(arg_t args, state_t* state);
Status AND_ABY(arg_t args, state_t* state);
Status AND_IDX(arg_t args, state_t* state);
Status AND_IDY(arg_t args, state_t* state);

Status EOR_IMM(arg_t args, state_t* state);
Status EOR_ZER(arg_t args, state_t* state);
Status EOR_ZEX(arg_t args, state_t* state);
Status EOR_ABS(arg_t args, state_t* state);
Status EOR_ABX(arg_t args, state_t* state);
Status EOR_ABY(arg_t args, state_t* state);
Status EOR_IDX(arg_t args, state_t* state);
Status EOR_IDY(arg_t args, state_t* state);

Status ORA_IMM(arg_t args, state_t* state);
Status ORA_ZER(arg_t args, state_t* state);
Status ORA_ZEX(arg_t args, state_t* state);
Status ORA_ABS(arg_t args, state_t* state);
Status ORA_ABX(arg_t args, state_t* state);
Status ORA_ABY(arg_t args, state_t* state);
Status ORA_IDX(arg_t args, state_t* state);
Status ORA_IDY(arg_t args, state_t* state);

inline Status BIT(uint8_t value, state_t* state);
Status BIT_ZER(arg_t args, state_t* state);
Status BIT_ABS(arg_t args, state_t* state);

Status ADC_IMM(arg_t args, state_t* state);
Status ADC_ZER(arg_t args, state_t* state);
Status ADC_ZEX(arg_t args, state_t* state);
Status ADC_ABS(arg_t args, state_t* state);
Status ADC_ABX(arg_t args, state_t* state);
Status ADC_ABY(arg_t args, state_t* state);
Status ADC_IDX(arg_t args, state_t* state);
Status ADC_IDY(arg_t args, state_t* state);

Status SBC_IMM(arg_t args, state_t* state);
Status SBC_ZER(arg_t args, state_t* state);
Status SBC_ZEX(arg_t args, state_t* state);
Status SBC_ABS(arg_t args, state_t* state);
Status SBC_ABX(arg_t args, state_t* state);
Status SBC_ABY(arg_t args, state_t* state);
Status SBC_IDX(arg_t args, state_t* state);
Status SBC_IDY(arg_t args, state_t* state);

inline Status compare(uint8_t v, state_t* state, uint8_t axy);
Status CMP_IMM(arg_t args, state_t* state);
Status CMP_ZER(arg_t args, state_t* state);
Status CMP_ZEX(arg_t args, state_t* state);
Status CMP_ABS(arg_t args, state_t* state);
Status CMP_ABX(arg_t args, state_t* state);
Status CMP_ABY(arg_t args, state_t* state);
Status CMP_IDX(arg_t args, state_t* state);
Status CMP_IDY(arg_t args, state_t* state);

Status CPX_IMM(arg_t args, state_t* state);
Status CPX_ZER(arg_t args, state_t* state);
Status CPX_ZEX(arg_t args, state_t* state);
Status CPX_ABS(arg_t args, state_t* state);
Status CPX_ABX(arg_t args, state_t* state);
Status CPX_ABY(arg_t args, state_t* state);
Status CPX_IDX(arg_t args, state_t* state);
Status CPX_IDY(arg_t args, state_t* state);

Status CPY_IMM(arg_t args, state_t* state);
Status CPY_ZER(arg_t args, state_t* state);
Status CPY_ZEX(arg_t args, state_t* state);
Status CPY_ABS(arg_t args, state_t* state);
Status CPY_ABX(arg_t args, state_t* state);
Status CPY_ABY(arg_t args, state_t* state);
Status CPY_IDX(arg_t args, state_t* state);
Status CPY_IDY(arg_t args, state_t* state);

inline Status INC_ZER(arg_t args, state_t* state);
inline Status INC_ZEX(arg_t args, state_t* state);
inline Status INC_ABS(arg_t args, state_t* state);
inline Status INC_ABX(arg_t args, state_t* state);

Status INX(arg_t args, state_t* state);
Status INY(arg_t args, state_t* state);

inline Status DEC_ZER(arg_t args, state_t* state);
inline Status DEC_ZEX(arg_t args, state_t* state);
inline Status DEC_ABS(arg_t args, state_t* state);
inline Status DEC_ABX(arg_t args, state_t* state);

Status DEX(arg_t args, state_t* state);
Status DEY(arg_t args, state_t* state);

inline Status shift_r(uint8_t* v, state_t* state);
Status LSR_ACC(arg_t args, state_t* state);
Status LSR_ZER(arg_t args, state_t* state);
Status LSR_ZEX(arg_t args, state_t* state);
Status LSR_ABS(arg_t args, state_t* state);
Status LSR_ABX(arg_t args, state_t* state);

inline Status shift_l(uint8_t* v, state_t* state);
Status ASL_ACC(arg_t args, state_t* state);
Status ASL_ZER(arg_t args, state_t* state);
Status ASL_ZEX(arg_t args, state_t* state);
Status ASL_ABS(arg_t args, state_t* state);
Status ASL_ABX(arg_t args, state_t* state);

inline Status rotate_r(uint8_t* v, state_t* state);
Status ROR_ACC(arg_t args, state_t* state);
Status ROR_ZER(arg_t args, state_t* state);
Status ROR_ZEX(arg_t args, state_t* state);
Status ROR_ABS(arg_t args, state_t* state);
Status ROR_ABX(arg_t args, state_t* state);

inline Status rotate_l(uint8_t* v, state_t* state);
Status ROL_ACC(arg_t args, state_t* state);
Status ROL_ZER(arg_t args, state_t* state);
Status ROL_ZEX(arg_t args, state_t* state);
Status ROL_ABS(arg_t args, state_t* state);
Status ROL_ABX(arg_t args, state_t* state);

#endif