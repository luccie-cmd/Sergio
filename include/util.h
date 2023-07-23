#ifndef _UTIL_H
#define _UTIL_H
#include <stdio.h>
#include "types.h"
#include "insts.h"

typedef struct{
    size_t len;
    BYTE *data;
} File;

int WriteFile(char *file);
File ReadFile(char *file);
void print_program(const File *f);

#endif // _UTIL_H