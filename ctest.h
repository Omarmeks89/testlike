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

#ifndef _CTEST_H
#define _CTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#define PASSED "PASSED"
#define FAILED "FAILED"

/* v0.1.1 new string format */
#define MSG_TEMPL                               "%-32s %16s %32s %8s.\n"
#define LINE_FMT                                "(LINE %8d)"
#define EXP_GOT_INT32                           "[EXP.: %12d, GOT: %12d]" 
#define EXP_GOT_DBL                             "[EXP.: %10.6lf, GOT: %10.6lf, EPS.: %10.6lf]"
#define N_NULLPTR                               "[PTR NOT NULL. ADDR.: %8p]"
#define NULLPTR                                 "[NULLPTR: %8p]"
#define DBL_ISEQ_TO                             "[%10.6lf EQ TO %10.6lf. EPS.: %10.6lf]"
#define INT32_ISEQ_TO                           "[%12d EQ TO %12d]"

#ifndef MSG_BUF_SIZE
#   define MSG_BUF_SIZE 256
#endif

#define SPACE " "

/* new macro-formatter */
#define build_msg(tmpl, fname, ...) (printf(tmpl, fname, __VA_ARGS__))

/* build part of msg string */
#define _build_msg_part(tmpl, buf, ...) (sprintf(buf, tmpl, __VA_ARGS__))

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

#ifdef QUIET
#   define on_success(...)
# else
#   define on_success(...) (printf(__VA_ARGS__))
#endif

#define on_fail(...) (printf(__VA_ARGS__))

/* ASSERT_EQ_PTR_NULL check that pointer is eq to NULL */
#define ASSERT_EQ_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        char msg[MSG_BUF_SIZE];                                                                 \
        int success = eq_null_ptr(RES);                                                         \
        if (success) {                                                                          \
            _build_msg_part(NULLPTR, msg, RES);                                                \
            on_success(MSG_TEMPL, F_NAME, SPACE, msg, PASSED);                                  \
        }                                                                                       \
        else {                                                                                  \
            char ln[32];                                                                        \
            _build_msg_part(N_NULLPTR, msg, RES);                                              \
            _build_msg_part(LINE_FMT, ln, LINE);                                               \
            on_fail(MSG_TEMPL, F_NAME, ln, msg, FAILED);                                        \
            exit(EINVAL);                                                                       \
        }                                                                                       \
    }

#define ASSERT_NE_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = ne_null_ptr(RES);                                                         \
    }

#define EXPECT_EQ_PTR_NULL(RES, F_NAME, STATE, LINE)                                            \
    {                                                                                           \
        int success = eq_null_ptr(RES);                                                         \
    }

#define EXPECT_NE_PTR_NULL(RES, F_NAME, STATE, LINE)                                            \
    {                                                                                           \
        int success = ne_null_ptr(RES);                                                         \
    }

#define ASSERT_EQ_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = eq_int32(RES, EXP);                                                       \
    }

#define ASSERT_NE_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = ne_int32(RES, EXP);                                                       \
    }

#define EXPECT_EQ_INT32(RES, EXP, F_NAME, STATE, LINE)                                          \
    {                                                                                           \
        int success = eq_int32(RES, EXP);                                                       \
    }

#define EXPECT_NE_INT32(RES, EXP, F_NAME, STATE, LINE)                                          \
    {                                                                                           \
        int success = ne_int32(RES, EXP);                                                       \
    }

/* assert to double */
#define ASSERT_EQ_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = eq_double64(RES, EXP, EPSILON);                                           \
    }

#define ASSERT_NE_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = ne_double64(RES, EXP, EPSILON);                                           \
    }

#define EXPECT_EQ_DBL(RES, EXP, STATE, EPSILON, F_NAME, LINE)                                   \
    {                                                                                           \
        int success = eq_double64(RES, EXP, EPSILON);                                           \
    }

#define EXPECT_NE_DBL(RES, EXP, STATE, EPSILON, F_NAME, LINE)                                   \
    {                                                                                           \
        int success = ne_double64(RES, EXP, EPSILON);                                           \
    }

#endif /* _CTEST_H */
