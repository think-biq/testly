# Testly

Minimal test utilties.

## Overview

Testly brings a minimal set of utilities for function based testing. You specify a test method, and can use **Assert** or **Fail** to signal that the test should fail. To run the test, you get a wrapper macro, which deals with checking the tests result.

### Assert @ assert.h

At the heart of testly is the varadic function **Assert**.
```c
int Assert(size_t DataSize,
	const char* Name, int bExitOnFail,
	const void* Expected, const void* Actual, 
	const char* FailFMT, ...
);
```
The first parameter *DataSize* controls the behaviour of the comparison. If you set it to 0, **Assert** will assume that the pointer *Expected* and *Actual* are '\0'-terminated strings. If the *DataSize* is positive, then **Assert** will treat the pointer as contigious data and use *memcmp* to determine equality. It is not recommended to use complex / structure types or strings in this mode, since memcmp will likely yield wrong results. Prefer member wise asserts if you are dealing with structs. Otherwise, arrays of integral types, or even integral types themselves are supported.
The *Name* allows you to identify the assert for clear overview in the results page. *bExitOnFail* let's you specify how **Assert** should react when failing. True means the assert will terminate the program, false means the assert will be flagged as failed, yet letting the program continue. To get more insight into a failed test case, you can specify a format string *FailFMT*, and a varadic list of argument.

#### Example: Checking integral types (i.e. integer)

```c
int Expected = 42;
int Given = 23;
int Passed = Assert(sizeof(int), "CheckIntegers",
	TESTLY_EXIT_ON_FAIL, &Expected, &Given,
    "Expected %i, got %i.", Expected, Given
);

```

In order to tread an integral type as contigous data, we pass it as pointer to the stack variables and specify the size of the datatype. 

#### Example: Checking strings

```c
const char* Expected = "Es hört doch nur jeder, was er versteht.";
const char* Given = "Man reist ja nicht um anzukommen, sondern um zu reisen.";
int Passed = Assert(0, "CheckIntegers", 
	TESTLY_EXIT_ON_FAIL, Expected, Given,
    "Expected %i, got %i.", Expected, Given
);

```

Specify a *DataSize* of 0, to ask **Assert** to treat the given data as strings.

#### Example: Checking data arrays

```c
const int64_t Expected[2] = { 1631880000, 433512000 };
const int64_t Given[2] = { 433512000, 1631880000 };
int Passed = Assert(2*sizeof(int64_t), "CheckDataArrays", 
	TESTLY_EXIT_ON_FAIL, Expected, Given,
    "Expected %i, got %i.", Expected, Given
);

```

Specify a *DataSize* as a total number of bytes your array covers and **Assert** will try to compare the memory of both arrays.

### Fail @ assert.h

If you need to always fail a section / test function.
```c
void Fail(const char* Name, int bExitOnFail, const char* FailFMT, ...);
```
Specify the *Name* of the section, hint if you want **Fail** to terminate the process via *bExitOnFail* and give a reason (format string) through *FailFMT*.

### RUN_TEST @ run.h

Runs a test function and evaluates if it passed or failed.
```c
#define RUN_TEST(Name) \
	...
```
Specify the name of the test function through *Name*.

### Usage

Test function should return an integer indicating if the test passed (< 0) or failed (0).
Run each test through RUN_TEST for convenience.

See *test/main.c* for more examples on how to use testly.


