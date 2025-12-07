#include "../include/runtime.h"
#include <cstdio>

extern "C" DLLEXPORT double putchard(double X) {
    fputc(static_cast<char>(X), stderr);
    return 0;
}

extern "C" DLLEXPORT double printd(double X) {
    fprintf(stderr, "%f\n", X);
    return 0;
}
