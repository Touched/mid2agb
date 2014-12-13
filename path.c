#include <stdlib.h>
#include <string.h>

void *tokenize_path(const char *fullPath) {
    void *v1; // eax@1
    void *v2; // esi@1
    void *result; // eax@2

    v1 = malloc(771u);
    v2 = v1;
    if (v1) {
        _splitpath(FullPath, (char *) v1, (char *) v1 + 3, (char *) v1 + 259, (char *) v1 + 515);
        result = v2;
    }
    else {
        result = 0;
    }
    return result;
}

char *resolve_path_and_extension(char *fullPath, const char *ext) {
    void *v2; // edi@1
    char *result; // eax@2

    v2 = tokenize_path(FullPath);
    if (v2) {
        _makepath(FullPath, (const char *) v2, (const char *) v2 + 3, (const char *) v2 + 259, ext);
        free(v2);
        result = FullPath;
    }
    else {
        result = 0;
    }
    return result;
}

int check_extension(const char *fullPath, const char *a2) {
    char Ext; // [sp+0h] [bp-100h]@1

    _splitpath(FullPath, 0, 0, 0, &Ext);
    return strcmp(&Ext, a2);
}

char *strip_extension(const char *fullPath) {
    void *fname; // esi@1
    void *result; // eax@2

    fname = malloc(256u);                         // max path length without extension, probably
    if (fname) {
        _splitpath(FullPath, 0, 0, (char *) fname, 0);
        result = fname;
    }
    else {
        result = 0;
    }
    return result;
}