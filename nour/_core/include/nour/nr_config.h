/*
    PyNour Configuration System
    ==========================

    This file defines core configuration macros and platform-specific settings
    for the PyNour library. It provides a unified way to handle:

    1. Compiler-specific directives and optimizations
    2. Platform detection and adaptation
    3. Common utility macros used throughout the library
    4. Inline function specifications

    Key Components:
    --------------
    1. Compiler Detection: Identifies and configures for different compilers
    2. Platform Detection: Windows vs Unix-like systems
    3. Function Attributes: Inline, static, and visibility controls
    4. Utility Macros: Common definitions used across the library

    Usage:
    ------
    This header should be included first in most PyNour source files to ensure
    consistent behavior across different platforms and compilers.
*/

#ifndef NOUR__CORE_INCLUDE__NOUR_NR_CONFIG_H
#define NOUR__CORE_INCLUDE__NOUR_NR_CONFIG_H

/* Maximum number of dimensions supported for arrays */
#define NR_NODE_MAX_NDIM 32

/*
    Compiler-Specific Definitions
    ----------------------------
    Detects the compiler being used and sets appropriate
    function attributes and optimizations.
*/
#if defined(__GNUC__) || defined(__clang__)  // GCC and Clang
    #define NR_INLINE __inline__
    #define NR_NOINLINE __attribute__((noinline))
    #define NR_FINLINE __attribute__((always_inline)) __inline__
    #define NR_TLS __thread
#elif defined(_MSC_VER)  // Microsoft Visual Studio Compiler
    #define NR_INLINE __inline
    #define NR_NOINLINE __declspec(noinline)
    #define NR_FINLINE __forceinline
    #define NR_TLS __declspec(thread)
#else  // Other compilers
    #define NR_INLINE inline
    #define NR_NOINLINE
    #define NR_FINLINE inline
    #define NR_TLS
#endif

/*
    Platform-Specific Definitions
    ---------------------------
    Detects the operating system and sets appropriate
    platform-specific configurations.
*/
#if defined(_WIN32) || defined(_WIN64)  // Windows
    #define NR_WINDOWS 1
    #define NR_UNIX 0
#elif defined(__unix__) || defined(__APPLE__)  // Unix-like OS (Linux, MacOS)
    #define NR_WINDOWS 0
    #define NR_UNIX 1
#else
    #define NR_WINDOWS 0
    #define NR_UNIX 0
#endif

/*
    Function Visibility and Linkage Controls
    --------------------------------------
    Defines macros for controlling function visibility
    and linkage across the library.
*/
#define NR_STATIC static
#define NR_STATIC_INLINE NR_STATIC NR_INLINE
#define NR_STATIC_FINLINE NR_STATIC NR_FINLINE

#define NR_PRIVATE NR_STATIC_INLINE
#define NR_FPRIVATE NR_STATIC_FINLINE

#define NR_HEADER NR_STATIC_INLINE
#define NR_PUBLIC

/* Null pointer definition */
#define NR_NULL ((void*)0)

/*
    Unused Variable Handling
    ----------------------
    Provides compiler-specific ways to mark variables
    as intentionally unused to prevent warnings.
*/
#if defined(__GNUC__) || defined(__ICC) || defined(__clang__)
    #define NR_UNUSED(x) __attribute__((unused)) x
#else
    #define NR_UNUSED(x) x
#endif

#endif /* NR_CONFIG_H */