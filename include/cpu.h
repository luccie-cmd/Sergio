#ifndef _CPU_H
#define _CPU_H
#include <stdio.h>
#include "types.h"

typedef struct{
    int bus[8];
} Bus;

typedef struct{
    BYTE registerA;
    BYTE registerB;
    BYTE memory[INT16_MAX];
    Bus bus;
    uint16_t addresses_len;
    WORD stack[255];
    BYTE SP;
} CPU;

void print_cpu(const CPU *cpu);

#endif // _CPU_H