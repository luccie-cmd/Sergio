#ifndef _CPU_H
#define _CPU_H
#include <stdio.h>
#include "types.h"
#include "insts.h"

typedef struct{
    int bus[8];
} Bus;

typedef struct{
    int C;
    int Z;
} Flags;

typedef struct{
    BYTE registerA;
    BYTE registerB;
    BYTE memory[INT16_MAX];
    Bus bus;
    WORD stack[255];
    BYTE SP;
    Flags flags;
} CPU;

void print_cpu(const CPU *cpu);

#endif // _CPU_H