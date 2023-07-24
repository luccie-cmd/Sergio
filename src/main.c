#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "util.h"
#include "cpu.h"
#include "insts.h"

char *shift(int *argc, char ***argv){
    if(*argc == 0) return NULL;
    char *result = **argv;
    *argv+=1;
    *argc-=1;
    return result;
}

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
                BYTE value = program.data[programi+1];
                cpu->registerA = value;
                programi+=2;
            } break;
            case INST_TYPE_STA: {
                BYTE msb = program.data[programi+1];
                BYTE lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                cpu->memory[combinedValue] = cpu->registerA;
                programi+=3;
            } break;
            case INST_TYPE_LDB: {
                BYTE value = program.data[programi+1];
                cpu->registerB = value;
                programi+=2;
            } break;
            case INST_TYPE_STB: {
                BYTE msb = program.data[programi+1];
                BYTE lsb = program.data[programi+2];
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
                BYTE msb = program.data[programi+1];
                BYTE lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                BYTE packed_value = 0;
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
                BYTE addr = program.data[programi+1];
                programi = addr;
            } break;
            case INST_TYPE_LFM: {
                BYTE msb = program.data[programi+1];
                BYTE lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                cpu->registerA = cpu->memory[combinedValue];
                programi+=3;
            } break;
            case INST_TYPE_ADD: {
                BYTE value = program.data[programi+1];
                cpu->registerA += value;
                programi+=2;
            } break;
            case INST_TYPE_INT: {
                BYTE interrupt = program.data[programi+1];
                switch(interrupt){
                    case INT_VIDEO: {
                        switch(cpu->registerA){
                            // print a single character
                            case 0x01: {
                                BYTE ascii = cpu->registerB;
                                putc(ascii, stdout);
                            } break;
                            default: {
                                printf("Invalid interrupt type\n");
                                exit(1);
                            }
                        }
                    } break;
                    case INT_HLT: {
                        exit(0);
                    } break;
                    default: {
                        printf("No interrupt with value `%d`\n", interrupt);
                        exit(1);
                    }
                }
                programi+=2;
            } break;
            case INST_TYPE_CALL: {
                BYTE msb = program.data[programi+1];
                BYTE lsb = program.data[programi+2];
                uint16_t combinedValue = ((uint16_t)msb << 8) | lsb;
                cpu->stack[cpu->SP++] = programi+3;
                programi=combinedValue;
            } break;
            case INST_TYPE_RET: {
                programi = cpu->stack[cpu->SP - 1];
                cpu->SP -= 1;
            } break;
            default: {
                printf("No inst with hex value: 0x%x\n", program.data[programi]);
                exit(1);
            }
        }
    }
}

void usage(){
    printf("Sergio -o <*.bin>\n");
    printf("extra options\n");
    printf("    -h  prints this help\n");
}

int main(int argc, char **argv){
    (void)shift(&argc, &argv);
    char *out_file = NULL;
    while(argc > 0){
        char *arg = shift(&argc, &argv);
        if(strcmp(arg, "-o") == 0){
            out_file = shift(&argc, &argv);
            if(out_file == NULL){
                usage();
                printf("Must provide file after `-o`\n");
                exit(1);
            }
        }
        else if(strcmp(arg, "-h") == 0){
            usage();
            return 0;
        }
        else{
            printf("No argument named: `%s`\n", arg);
            exit(1);
        }
    }
    WriteFile(out_file);
    CPU cpu = {0};
    File program = ReadFile(out_file);
    execute(&cpu, program);
    free(program.data);
    return 0;
}