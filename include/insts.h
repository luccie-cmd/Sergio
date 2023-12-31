#ifndef _INSTS_H
#define _INSTS_H
#include <stdio.h>
#include <stdlib.h>

typedef enum{
    INST_TYPE_LDA=0xa1,  // loads the a register with the number provided
    INST_TYPE_LDB=0xb1,  // loads the b register with the number provided
    INST_TYPE_STA=0x5a,  // stores the a register into memory with the index of the bytes provided after it
    INST_TYPE_STB=0x5b,  // stores the b register into memory with the index of the bytes provided after it
    INST_TYPE_OBU=0x0b,  // outputs the a register onto the bus
    INST_TYPE_MOVB=0xba, // moves the a register to the b register
    INST_TYPE_MOVA=0xab, // moves the b register to the a register
    INST_TYPE_JMP=0x10,  // sets the program index at the provided address (max 255)
    INST_TYPE_LFM=0x90,  // sets the a register to the content of the memory address
    INST_TYPE_NOP=0xea,  // does nothing
    INST_TYPE_IBU=0x1b,  // sets the memory at the provided index to the bus content
    INST_TYPE_ADD=0xad,  // add the value of the number after it to the a register
    INST_TYPE_SUB=0x5d,  // subs the value of the number after it to the a register
    INST_TYPE_DIV=0xd1,  // divs the value of the number after it to the a register and sets the 0 bit if you try to divide by zero
    INST_TYPE_MULT=0x87, // multiplies the value of the number after it to the a register
    INST_TYPE_INT=0x17,  // cpu interrupts
    INST_TYPE_CALL=0x20, // sets the intstruction pointer to the address after it and pushes the return address to the stack
    INST_TYPE_RET=0x21,  // gets the first address in the stack that it finds and returns to it
    INST_TYPE_CLC=0xc1,  // clears the carry flag
    INST_TYPE_CLZ=0xf1,  // clears the zero flag
} Inst_Type;

typedef enum{
    INT_VIDEO=0x01,
    INT_HLT=0x02,
    
    INT_DIV_BY_ZERO=0x20,
} Interrupts;

const char* inst_as_cstr(Inst_Type type);

void interrupt(Interrupts interrupt);

#endif // _INSTS_H