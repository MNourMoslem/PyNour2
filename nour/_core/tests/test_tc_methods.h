#ifndef NOUR__CORE_SRC_NOUR_TESTS_TEST_TC_METHODS_H
#define NOUR__CORE_SRC_NOUR_TESTS_TEST_TC_METHODS_H

#include "nour/nour.h"
#include "common.h"
#include "../src/nour/niter.h"
#include "../src/nour/node_core.h"
#include "../src/nour/free.h"
#include "../src/nour/nmath.h"

#define TEST_TC_METHODS_FUNCTION(st, nst, dt, ndt, idx)       \
static int test_tc_methods_##idx() {                       \
    int res = 0;                                             \
    Node *n1, *n2;                                           \
    nst arr[] = NR_32ONES;                                   \
    for (int i = 0; i < 32; i++) {                           \
        arr[i] = i + 1;                                      \
    }                                                        \
    nr_long shp[] = {16};                                  \
    int nd = 1;                                              \
    NR_DTYPE dtype = st;                                     \
    n1 = Node_New(arr, 1, nd, shp, dtype);                   \
    if (!n1) {                                               \
        return -1;                                           \
    }                                                        \
    n2 = Node_ToType(NULL, n1, dt);                          \
    if (!n2) {                                               \
        res = -1;                                            \
    }                                                        \
    int nitems = (int)Node_NItems(n1);                       \
    nst v1;                                                  \
    ndt v2;                                                  \
    for (int i = 0; i < nitems; i++) {                       \
        v1 = *((nst*)n1->data + i);                          \
        v2 = *((ndt*)n2->data + i);                          \
        if ((ndt)v1 != v2) {                                 \
            res = -1;                                        \
            break;                                           \
        }                                                    \
    }                                                        \
    Node_Free(n1);                                           \
    Node_Free(n2);                                           \
    return res;                                              \
}

// Conversions to NR_BOOL
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_BOOL   , nr_bool   , 1)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_BOOL   , nr_bool   , 2)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_BOOL   , nr_bool   , 3)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_BOOL   , nr_bool   , 4)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_BOOL   , nr_bool   , 5)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_BOOL   , nr_bool   , 6)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_BOOL   , nr_bool   , 7)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_BOOL   , nr_bool   , 8)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_BOOL   , nr_bool   , 9)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_BOOL   , nr_bool   , 10)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_BOOL   , nr_bool   , 11)

// Conversions to NR_INT8
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_INT8   , nr_int8   , 12)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_INT8   , nr_int8   , 13)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_INT8   , nr_int8   , 14)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_INT8   , nr_int8   , 15)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_INT8   , nr_int8   , 16)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_INT8   , nr_int8   , 17)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_INT8   , nr_int8   , 18)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_INT8   , nr_int8   , 19)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_INT8   , nr_int8   , 20)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_INT8   , nr_int8   , 21)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_INT8   , nr_int8   , 22)

// Conversions to NR_UINT8
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_UINT8  , nr_uint8  , 23)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_UINT8  , nr_uint8  , 24)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_UINT8  , nr_uint8  , 25)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_UINT8  , nr_uint8  , 26)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_UINT8  , nr_uint8  , 27)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_UINT8  , nr_uint8  , 28)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_UINT8  , nr_uint8  , 29)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_UINT8  , nr_uint8  , 30)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_UINT8  , nr_uint8  , 31)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_UINT8  , nr_uint8  , 32)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_UINT8  , nr_uint8  , 33)

// Conversions to NR_INT16
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_INT16  , nr_int16  , 34)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_INT16  , nr_int16  , 35)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_INT16  , nr_int16  , 36)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_INT16  , nr_int16  , 37)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_INT16  , nr_int16  , 38)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_INT16  , nr_int16  , 39)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_INT16  , nr_int16  , 40)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_INT16  , nr_int16  , 41)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_INT16  , nr_int16  , 42)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_INT16  , nr_int16  , 43)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_INT16  , nr_int16  , 44)

// Conversions to NR_UINT16
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_UINT16 , nr_uint16 , 45)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_UINT16 , nr_uint16 , 46)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_UINT16 , nr_uint16 , 47)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_UINT16 , nr_uint16 , 48)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_UINT16 , nr_uint16 , 49)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_UINT16 , nr_uint16 , 50)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_UINT16 , nr_uint16 , 51)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_UINT16 , nr_uint16 , 52)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_UINT16 , nr_uint16 , 53)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_UINT16 , nr_uint16 , 54)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_UINT16 , nr_uint16 , 55)

// Conversions to NR_INT32
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_INT32  , nr_int32  , 56)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_INT32  , nr_int32  , 57)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_INT32  , nr_int32  , 58)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_INT32  , nr_int32  , 59)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_INT32  , nr_int32  , 60)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_INT32  , nr_int32  , 61)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_INT32  , nr_int32  , 62)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_INT32  , nr_int32  , 63)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_INT32  , nr_int32  , 64)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_INT32  , nr_int32  , 65)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_INT32  , nr_int32  , 66)

// Conversions to NR_UINT32
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_UINT32 , nr_uint32 , 67)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_UINT32 , nr_uint32 , 68)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_UINT32 , nr_uint32 , 69)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_UINT32 , nr_uint32 , 70)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_UINT32 , nr_uint32 , 71)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_UINT32 , nr_uint32 , 72)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_UINT32 , nr_uint32 , 73)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_UINT32 , nr_uint32 , 74)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_UINT32 , nr_uint32 , 75)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_UINT32 , nr_uint32 , 76)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_UINT32 , nr_uint32 , 77)

// Conversions to NR_INT64
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_INT64  , nr_int64  , 78)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_INT64  , nr_int64  , 79)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_INT64  , nr_int64  , 80)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_INT64  , nr_int64  , 81)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_INT64  , nr_int64  , 82)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_INT64  , nr_int64  , 83)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_INT64  , nr_int64  , 84)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_INT64  , nr_int64  , 85)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_INT64  , nr_int64  , 86)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_INT64  , nr_int64  , 87)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_INT64  , nr_int64  , 88)

// Conversions to NR_UINT64
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_UINT64 , nr_uint64 , 89)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_UINT64 , nr_uint64 , 90)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_UINT64 , nr_uint64 , 91)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_UINT64 , nr_uint64 , 92)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_UINT64 , nr_uint64 , 93)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_UINT64 , nr_uint64 , 94)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_UINT64 , nr_uint64 , 95)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_UINT64 , nr_uint64 , 96)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_UINT64 , nr_uint64 , 97)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_UINT64 , nr_uint64 , 98)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_UINT64 , nr_uint64 , 99)

// Conversions to NR_FLOAT32
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_FLOAT32, nr_float32, 100)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_FLOAT32, nr_float32, 101)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_FLOAT32, nr_float32, 102)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_FLOAT32, nr_float32, 103)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_FLOAT32, nr_float32, 104)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_FLOAT32, nr_float32, 105)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_FLOAT32, nr_float32, 106)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_FLOAT32, nr_float32, 107)
TEST_TC_METHODS_FUNCTION(NR_UINT64 , nr_uint64 , NR_FLOAT32, nr_float32, 108)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32, nr_float32, NR_FLOAT32, nr_float32, 109)
TEST_TC_METHODS_FUNCTION(NR_FLOAT64, nr_float64, NR_FLOAT32, nr_float32, 110)

// Conversions to NR_FLOAT64
TEST_TC_METHODS_FUNCTION(NR_BOOL   , nr_bool   , NR_FLOAT64, nr_float64, 111)
TEST_TC_METHODS_FUNCTION(NR_INT8   , nr_int8   , NR_FLOAT64, nr_float64, 112)
TEST_TC_METHODS_FUNCTION(NR_UINT8  , nr_uint8  , NR_FLOAT64, nr_float64, 113)
TEST_TC_METHODS_FUNCTION(NR_INT16  , nr_int16  , NR_FLOAT64, nr_float64, 114)
TEST_TC_METHODS_FUNCTION(NR_UINT16 , nr_uint16 , NR_FLOAT64, nr_float64, 115)
TEST_TC_METHODS_FUNCTION(NR_INT32  , nr_int32  , NR_FLOAT64, nr_float64, 116)
TEST_TC_METHODS_FUNCTION(NR_UINT32 , nr_uint32 , NR_FLOAT64, nr_float64, 117)
TEST_TC_METHODS_FUNCTION(NR_INT64  , nr_int64  , NR_FLOAT64, nr_float64, 118)
TEST_TC_METHODS_FUNCTION(NR_UINT64  , nr_uint64  , NR_FLOAT64, nr_float64, 119)
TEST_TC_METHODS_FUNCTION(NR_FLOAT32  , nr_float32  , NR_FLOAT64, nr_float64, 120)

int __test_all_tc_methods(){
    TestFunc all_tests[] = {
        test_tc_methods_1,
        test_tc_methods_2,
        test_tc_methods_3,
        test_tc_methods_4,
        test_tc_methods_5,
        test_tc_methods_6,
        test_tc_methods_7,
        test_tc_methods_8,
        test_tc_methods_9,
        test_tc_methods_10,
        test_tc_methods_11,
        test_tc_methods_12,
        test_tc_methods_13,
        test_tc_methods_14,
        test_tc_methods_15,
        test_tc_methods_16,
        test_tc_methods_17,
        test_tc_methods_18,
        test_tc_methods_19,
        test_tc_methods_20,
        test_tc_methods_21,
        test_tc_methods_22,
        test_tc_methods_23,
        test_tc_methods_24,
        test_tc_methods_25,
        test_tc_methods_26,
        test_tc_methods_27,
        test_tc_methods_28,
        test_tc_methods_29,
        test_tc_methods_30,
        test_tc_methods_31,
        test_tc_methods_32,
        test_tc_methods_33,
        test_tc_methods_34,
        test_tc_methods_35,
        test_tc_methods_36,
        test_tc_methods_37,
        test_tc_methods_38,
        test_tc_methods_39,
        test_tc_methods_40,
        test_tc_methods_41,
        test_tc_methods_42,
        test_tc_methods_43,
        test_tc_methods_44,
        test_tc_methods_45,
        test_tc_methods_46,
        test_tc_methods_47,
        test_tc_methods_48,
        test_tc_methods_49,
        test_tc_methods_50,
        test_tc_methods_51,
        test_tc_methods_52,
        test_tc_methods_53,
        test_tc_methods_54,
        test_tc_methods_55,
        test_tc_methods_56,
        test_tc_methods_57,
        test_tc_methods_58,
        test_tc_methods_59,
        test_tc_methods_60,
        test_tc_methods_61,
        test_tc_methods_62,
        test_tc_methods_63,
        test_tc_methods_64,
        test_tc_methods_65,
        test_tc_methods_66,
        test_tc_methods_67,
        test_tc_methods_68,
        test_tc_methods_69,
        test_tc_methods_70,
        test_tc_methods_71,
        test_tc_methods_72,
        test_tc_methods_73,
        test_tc_methods_74,
        test_tc_methods_75,
        test_tc_methods_76,
        test_tc_methods_77,
        test_tc_methods_78,
        test_tc_methods_79,
        test_tc_methods_80,
        test_tc_methods_81,
        test_tc_methods_82,
        test_tc_methods_83,
        test_tc_methods_84,
        test_tc_methods_85,
        test_tc_methods_86,
        test_tc_methods_87,
        test_tc_methods_88,
        test_tc_methods_89,
        test_tc_methods_90,
        test_tc_methods_91,
        test_tc_methods_92,
        test_tc_methods_93,
        test_tc_methods_94,
        test_tc_methods_95,
        test_tc_methods_96,
        test_tc_methods_97,
        test_tc_methods_98,
        test_tc_methods_99,
        test_tc_methods_100,
        test_tc_methods_101,
        test_tc_methods_102,
        test_tc_methods_103,
        test_tc_methods_104,
        test_tc_methods_105,
        test_tc_methods_106,
        test_tc_methods_107,
        test_tc_methods_108,
        test_tc_methods_109,
        test_tc_methods_110,
        test_tc_methods_111,
        test_tc_methods_112,
        test_tc_methods_113,
        test_tc_methods_114,
        test_tc_methods_115,
        test_tc_methods_116,
        test_tc_methods_117,
        test_tc_methods_118,
        test_tc_methods_119,
        test_tc_methods_120,
    };

    TestFunc func;
    for (int i = 0; i < 120; i++){
        func = all_tests[i];
        if (func() != 0){
            return -1;
        }
    }
    return 0;
}

void test_tc_methods(){
    NTEST_RUN_TEST("Type Conversion Methods",
    {
        NTEST_ONE_TEST(1, __test_all_tc_methods);
    }
    )
}


#endif