#include "util.h"

int WriteFile(char *file){
    FILE *f = fopen(file, "wb");
    if(!f){
        printf("Could not make file `%s`\n", file);
        return 1;
    }
    uint8_t program[] = {
        0x00, 'S', 'G', 0x00,
        0xa1, 0x01,
        0xb1, 0x42,
        0x5a, 0x00, 0x00,
        0x5b, 0x00, 0x01,
        0x0b,
        0xab,
        0xba,
        0x10, 19,
        0x90, 0x00, 0x01,
        0xea,
        0xab,
        0xad, 0xff,
        0x90, 0x00, 0x00,

        // reset all memory
        0xa1, 0x00,
        0x5a, 0x00, 0x00,
        0x5a, 0x00, 0x01,
        0x5a, 0x00, 0x02,
        0x5a, 0x00, 0x03,
        0xab,
        0xb1, 0x00,
        0xab,
        0x0b,
        0xc1,
        0xf1,
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