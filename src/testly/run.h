/*
Copyright (c) 2021 blurryroots innovation qanat OÜ

All rights reserved.
*/
/*! \file run.h
    \brief Run macro.
    
    ^^
*/

#ifndef TESTLY_H_
#define TESTLY_H_

#include <stdio.h>

/**
* Runs the given function and evalues if test passed or failed.
* 
* @param Name Name of the test function.
*/
#define RUN_TEST(Name) \
{ \
    int Passed = Name(); \
    if (Passed) \
    { \
        fprintf(stdout, "\033[0;32m"); \
        fprintf(stdout, "Test Passed: "); \
        fprintf(stdout, "\033[0m"); \
        fprintf(stdout, "%s.\n", #Name); \
    } \
    else \
    { \
        fprintf(stdout, "\033[0;31m"); \
        fprintf(stdout, "Test Failed: "); \
        fprintf(stdout, "\033[0m"); \
        fprintf(stdout, "%s.\n", #Name); \
    } \
}

#endif