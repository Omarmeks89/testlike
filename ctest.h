/* Simple lightweight testing util for C programs.
* Copyright (C) 2024  Egor Markov
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#ifndef _CTEST_H
#define _CTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PASSED "PASSED"
#define FAILED "FAILED"
#define EXPECTED "EXPECTED: "
#define GOT "GOT: "
#define PTR_ "PTR IS NOT NULL. ADDR.: "
#define LINE_STR "LINE: "
#define IS_EQ_TO "IS EQUAL TO:"

/* for not NULL pointer */
#define NULLPTR "GOT NULLPTR. ADDR.: "

/* extension for floating point */
#define EPSILON "EPS.: "
#define NE_EPSILON " EPS.: "

/* section of spaces and
 * puctuation symbols. */
#define SINGLE_SPACE " "
#define COMMA_SPACE ", "
#define SINGLE_POINT "."

/* brackets */
#define SQR_BRACKET_OPEN "["
#define SQR_BRACKET_CLOSE "]"

#define RND_BRACKET_OPEN "("
#define RND_BRACKET_CLOSE ")"

/* other */
#define NO_SYMBOL ""

/* special symbols and
 * formatting symbols */
#define FNAME_OFFSET "%-32s"
#define LINE_NO_FMT "%6d"
#define TEST_STATUS_OFFSET "%32s"
#define TEST_STATUS_OFFSET_DBL "%8s"

#ifndef INT32_FMT_TEMPL
#  define INT32_FMT_TEMPL "%8d"
#endif

#ifndef INT64_FMT_TEMPL
#  define INT64_FMT_TEMPL "%16ld"
#endif

#ifndef DBL_FMT_TEMPL
#  define DBL_FMT_TEMPL "%10.6lf"
#endif

#ifndef DBL_EPS_TOLERANCE
#  define DBL_EPS_TOLERANCE "%10.9lf"
#endif

#ifndef PTR_FMT_TEMPL
#  define PTR_FMT_TEMPL "%8p"
#endif

#define _T_EOL "\n"

/* macro-template for passed test message 
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d'
 *
 * Returns:
 *   Joined literal with format directives. */
#define _PASS_MSG(__type) (             \
        FNAME_OFFSET                    \
        SINGLE_SPACE                    \
        SQR_BRACKET_OPEN                \
        EXPECTED                        \
        __type                          \
        COMMA_SPACE                     \
        GOT                             \
        __type                          \
        SQR_BRACKET_CLOSE               \
        TEST_STATUS_OFFSET              \
        SINGLE_POINT                    \
        _T_EOL)

/* macro-template for failed test message 
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d'
 *
 * Returns:
 *   Joined literal with format directives. */
#define _FAIL_MSG(__type) (             \
        FNAME_OFFSET                    \
        SINGLE_SPACE                    \
        RND_BRACKET_OPEN                \
        LINE_STR                        \
        LINE_NO_FMT                     \
        RND_BRACKET_CLOSE               \
        SINGLE_SPACE                    \
        SQR_BRACKET_OPEN                \
        EXPECTED                        \
        __type                          \
        COMMA_SPACE                     \
        GOT                             \
        __type                          \
        SQR_BRACKET_CLOSE               \
        TEST_STATUS_OFFSET              \
        SINGLE_POINT                    \
        _T_EOL)

/* macro-template for failed test message 
 * for ne (not equal) comparison.
 *
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d'
 *
 * Returns:
 *   Joined literal with format directives. */
#define _FAIL_NE_MSG(__type, _ne_eps, __eps_tol) (          \
        FNAME_OFFSET                                        \
        SINGLE_SPACE                                        \
        RND_BRACKET_OPEN                                    \
        LINE_STR                                            \
        LINE_NO_FMT                                         \
        RND_BRACKET_CLOSE                                   \
        SINGLE_SPACE                                        \
        SQR_BRACKET_OPEN                                    \
        __type                                              \
        SINGLE_SPACE                                        \
        IS_EQ_TO                                            \
        __type                                              \
        _ne_eps                                             \
        __eps_tol                                           \
        SQR_BRACKET_CLOSE                                   \
        TEST_STATUS_OFFSET                                  \
        SINGLE_POINT                                        \
        _T_EOL)

/* macro-template for passed null-pointer check */
#define _PASS_NULL_PTR(__type) (        \
        FNAME_OFFSET                    \
        SINGLE_SPACE                    \
        SQR_BRACKET_OPEN                \
        PTR_                            \
        __type                          \
        SQR_BRACKET_CLOSE               \
        TEST_STATUS_OFFSET              \
        SINGLE_POINT                    \
        _T_EOL)

/* macro-template for failed null-pointer check */
#define _FAIL_NULL_PTR(__type, __msg) ( \
        FNAME_OFFSET                    \
        SINGLE_SPACE                    \
        RND_BRACKET_OPEN                \
        LINE_STR                        \
        LINE_NO_FMT                     \
        RND_BRACKET_CLOSE               \
        SINGLE_SPACE                    \
        SQR_BRACKET_OPEN                \
        __msg                           \
        __type                          \
        SQR_BRACKET_CLOSE               \
        TEST_STATUS_OFFSET              \
        SINGLE_POINT                    \
        _T_EOL)

/* macro-template for passed test message 
 * (use with floating point values).
 * Params:
 *   __type:    format string with arg type
 *              that used in 'printf' function.
 *              Example:
 *                - '%6d'
 *
 *   __eps_tol: epsilon tolerance for
 *              additional result control.
 *              (use DBL_e_X macro)
 *
 * Returns:
 *   Joined literal with format directives. */
#define _PASS_MSG_DBL(__type, __eps_tol) (          \
        FNAME_OFFSET                                \
        SINGLE_SPACE                                \
        SQR_BRACKET_OPEN                            \
        EXPECTED                                    \
        __type                                      \
        COMMA_SPACE                                 \
        GOT                                         \
        __type                                      \
        COMMA_SPACE                                 \
        EPSILON                                     \
        __eps_tol                                   \
        SQR_BRACKET_CLOSE                           \
        TEST_STATUS_OFFSET_DBL                      \
        SINGLE_POINT                                \
        _T_EOL)

/* macro-template for fail test message 
 * (use with floating point values).
 * Params:
 *   __type:    format string with arg type
 *              that used in 'printf' function.
 *              Example:
 *                - '%6d'
 *
 *   __eps_tol: epsilon tolerance for
 *              additional result control.
 *              (use DBL_e_X macro)
 *
 * Returns:
 *   Joined literal with format directives. */
#define _FAIL_MSG_DBL(__type, __eps_tol) (          \
        FNAME_OFFSET                                \
        SINGLE_SPACE                                \
        RND_BRACKET_OPEN                            \
        LINE_STR                                    \
        LINE_NO_FMT                                 \
        RND_BRACKET_CLOSE                           \
        SINGLE_SPACE                                \
        SQR_BRACKET_OPEN                            \
        EXPECTED                                    \
        __type                                      \
        COMMA_SPACE                                 \
        GOT                                         \
        __type                                      \
        COMMA_SPACE                                 \
        EPSILON                                     \
        __eps_tol                                   \
        SQR_BRACKET_CLOSE                           \
        TEST_STATUS_OFFSET_DBL                      \
        SINGLE_POINT                                \
        _T_EOL)

/* macro for set message about test pass.
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   E:      Expected value;
 *   G:      Got value. */
#define TEST_PASSED_MSG(__type, FN, E, G) (printf(_PASS_MSG(__type), FN, E, G, PASSED))

/* macro for print pointer success msg
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   G:      Got value. */
#define PTR_NULL_TEST_PASSED(__type, FN, G) (printf(_PASS_NULL_PTR(__type), FN, G, PASSED))

/* macro for print pointer test failure
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   G:      Got value. */
#define PTR_NULL_TEST_FAILED(__type, FN, LN, G) (printf(_FAIL_NULL_PTR(__type, PTR_), FN, LN, G, FAILED))

/* macro for print pointer test failure
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   G:      Got value. */
#define PTR_NE_NULL_TEST_FAILED(__type, FN, LN, G) (printf(_FAIL_NULL_PTR(__type, NULLPTR), FN, LN, G, FAILED))

/* macro for set message about test pass.
 * (use with floating point values).
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   E:      Expected value;
 *   G:      Got value;
 *   EPS:    current floating point tolerance. */
#define TEST_PASSED_MSG_DBL(__type, FN, E, G, EPS) (printf(_PASS_MSG_DBL(__type, DBL_EPS_TOLERANCE), \
                                                    FN, E, G, EPS, PASSED))

/* macro for set message about test fail.
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   E:      Expected value;
 *   G:      Got value. */
#define TEST_FAILED_MSG(__type, FN, LN, E, G) (printf(_FAIL_MSG(__type), FN, LN, E, G, FAILED))

/* macro for set message about test fail
 * if values are not equal.
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   E:      Expected value;
 *   G:      Got value. */
#define TEST_NE_FAILED_MSG(__type, FN, LN, E, G) (printf(_FAIL_NE_MSG(__type, NO_SYMBOL, NO_SYMBOL), FN, LN, E, G, FAILED))

/* macro for set message about test fail.
 * (use with floating point values).
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   E:      Expected value;
 *   G:      Got value;
 *   EPS:    current floating point tolerance. */
#define TEST_FAILED_MSG_DBL(__type, FN, LN, E, G, EPS) (printf(_FAIL_MSG_DBL(__type, DBL_EPS_TOLERANCE), \
                                                        FN, LN, E, G, EPS, FAILED))

/* macro for set message about test fail.
 * (use with floating point values).
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   E:      Expected value;
 *   G:      Got value;
 *   EPS:    current floating point tolerance. */
#define TEST_NE_FAILED_MSG_DBL(__type, FN, LN, E, G, EPS) (printf(_FAIL_NE_MSG(__type, NE_EPSILON, DBL_EPS_TOLERANCE), \
                                                        FN, LN, E, G, EPS, FAILED))


/* custom epsilons */
#define DBL_e_9 1e-9
#define DBL_e_8 1e-8
#define DBL_e_7 1e-7
#define DBL_e_6 1e-6
#define DBL_e_5 1e-5
#define DBL_e_4 1e-4
#define DBL_e_3 1e-3
#define DBL_e_2 1e-2
#define DBL_e_1 1e-1

/* type casting */
#define eq_int32(a, b) ((int) a == (int) b)

#define ne_int32(a, b) ((int) a != (int) b)

#define eq_double64(a, b, eps) ((fabs((double) a - (double) b) <= (double) eps))

#define ne_double64(a, b, eps) ((fabs((double) a - (double) b) > (double) eps))

#define eq_null_ptr(a) ((void *) a == NULL)

#define ne_null_ptr(a) ((void *) a != NULL)

#define LINE() (__LINE__)

enum test_fail_mode {
    ABRT = 0x1,
    CONT = 0x2,
};

/* flagss for extend tests behaviour. */
enum test_check_mode {
    CHKEQ = 0x4,
    CHKNE = 0x8,
};

/* exclude ABRT and CONT from flags. */
#define EXCLUDE_ABRT 0xC

static int 
check_null_ptr_result(int res, void * ptr, char * fname, int line, int flags) {
    if (res) {
#ifdef ALMSG
        PTR_NULL_TEST_PASSED(PTR_FMT_TEMPL, fname, ptr);                           
#endif
    }
    else {
        switch (flags & EXCLUDE_ABRT) {
            case CHKEQ:
                PTR_NULL_TEST_FAILED(PTR_FMT_TEMPL, fname, line, ptr);                     
                break;
            case CHKNE:
                PTR_NE_NULL_TEST_FAILED(PTR_FMT_TEMPL, fname, line, ptr);
                break;
            default:
                perror("UNDEFINED FLAG");
                break;
        }

        if (flags & ABRT)
#ifdef ABORT
            abort();                                                                    
#else
            exit(1);
#endif
    }

    return res;
}

static int
check_int32_result(int res, int exp, int got, char *fname, int line, int flags) {
    if (res) {
#ifdef ALMSG
        TEST_PASSED_MSG(INT32_FMT_TEMPL, fname, exp, got);
#endif
    }
    else {
        /* means 1001 or 0110 ^ 0011 => 1000 or 0100 (8 or 4) */
        switch (flags & EXCLUDE_ABRT) {
            case CHKEQ:
                TEST_FAILED_MSG(INT32_FMT_TEMPL, fname, line, exp, got);
                break;
            case CHKNE:
                TEST_NE_FAILED_MSG(INT32_FMT_TEMPL, fname, line, exp, got);
                break;
            default:
                perror("UNDEFINED FLAG");
                break;
        }

        if (flags & ABRT)
#ifdef ABORT
            abort();                                                                    
#else
            exit(1);
#endif
    }

    return res;
}

static int
check_dbl_result(int res, double exp, double got, double eps, char *fname, int line, int flags) {
    if (res) {
#ifdef ALMSG
        TEST_PASSED_MSG_DBL(DBL_FMT_TEMPL, fname, exp, got, eps);
#endif
    }
    else {
        switch (flags & EXCLUDE_ABRT) {
            case CHKEQ:
                TEST_FAILED_MSG_DBL(DBL_FMT_TEMPL, fname, line, exp, got, eps);
                break;
            case CHKNE:
                TEST_NE_FAILED_MSG_DBL(DBL_FMT_TEMPL, fname, line, exp, got, eps);
                break;
            default:
                perror("UNDEFINED FLAG");
                break;
        }

        if (flags & ABRT)
#ifdef ABORT
            abort();                                                                    
#else
            exit(1);
#endif
    }

    return res;
}

/* ASSERT_EQ_PTR_NULL check that pointer is eq to NULL */
#define ASSERT_EQ_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = eq_null_ptr(RES);                                                         \
        check_null_ptr_result(success, RES, F_NAME, LINE, CHKEQ | ABRT);                        \
    }

#define ASSERT_NE_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = ne_null_ptr(RES);                                                         \
        check_null_ptr_result(success, RES, F_NAME, LINE, CHKNE | ABRT);                        \
    }

#define EXPECT_EQ_PTR_NULL(RES, F_NAME, STATE, LINE)                                            \
    {                                                                                           \
        int success = eq_null_ptr(RES);                                                         \
        *STATE = check_null_ptr_result(success, RES, F_NAME, LINE, CHKEQ | CONT);               \
    }

#define EXPECT_NE_PTR_NULL(RES, F_NAME, STATE, LINE)                                            \
    {                                                                                           \
        int success = ne_null_ptr(RES);                                                         \
        *STATE = check_null_ptr_result(success, RES, F_NAME, LINE, CHKNE | CONT);               \
    }


/* ASSERT_EQ check that two args are equal
 * or will abort execution. */
#define ASSERT_EQ_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = eq_int32(RES, EXP);                                                       \
        check_int32_result(success, EXP, RES, F_NAME, LINE, CHKEQ | ABRT);                      \
    }

#define ASSERT_NE_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = ne_int32(RES, EXP);                                                       \
        check_int32_result(success, EXP, RES, F_NAME, LINE, CHKNE | ABRT);                      \
    }

/* will not abort() routine execution, only
 * write to stderr about test failure or success. */
#define EXPECT_EQ_INT32(RES, EXP, F_NAME, STATE, LINE)                                          \
    {                                                                                           \
        int success = eq_int32(RES, EXP);                                                       \
        *STATE = check_int32_result(success, EXP, RES, F_NAME, LINE, CHKEQ | CONT);             \
    }

#define EXPECT_NE_INT32(RES, EXP, F_NAME, STATE, LINE)                                          \
    {                                                                                           \
        int success = ne_int32(RES, EXP);                                                       \
        *STATE = check_int32_result(success, EXP, RES, F_NAME, LINE, CHKNE | CONT);             \
    }

/* assert to double */
#define ASSERT_EQ_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = eq_double64(RES, EXP, EPSILON);                                           \
        check_dbl_result(success, EXP, RES, EPSILON, F_NAME, LINE, CHKEQ | ABRT);               \
    }

#define ASSERT_NE_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = ne_double64(RES, EXP, EPSILON);                                           \
        check_dbl_result(success, EXP, RES, EPSILON, F_NAME, LINE, CHKNE | ABRT);               \
    }

/* EXPECT waiting for pointer for test result */
#define EXPECT_EQ_DBL(RES, EXP, STATE, EPSILON, F_NAME, LINE)                                   \
    {                                                                                           \
        int success = eq_double64(RES, EXP, EPSILON);                                           \
        *STATE = check_dbl_result(success, EXP, RES, EPSILON, F_NAME, LINE, CHKEQ | CONT);      \
    }

#define EXPECT_NE_DBL(RES, EXP, STATE, EPSILON, F_NAME, LINE)                                   \
    {                                                                                           \
        int success = ne_double64(RES, EXP, EPSILON);                                           \
        *STATE = check_dbl_result(success, EXP, RES, EPSILON, F_NAME, LINE, CHKNE | CONT);      \
    }

#endif /* _CTEST_H */
