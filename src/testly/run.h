
#ifndef TESTLY_H_
#define TESTLY_H_

#include <stdio.h>

#define RUN_TEST(Name) \
{ \
    int Passed = Name(); \
    if (Passed) \
    { \
        fprintf(stdout, "\033[0;32m"); \
        fprintf(stdout, "Passed: "); \
        fprintf(stdout, "\033[0m"); \
        fprintf(stdout, "%s.\n", #Name); \
    } \
    else \
    { \
        fprintf(stdout, "\033[0;31m"); \
        fprintf(stdout, "Failed: "); \
        fprintf(stdout, "\033[0m"); \
        fprintf(stdout, "%s.\n", #Name); \
    } \
}

#endif