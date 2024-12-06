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

#ifndef NOUR__CORE_INCLUDE__NOUR_NR_ERROR_H
#define NOUR__CORE_INCLUDE__NOUR_NR_ERROR_H

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
static NError __NR_NERROR_GLOBAL_ERROR_VAR__= {
    .type = NError_NoError,
    .context = ""
};

/*
    Converts an error type to its string representation.
    Used primarily for error reporting and debugging.
    
    Parameters:
        type: The error type to convert
        trg_str: Target string buffer for the result
*/
NR_PRIVATE void
_NError_TypeAsString(NError_Type type, char* trg_str) {
    switch (type) {
        case NError_NoError:
            strcpy(trg_str, "NoError");
            break;
        case NError_MemoryError:
            strcpy(trg_str, "MemoryError");
            break;
        case NError_TypeError:
            strcpy(trg_str, "TypeError");
            break;
        case NError_IndexError:
            strcpy(trg_str, "IndexError");
            break;
        case NError_ValueError:
            strcpy(trg_str, "ValueError");
            break;
        case NError_IOError:
            strcpy(trg_str, "IOError");
            break;
        case NError_ZeroDivisionError:
            strcpy(trg_str, "ZeroDivisionError");
            break;
        case NError_ImportError:
            strcpy(trg_str, "ImportError");
            break;
        case NError_AttributeError:
            strcpy(trg_str, "AttributeError");
            break;
        case NError_KeyError:
            strcpy(trg_str, "KeyError");
            break;
        case NError_AssertionError:
            strcpy(trg_str, "AssertionError");
            break;
        case NError_RuntimeError:
            strcpy(trg_str, "RuntimeError");
            break;
        case NError_OverflowError:
            strcpy(trg_str, "OverflowError");
            break;
        default:
            strcpy(trg_str, "UnknownError");
            break;
    }
}

/*
    Checks if there is currently an active error.
    
    Returns:
        1 if there is an error, 0 otherwise.
*/
NR_HEADER int 
NError_IsError(){
    return __NR_NERROR_GLOBAL_ERROR_VAR__.type != NError_NoError;
}

/*
    Raises an error with a formatted message.
    
    Parameters:
        type: The type of error to raise
        format: Printf-style format string
        ...: Variable arguments for format string
    
    Returns:
        NULL, allowing for convenient return statements in functions
*/
NR_HEADER void* 
NError_RaiseError(NError_Type type, const char *format, ...) {
    __NR_NERROR_GLOBAL_ERROR_VAR__.type = type;

    va_list args;
    va_start(args, format);

    vsnprintf(__NR_NERROR_GLOBAL_ERROR_VAR__.context, NERROR_MAX_STRING_LEN, format, args);

    va_end(args);

    return NULL;
}

/*
    Prints the current error to stdout.
    Format: "ErrorType: error message"
*/
NR_HEADER void 
NError_Print(){
    char type_str[30];
    _NError_TypeAsString(__NR_NERROR_GLOBAL_ERROR_VAR__.type, type_str);
    printf("%s: %s\n", type_str, __NR_NERROR_GLOBAL_ERROR_VAR__.context);
}

/*
    Convenience functions for raising specific types of errors.
    Each returns NULL for convenient use in return statements.
*/

/*
    Raises an error without any context message.
    
    Parameters:
        type: The type of error to raise
    
    Returns:
        NULL, allowing for convenient return statements in functions
*/
NR_HEADER void* 
NError_RaiseErrorNoContext(NError_Type type){
    __NR_NERROR_GLOBAL_ERROR_VAR__.type = type;
    return NULL;
}

NR_HEADER void* NError_RaiseMemoryError() {
    return NError_RaiseErrorNoContext(NError_MemoryError);
}

NR_HEADER void* NError_RaiseTypeError() {
    return NError_RaiseErrorNoContext(NError_TypeError);
}

NR_HEADER void* NError_RaiseIndexError() {
    return NError_RaiseErrorNoContext(NError_IndexError);
}

NR_HEADER void* NError_RaiseValueError() {
    return NError_RaiseErrorNoContext(NError_ValueError);
}

NR_HEADER void* NError_RaiseIOError() {
    return NError_RaiseErrorNoContext(NError_IOError);
}

NR_HEADER void* NError_RaiseZeroDivisionError() {
    return NError_RaiseErrorNoContext(NError_ZeroDivisionError);
}

NR_HEADER void* NError_RaiseImportError() {
    return NError_RaiseErrorNoContext(NError_ImportError);
}

NR_HEADER void* NError_RaiseAttributeError() {
    return NError_RaiseErrorNoContext(NError_AttributeError);
}

NR_HEADER void* NError_RaiseKeyError() {
    return NError_RaiseErrorNoContext(NError_KeyError);
}

NR_HEADER void* NError_RaiseAssertionError() {
    return NError_RaiseErrorNoContext(NError_AssertionError);
}

NR_HEADER void* NError_RaiseRuntimeError() {
    return NError_RaiseErrorNoContext(NError_RuntimeError);
}

NR_HEADER void* NError_RaiseOverflowError() {
    return NError_RaiseErrorNoContext(NError_OverflowError);
}

#endif