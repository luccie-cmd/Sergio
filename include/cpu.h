#ifndef _CPU_H
#define _CPU_H
#include <stdio.h>
#include "types.h"

typedef struct{
    int bus[8];
} Bus;

typedef struct{
    uint8_t addr;
    uint8_t ret_addr;
} Call_Address;

typedef struct{
    BYTE registerA;
    BYTE registerB;
    BYTE memory[INT16_MAX];
    Bus bus;
    Call_Address addresses[1024];
    uint16_t addresses_len;
} CPU;

void print_cpu(const CPU *cpu);

#endif // _CPU_H