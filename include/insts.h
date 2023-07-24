#ifndef _INSTS_H
#define _INSTS_H
#include <stdio.h>

typedef enum{
    INST_TYPE_LDA=0xa1,  // loads the a register with the number provided
    INST_TYPE_LDB=0xb1,  // loads the b register with the number provided
    INST_TYPE_STA=0x5a,  // stores the a register into memory with the index of the bytes provided after it
    INST_TYPE_STB=0x5b,  // stores the b register into memory with the index of the bytes provided after it
    INST_TYPE_OBU=0x0b,  // outputs the a register onto the bus
    INST_TYPE_MOVB=0xba, // moves the b register to the a register
    INST_TYPE_MOVA=0xab, // moves the a register to the b register
    INST_TYPE_JMP=0x10,  // sets the program index at the provided address (max 255)
    INST_TYPE_LFM=0x90,  // sets the a register to the content of the memory address
    INST_TYPE_NOP=0xea,  // does nothing
    INST_TYPE_IBU=0x1b,  // sets the memory at the provided index to the bus content
    INST_TYPE_ADD=0xad,  // add the value of the number after it to the a register
    INST_TYPE_INT=0x17,  // cpu interrupts
} Inst_Type;

typedef enum{
    INT_VIDEO=0x01,
} Interrupts;

const char* inst_as_cstr(Inst_Type type);

#endif // _INSTS_H