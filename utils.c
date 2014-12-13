#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

void print_error(const char *Format, ...) {
    va_list va;

    va_start(va, Format);
    printf("\nERROR : ");
    vprintf(Format, va);
    printf("\n\n");
    exit(2);
}

signed int fprintf_and_reset(const char *Format, ...) {
    signed int result; // eax@1
    va_list va; // [sp+8h] [bp+8h]@1

    va_start(va, Format);
    fprintf(output_file_fp, "\t.byte\t");
    vfprintf(output_file_fp, Format, va);
    fprintf(output_file_fp, "\n");
    result = -1;
    dword_40DF0C = -1;
    dword_40DF08 = -1;
    dword_40DF00 = -1;
    return result;
}

int reset_something() {
    int result; // eax@1

    dword_40DEF0 = -1;
    dword_40DEF4 = -1;
    dword_40DF1C = -1;
    result = 0;
    dword_40DF0C = 0;
    dword_40DF08 = 0;
    dword_40DF00 = 0;
    dword_40DF24 = 0;
    byte_40DF28 = 0;
    return result;
}