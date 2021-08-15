/*
Copyright (c) 2021 blurryroots innovation qanat OÜ

All rights reserved.
*/

#include "assert.h"

#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

static int bIsColorModeActive = 1;

void Testly_SetColorMode(int bColorModeActive)
{
    bIsColorModeActive = bColorModeActive;
}

int Testly_IsColorModeActive()
{
    return bIsColorModeActive;
}

void Fail(const char* Name, int bExitOnFail, const char* FailFMT, ...)
{
    if (bIsColorModeActive)
    {
        fprintf(stdout, "\033[0;31m");
    }
    fprintf(stdout, "Segment Failed: ");
    if (bIsColorModeActive)
    {
        fprintf(stdout, "\033[0m"); // Reset color.
    }
    fprintf(stdout, "%s.\n\t", Name);

    char FMT[strlen(FailFMT) + 1 + 1];
    sprintf(FMT, "%s\n", FailFMT);

    va_list FailArgs;
    va_start(FailArgs, FailFMT);
    vfprintf(stdout, FMT, FailArgs); // Special case for varadic args.
    va_end(FailArgs);
    
    if (0 != bExitOnFail)
        exit(1);
}

// Specialized version of Fail, to accept a concrete varadic argument list object.
void VFail(const char* Name, int bExitOnFail, const char* FailFMT, va_list FailArgs)
{
    if (bIsColorModeActive)
    {
        fprintf(stdout, "\033[0;31m");
    }
    fprintf(stdout, "Segment Failed: ");
    if (bIsColorModeActive)
    {
        fprintf(stdout, "\033[0m"); // Reset color.
    }
    fprintf(stdout, "%s.\n\t", Name);

    char FMT[strlen(FailFMT) + 1 + 1];
    sprintf(FMT, "%s\n", FailFMT);
    vfprintf(stdout, FMT, FailArgs); // Special case for varadic args.
    
    if (0 != bExitOnFail)
        exit(1);
}

int Check_Internally(const char* Name, int bExitOnFail, size_t DataSize,
    const void* Expected, const void* Actual, const char* FailFMT, va_list VarArgs)
{
    int Passed = 1;

    if (NULL != Expected && NULL != Actual)
    {
        if (0 == DataSize)
        {
            Passed = (0 == strcmp((const char*)Expected, (const char*)Actual));
        }
        else
        {
            Passed = (0 == memcmp(Expected, Actual, DataSize));
        }     
    }

    if (0 == Passed)
    {
        VFail(NULL == Name ? "NULL" : Name, bExitOnFail, FailFMT, VarArgs);
    }

    return Passed;
}

int Check(const char* Name, size_t DataSize,
    const void* Expected, const void* Actual, const char* FailFMT, ...)
{
    va_list VarArgs;
    va_start(VarArgs, FailFMT);
    int Passed = Check_Internally(Name, 0, DataSize, Expected, Actual, FailFMT, VarArgs);
    va_end(VarArgs);

    return Passed;
}


void Assert(const char* Name, size_t DataSize,
    const void* Expected, const void* Actual, const char* FailFMT, ...)
{
     va_list VarArgs;
    va_start(VarArgs, FailFMT);
    Check_Internally(Name, 1, DataSize, Expected, Actual, FailFMT, VarArgs);
    va_end(VarArgs);
}