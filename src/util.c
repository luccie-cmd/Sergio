#include "util.h"

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