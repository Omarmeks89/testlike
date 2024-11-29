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
#include <stdarg.h>

/* for string comparison */
#include <locale.h>
#include <string.h>

#define PASSED "PASSED"
#define FAILED "FAILED"

/* v0.1.1 new string format */
#define MSG_TEMPL                               "%-32s %16s %64s %16s.\n"
#define LINE_FMT                                "(LINE %d)"
#define EXP_GOT_INT32                           "[EXP.: %d, GOT: %d]" 
#define EXP_GOT_DBL                             "[EXP.: %.6lf, GOT: %.6lf, EPS.: %.6lf]"
#define N_NULLPTR                               "[PTR NOT NULL. ADDR.: %p]"
#define NULLPTR                                 "[NULLPTR: %p]"
#define DBL_ISEQ_TO                             "[%.6lf == %.6lf. EPS.: %.6lf]"
#define DBL_ISNE_TO                             "[%.6lf != %.6lf. EPS.: %.6lf]"
#define INT32_ISEQ_TO                           "[%d == %d]"
#define INT32_ISNE_TO                           "[%d != %d]"

#define MSG_BUF_SIZE 64
#define LINE_BUF_SIZE 16

#define SPACE " "

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
#   define _ALLOC 0
# else
#   define _ALLOC 1
#endif

void _printmsg(FILE * stream, const char *fmt, ...) {
    int w = 0;
    va_list v;

    va_start(v, fmt);
    w = vfprintf(stream, fmt, v);
    if (w <= 0)
        exit(errno);

    va_end(v);
}

#if defined(ESTRM)
#   if ESTRM== 2
#       define _ES stderr
#   elif ESTRM==1
#       define _ES stdout
#   else
#       error "invalid errstream no. Use 1 or 2"
#   endif
#else
#   define _ES stderr
#endif

#if defined(MSTRM)
#   if MSTRM==1
#       define _MS stdout
#   elif MSTRM==2
#       define _MS stderr
#   else
#       error "invalid errstream no. Use 1 or 2"
#   endif
#else
#   define _MS stdout
#endif

#define _BUF_TAIL(parts) parts

#define notify(ST, S, F, FN, LN, ABRT, ...)                                                     \
    {                                                                                           \
        char *msg, *ln;                                                                         \
        int w = 0;                                                                              \
        if ((ST) && (_ALLOC)) {                                                                 \
            msg = (char *) calloc(MSG_BUF_SIZE, sizeof(char));                                  \
            if (msg == NULL)                                                                    \
                exit(errno);                                                                    \
            w = _build_msg_part(S, msg, __VA_ARGS__);                                           \
            if (w < 0)                                                                          \
                exit(errno);                                                                    \
            _printmsg(_MS, MSG_TEMPL, FN, SPACE, msg, PASSED);                                  \
            free(msg);                                                                          \
        }                                                                                       \
        else {                                                                                  \
            msg = (char *) calloc(MSG_BUF_SIZE + LINE_BUF_SIZE + _BUF_TAIL(2), sizeof(char));   \
            if (msg == NULL)                                                                    \
                exit(errno);                                                                    \
            ln = msg + MSG_BUF_SIZE;                                                            \
            w = _build_msg_part(F, msg, __VA_ARGS__);                                           \
            if (w < 0)                                                                          \
                exit(errno);                                                                    \
            w = _build_msg_part(LINE_FMT, ln, LN);                                              \
            if (w < 0)                                                                          \
                exit(errno);                                                                    \
            _printmsg(_ES, MSG_TEMPL, FN, ln, msg, FAILED);                                     \
            if (ABRT)                                                                           \
                exit(EINVAL);                                                                   \
            free(msg);                                                                          \
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

#define POINT_SYMB '.'

/* max symbols count before '.' symbol */
#define HEAD_SYMS_LIM                           10
#define ASCII_HEAD                              0x80

/* return 1 if 'UTF-8' is found or 0 */
int is_locale_utf8(const char *localestr)
{
    int i = 0;
    const char *loc = "UTF-8";

    /* check that is ASCII symbol */
    for (i = 0; i < HEAD_SYMS_LIM; i++)
    {
        if ((*(localestr + i) ^ ASCII_HEAD) == 0)
            continue;

        if (*(localestr + i) == POINT_SYMB)
        {
            /* this is a point
             * move i forward by one and break */
            i++;
            break;
        }
    }

    if (i == HEAD_SYMS_LIM)
        return 0;

    return strcoll(localestr + i, loc);
}

/* strings comparison */
int testlike_strcmp_utf8(void)
{
    char *string = NULL;

    string = setlocale(LC_COLLATE, "");
    if (string == NULL)
        exit(errno);

    return is_locale_utf8(string);
}

/* function, that compare two strings symbol by symbol
 * and return index (i > 0), that not match, or will return 0
 */
int check_utf8_strings_match(const char *smpl, const char *curr, int *error)
{
}

#endif /* _CTEST_H */
