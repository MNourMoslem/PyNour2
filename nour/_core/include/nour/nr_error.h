/*
    PyNour Error Handling System
    ===========================

    This file implements PyNour's error handling system, which provides a centralized
    way to manage and report errors throughout the library. The system is designed to:

    1. Track different types of errors using an enumerated type system
    2. Store error context information in a thread-safe manner
    3. Provide convenient macros and functions for error reporting
    4. Support error propagation through the call stack

    Key Components:
    --------------
    1. NError_Type: Enumeration of all possible error types
    2. NError: Structure containing error information
    3. Global error state: Thread-local storage for the current error
    4. Error reporting functions and macros

    Usage:
    ------
    To raise an error:
        return NError_RaiseError(NError_TypeError, "Invalid type: expected %s, got %s", expected, got);
    
    To check for errors:
        if (NError_IsError()) {
            // Handle error
            NError_Print();
        }

    Thread Safety:
    -------------
    The error system uses thread-local storage to ensure thread safety when
    multiple threads are using the library simultaneously.
*/

#ifndef NOUR__CORE_INCLUDE_NOUR_NR_ERROR_H
#define NOUR__CORE_INCLUDE_NOUR_NR_ERROR_H

#define NERROR_MAX_STRING_LEN 256

#include "nr_config.h"
#include <stdarg.h>
#include <stdio.h>

/* 
    Enumeration of all possible error types in PyNour.
    Each error type corresponds to a specific category of errors
    that can occur during library operation.
*/
typedef enum {
    NError_NoError,          // No error has occurred
    NError_MemoryError,      // Memory allocation or management errors
    NError_TypeError,        // Type-related errors (invalid or mismatched types)
    NError_IndexError,       // Index out of bounds errors
    NError_ValueError,       // Invalid value errors
    NError_IOError,          // Input/output operation errors
    NError_ZeroDivisionError,// Division by zero errors
    NError_ImportError,      // Module or component import errors
    NError_AttributeError,   // Attribute access or modification errors
    NError_KeyError,         // Key-related errors in mapping operations
    NError_AssertionError,   // Assertion failure errors
    NError_RuntimeError,     // General runtime errors
    NError_OverflowError     // Numeric overflow errors
}NError_Type;

/*
    Structure containing error information.
    Stores both the type of error and additional context information
    as a formatted string.
*/
typedef struct
{
    NError_Type type;                            // Type of the error
    char context[NERROR_MAX_STRING_LEN];         // Error message and context
}NError;

/*
    Global error state variable.
    Thread-local storage ensures thread safety.
    Initialized to no error state.
*/
extern NError __NR_NERROR_GLOBAL_ERROR_VAR__;


#endif /* NOUR__CORE_INCLUDE_NOUR_NR_ERROR_H */