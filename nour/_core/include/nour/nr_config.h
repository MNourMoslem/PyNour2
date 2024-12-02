#ifndef NOUR__CORE_INCLUDE__NOUR_NR_CONFIG_H
#define NOUR__CORE_INCLUDE__NOUR_NR_CONFIG_H


#define NR_NODE_MAX_NDIM 32

// Detect Compiler
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

// Platform-Specific Definitions
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


#define NR_STATIC static
#define NR_STATIC_INLINE NR_STATIC NR_INLINE
#define NR_STATIC_FINLINE NR_STATIC NR_FINLINE

#define NR_PRIVATE NR_STATIC_INLINE
#define NR_FPRIVATE NR_STATIC_FINLINE

#define NR_HEADER NR_STATIC_INLINE
#define NR_PUBLIC

#define NR_NULL ((void*)0)

#if defined(__GNUC__)
    #define __COMP_NR_UNUSED __attribute__ ((__unused__))
#elif defined(__ICC)
    #define __COMP_NR_UNUSED __attribute__ ((__unused__))
#elif defined(__clang__)
    #define __COMP_NR_UNUSED __attribute__ ((unused))
#else
    #define __COMP_NR_UNUSED
#endif

#define NR_UNUSED(x) _##x##__COMP_NPY_UNUSED

#endif /* NR_CONFIG_H */