#include <stdio.h>
#include "../src/mem.h"
#include "../src/registers.h"
#include "minunit.h"

// TODO: tests may be faulty, find out better test cases.

/*int tests_run = 0;
reg_t regs;

static char* test_read_acc() {
    regs.A = 0x10;
    mu_assert(m_read(0, ACC, &regs) == 0x10, "does not m_read accumulator.");
    return 0;
}

static char* test_read_imm() {
    mu_assert(m_read(0x11, IMM, &regs) == 0x11, "immediate mode doesnt work.");
    return 0;
}

static char* test_read_write_zer() {
    m_write(0xff, 0x50, ZER, regs);
    mu_assert(m_read(0xff, ZER, &regs) == 0x50, "zero page mode.");
    return 0;
}

static char* test_read_write_zex() {
    
    regs.X = 0x11;
    m_write(0xf0, 0x50, ZEX, regs);
    mu_assert(m_read(0xf0, ZEX, &regs) == 0x50, "zero,X page mode.");
    return 0;
}

static char* test_read_write_zey() {
    
    regs.X = 0x01;
    m_write(0xfc, 0x40, ZEY, regs);
    mu_assert(m_read(0xfc, ZEY, &regs) == 0x40, "zero,Y page mode.");
    return 0;
}

static char* test_read_write_abs() {
    
    m_write(0xabcd, 0x50, ABS, regs);
    mu_assert(m_read(0xabcd, ABS, &regs) == 0x50, "absolute mode.");
    return 0;
}

static char* test_read_write_abx() {
    
    regs.X = 0x05;
    m_write(0xfbcd, 0x70, ABS, regs);
    mu_assert(m_read(0xfbcd, ABS, &regs) == 0x70, "absolute,X mode.");
    return 0;
}

static char* test_read_write_aby() {
    
    regs.Y = 0x04;
    m_write(0xabed, 0x85, ABY, regs);
    mu_assert(m_read(0xabed, ABY, &regs) == 0x85, "absolute,Y mode.");
    return 0;
}

static char* test_read_rel() {
    // TODO
    return 0;
}

static char* test_read_ind() {
    // TODO
    return 0;
}

static char* test_read_write_idx() {
    m_write(0xfcab, 0x60, IDX, regs);
    mu_assert(m_read(0xfcab, IDX, &regs) == 0x60, "IDX mode.");
    return 0;
}

static char* test_read_write_idy() {
    m_write(0x0aed, 0x46, IDY, regs);
    mu_assert(m_read(0x0aed, IDY, &regs) == 0x46, "IDY mode.");
    return 0;
}

static char* mem_tests() {

    mu_run_test(test_read_acc);
    mu_run_test(test_read_imm);
    mu_run_test(test_read_write_zer);
    mu_run_test(test_read_write_zex);
    mu_run_test(test_read_write_zey);
    mu_run_test(test_read_write_abs);
    mu_run_test(test_read_write_abx);
    mu_run_test(test_read_write_aby);
    //mu_run_test(test_read_write_rel); not yet implemented
    //mu_run_test(test_read_write_ind); not yet implemented
    mu_run_test(test_read_write_idx);
    mu_run_test(test_read_write_idy);

    return 0;
}*/

int main() {
 /*   char* result = mem_tests();

    if(result != 0)
        printf("%s\n", result);
    else printf("ALL TESTS ARE GO!!\n");

    printf("\n%d tests run.\n", tests_run);*/
    
    return 0;
}