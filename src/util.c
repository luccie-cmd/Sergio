#include "util.h"

int WriteFile(char *file){
    FILE *f = fopen(file, "wb");
    if(!f){
        printf("Could not make file `%s`\n", file);
        return 1;
    }
    uint8_t program[] = {
        0x00, 'S', 'G', 0x00,
        0x20, 0x00, 0x0F,  // call #$000F
        0xa1, 0x01,        // lda #$01
        0xb1, 101,         // ldb #72
        0x17, 0x01,        // int #$01
        0x17, 0x02,        // int #$02

        // 0x000F
        0xa1, 0x01,        // lda #$01
        0xb1, 72,          // ldb #101
        0x17, 0x01,        // int #$01
        0x21,              // ret
    };
    fwrite(&program, 1, ARRAY_SIZE(program)*sizeof(uint8_t), f);
    fclose(f);
    return 0;
}

File ReadFile(char *file){
    FILE *f = fopen(file, "rb");
    if(!f){
        printf("Could not open file `%s`\n", file);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    BYTE *buffer = malloc(size);
    fread(buffer, 1, size, f);
    return (File) {.data = buffer, .len = size};
}

void print_program(const File * f){
    for(size_t i = 0; i < f->len; ++i){
        if(inst_as_cstr(f->data[i]) != NULL){
            printf("Program[%lld] = %s\n", i, inst_as_cstr(f->data[i]));
        }
    }
}
