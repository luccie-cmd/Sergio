#include "cpu.h"


void print_cpu(const CPU *cpu){
    printf("Bus:\n");
    printf("    ");
    for(int i = 0; i < 8; ++i){
        printf("%d ", cpu->bus.bus[i]);
    }
    printf("\n");
    printf("a = 0x%x\n", cpu->registerA);
    printf("b = 0x%x\n", cpu->registerB);
    for(int16_t i = 0; i < INT16_MAX; ++i){
        if(cpu->memory[i] != 0){
            printf("mem[%d] = 0x%x\n", i, cpu->memory[i]);
        }
    }
}
