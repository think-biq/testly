/*
Copyright (c) 2021 blurryroots innovation qanat OÜ

All rights reserved.
*/
/*! \file assert.h
    \brief Defines Assert and Fail functions.
    
    ^^
*/

#ifndef TESTLY_ASSERT_H_
#define TESTLY_ASSERT_H_

#include <string.h>

#define TESTLY_EXIT_ON_FAIL 0
#define TESTLY_MAX_ERROR_STRING_LENGTH 256

#ifndef TESTLY_ASSERT_DISABLED
/**
* Fail a test section.
*
* @param Name Name of the test section.
* @param bExitOnFail Wether Fail should terminate the process.
* @param FailFMT Format string for the reason the section failed.
*/
void Fail(const char* Name, int bExitOnFail, const char* FailFMT, ...);

/**
* Asserts equality of expected and actual value. Will exit program if failing.
* 
* If you set DataSize to 0, Assert will assume that the pointer
* Expected and Actual are '\0'-terminated strings. If the DataSize is
* positive, then Assert will treat the pointer as contigious data and use
* memcmp to determine equality. It is not recommended to use
* complex / structure types or strings in this mode, since memcmp will likely
* yield wrong results. Prefer member wise asserts if you are dealing with
* structs. Otherwise, arrays of integral types, or even integral types
* themselves are supported.
*
* @param Name Name of the test section.
* @param DataSize Treats Expected and Actual as strings if 0. Else treats values as contiguous memory.
* @param FailFMT Format string for the reason the section failed.
*/
void Assert(const char* Name, size_t DataSize, const void* Expected, const void* Actual, const char* FailFMT, ...);

/**
* Checks equality of expected and actual value.
* 
* If you set DataSize to 0, Assert will assume that the pointer
* Expected and Actual are '\0'-terminated strings. If the DataSize is
* positive, then Assert will treat the pointer as contigious data and use
* memcmp to determine equality. It is not recommended to use
* complex / structure types or strings in this mode, since memcmp will likely
* yield wrong results. Prefer member wise asserts if you are dealing with
* structs. Otherwise, arrays of integral types, or even integral types
* themselves are supported.
*
* @param Name Name of the test section.
* @param DataSize Treats Expected and Actual as strings if 0. Else treats values as contiguous memory.
* @param FailFMT Format string for the reason the section failed.
*/
int Check(const char* Name, size_t DataSize, const void* Expected, const void* Actual, const char* FailFMT, ...);
#else
/**
* Will be ignored if TESTLY_ASSERT_DISABLED is set.
*/
#define Fail(...) {}

/**
* Will always evaluate to 1 if TESTLY_ASSERT_DISABLED is set.
*/
#define Assert(...) (1)
#endif

#endif