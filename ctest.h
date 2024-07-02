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
#define MSG_TEMPL                               "%-32s %16s %64s %16s.\n"
#define LINE_FMT                                "(LINE %8d)"
#define EXP_GOT_INT32                           "[EXP.: %12d, GOT: %12d]" 
#define EXP_GOT_DBL                             "[EXP.: %10.6lf, GOT: %10.6lf, EPS.: %10.6lf]"
#define N_NULLPTR                               "[PTR NOT NULL. ADDR.: %8p]"
#define NULLPTR                                 "[NULLPTR: %8p]"
#define DBL_ISEQ_TO                             "[%10.6lf EQ TO %10.6lf. EPS.: %10.6lf]"
#define DBL_ISNE_TO                             "[%10.6lf NE TO %10.6lf. EPS.: %10.6lf]"
#define INT32_ISEQ_TO                           "[%12d EQ TO %12d]"
#define INT32_ISNE_TO                           "[%12d NE TO %12d]"

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

#define ABORT 1
#define CONTINUE 0

#ifdef QUIET
#   define on_success(...)
# else
#   define on_success(...) (printf(__VA_ARGS__))
#endif

#define on_fail(...) (printf(__VA_ARGS__))

#define notify(ST, S, F, FN, LN, ABRT, ...)                                                     \
    {                                                                                           \
        char msg[MSG_BUF_SIZE];                                                                 \
        if (ST) {                                                                               \
            _build_msg_part(S, msg, __VA_ARGS__);                                               \
            on_success(MSG_TEMPL, FN, SPACE, msg, PASSED);                                      \
        }                                                                                       \
        else {                                                                                  \
            char ln[MSG_BUF_SIZE / 4];                                                          \
            _build_msg_part(F, msg, __VA_ARGS__);                                               \
            _build_msg_part(LINE_FMT, ln, LN);                                                  \
            on_fail(MSG_TEMPL, FN, ln, msg, FAILED);                                            \
            if (ABRT)                                                                           \
                exit(EINVAL);                                                                   \
        }                                                                                       \
    }


/* ASSERT_EQ_PTR_NULL check that pointer is eq to NULL */
#define ASSERT_EQ_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = eq_null_ptr(RES);                                                         \
        notify(success, NULLPTR, N_NULLPTR, F_NAME, LINE, ABORT, RES);                          \
    }

#define ASSERT_NE_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = ne_null_ptr(RES);                                                         \
        notify(success, N_NULLPTR, NULLPTR, F_NAME, LINE, ABORT, RES);                          \
    }

#define EXPECT_EQ_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = eq_null_ptr(RES);                                                         \
        notify(success, NULLPTR, N_NULLPTR, F_NAME, LINE, CONTINUE, RES);                       \
    }

#define EXPECT_NE_PTR_NULL(RES, F_NAME, LINE)                                                   \
    {                                                                                           \
        int success = ne_null_ptr(RES);                                                         \
        notify(success, N_NULLPTR, NULLPTR, F_NAME, LINE, CONTINUE, RES);                       \
    }

/* marco for int32 values */
#define ASSERT_EQ_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = eq_int32(RES, EXP);                                                       \
        notify(success, EXP_GOT_INT32, EXP_GOT_INT32, F_NAME, LINE, ABORT, EXP, RES);           \
    }

#define ASSERT_NE_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = ne_int32(RES, EXP);                                                       \
        notify(success, INT32_ISNE_TO, INT32_ISEQ_TO, F_NAME, LINE, ABORT, EXP, RES);           \
    }

#define EXPECT_EQ_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = eq_int32(RES, EXP);                                                       \
        notify(success, EXP_GOT_INT32, EXP_GOT_INT32, F_NAME, LINE, CONTINUE, EXP, RES);        \
    }

#define EXPECT_NE_INT32(RES, EXP, F_NAME, LINE)                                                 \
    {                                                                                           \
        int success = ne_int32(RES, EXP);                                                       \
        notify(success, INT32_ISNE_TO, INT32_ISEQ_TO, F_NAME, LINE, CONTINUE, EXP, RES);        \
    }

/* assert to double */
#define ASSERT_EQ_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = eq_double64(RES, EXP, EPSILON);                                           \
        notify(success, EXP_GOT_DBL, EXP_GOT_DBL, F_NAME, LINE, ABORT, EXP, RES, EPSILON);      \
    }

#define ASSERT_NE_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = ne_double64(RES, EXP, EPSILON);                                           \
        notify(success, DBL_ISNE_TO, DBL_ISEQ_TO, F_NAME, LINE, ABORT, EXP, RES, EPSILON);      \
    }

#define EXPECT_EQ_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = eq_double64(RES, EXP, EPSILON);                                           \
        notify(success, EXP_GOT_DBL, EXP_GOT_DBL, F_NAME, LINE, CONTINUE, EXP, RES, EPSILON);   \
    }

#define EXPECT_NE_DBL(RES, EXP, EPSILON, F_NAME, LINE)                                          \
    {                                                                                           \
        int success = ne_double64(RES, EXP, EPSILON);                                           \
        notify(success, DBL_ISNE_TO, DBL_ISEQ_TO, F_NAME, LINE, CONTINUE, EXP, RES, EPSILON);   \
    }

#endif /* _CTEST_H */
