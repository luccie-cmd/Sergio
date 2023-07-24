#include "insts.h"

const char *inst_as_cstr(Inst_Type type)
{
    switch(type){
        case INST_TYPE_LDA: return "LDA";
        case INST_TYPE_LDB: return "LDB";
        case INST_TYPE_STA: return "STA";
        case INST_TYPE_STB: return "STB";
        case INST_TYPE_OBU: return "OBU";
        case INST_TYPE_IBU: return "IBU";
        case INST_TYPE_MOVB: return "MOVB";
        case INST_TYPE_MOVA: return "MOVA";
        case INST_TYPE_JMP: return "JMP";
        case INST_TYPE_LFM: return "LFM";
        case INST_TYPE_NOP: return "NOP";
        case INST_TYPE_ADD: return "ADD";
        case INST_TYPE_SUB: return "SUB";
        case INST_TYPE_MULT:return "MULT";
        case INST_TYPE_DIV: return "DIV";
        case INST_TYPE_INT: return "INT";
        case INST_TYPE_CALL: return "CALL";
        case INST_TYPE_RET: return "RET";
        case INST_TYPE_CLC: return "CLC";
        case INST_TYPE_CLZ: return "CLZ";
        default: return NULL;
    }
    return NULL;
}

void interrupt(Interrupts interrupt){
    if(interrupt == INT_DIV_BY_ZERO){
        printf("Segmentation fault\nCore dumped\n");
        exit(1);
    }
}
