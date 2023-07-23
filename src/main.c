#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "types.h"
#include "util.h"
#include "cpu.h"
#include "insts.h"

void execute(CPU *cpu, File program){
    size_t programi = 0;
    if(program.data[programi] != 0 && program.data[programi+1] != 'S' && program.data[programi+2] != 'G' && program.data[programi+3] != 0){
        printf("Invalid file\n");
        exit(1);
    }
    programi = 4;
    while(programi < program.len){
        switch((Inst_Type)program.data[programi]){
            case INST_TYPE_NOP: {
                programi++;
            } break;
            case INST_TYPE_LDA: {
                uint8_t value = program.data[programi+1];
                cpu->registerA = value;
                programi+=2;
            } break;
            case INST_TYPE_STA: {
                uint8_t msb = program.data[programi+1];
                uint8_t lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                cpu->memory[combinedValue] = cpu->registerA;
                programi+=3;
            } break;
            case INST_TYPE_LDB: {
                uint8_t value = program.data[programi+1];
                cpu->registerB = value;
                programi+=2;
            } break;
            case INST_TYPE_STB: {
                uint8_t msb = program.data[programi+1];
                uint8_t lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                cpu->memory[combinedValue] = cpu->registerB;
                programi+=3;
            } break;
            case INST_TYPE_OBU: {
                for(int i = 0; i < 8; ++i){
                    cpu->bus.bus[i] = (cpu->registerA >> (8 - i - 1)) & 0x01;
                }
                programi++;
            } break;
            case INST_TYPE_IBU: {
                uint8_t msb = program.data[programi+1];
                uint8_t lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                uint8_t packed_value = 0;
                for (int i = 0; i < 8; ++i) {
                    packed_value |= (cpu->bus.bus[(8 - i - 1)] & 0x01) << i;
                }
                cpu->memory[combinedValue] = packed_value;
                programi+=3;
            } break;
            case INST_TYPE_MOVB: {
                cpu->registerA = cpu->registerB;
                programi++;
            } break;
            case INST_TYPE_MOVA: {
                cpu->registerB = cpu->registerA;
                programi++;
            } break;
            case INST_TYPE_JMP: {
                uint8_t addr = program.data[programi+1];
                programi = addr;
            } break;
            case INST_TYPE_LFM: {
                uint8_t msb = program.data[programi+1];
                uint8_t lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                cpu->registerA = cpu->memory[combinedValue];
                programi+=3;
            } break;
            case INST_TYPE_ADD: {
                uint8_t value = program.data[programi+1];
                cpu->registerA += value;
                programi+=2;
            } break;
            default: {
                printf("No inst with hex value: 0x%x\n", program.data[programi]);
                exit(1);
            }
        }
    }
}

int main(){
    WriteFile();
    CPU cpu = {0};
    File program = ReadFile();
    print_program(&program);
    execute(&cpu, program);
    free(program.data);
    print_cpu(&cpu);
    return 0;
}