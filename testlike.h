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
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

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
        if ((localestr[i] ^ ASCII_HEAD) == 0)
            continue;

        if (localestr[i] == POINT_SYMB)
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

/* define UTF8 tail limits */
#define UTF8_2BYTES_RNG_START   0xC2
#define UTF8_2BYTES_RNG_END     0xDF

#define UTF8_3BYTES_SEQ_START   0xE0
#define UTF8_3BYTES_SEQ_END     0xEF
#define UTF8_3BYTES_MBYTE_MIN   0xA0
#define UTF8_3BYTES_MBYTE_MAX   0x9F

#define UTF8_4BYTES_SEQ_START   0xF0
#define UTF8_4BYTES_SEQ_END     0xF4

#define ASCII_LIMIT             0x7F       /**< max possible ascii symbol */

#define UTF16_SURR_START        0xD800
#define UTF16_SURR_END          0xDFFF

#define BYTE_MASK               0x000000FF

#define UTF8_BOM                0xEFBBBF

/* define constants for bytes count in wide char */
#define UTF8_2BYTES             2
#define UTF8_3BYTES             3
#define UTF8_4BYTES             4


enum match_error {
    NOERRS = -1,
    NOSTR  = -2,
    NOTUTF = -3,
    STROVF = -4,
    UNSLOC = -5,                            /**< unsupporetd locale. support UTF-8 only */
    INVARG = -6,
    NOTEQS = -7,
    INTLGE = -8,                            /**< means error in internal logic */
    UTFBOM = -9,                            /**< special case for UTF8 BOM */
};

/* =================== RFC 3629 (UTF-8) =================================================== */

/* eq function */
int eq_bytes(const char *s, const char *c)
{
    return ((*s ^ *c) != 0) ? (int) 1 : (int) 0;
}

int is_utf8_2byte_symbol(const char *str, const char *cur, int *pos,
                            int (*eq_func)(const char *a, const char *b));
int is_utf8_3byte_symbol(const char *str, const char *cur, int *pos,
                            int (*eq_func)(const char *a, const char *b));
int is_utf8_4byte_symbol(const char *str, const char *cur, int *pos,
                            int (*eq_func)(const char *a, const char *b));
int encode_utf8_symbol(const char *str, const char *cur, wchar_t *smb,
                        int bytes_cnt, int (* eq_func)(const char *a, const char *b));

int utf8_streq(const char *smpl, const char *curr, int *error)
{
    int i = 0, pos = 0, res = 0, str_len = 0;
    unsigned char ctrl = 0;

    if (error == NULL)
        return INVARG;

    str_len = (strchr(smpl, 0) - smpl) / sizeof(char);
    if (str_len < 0)
    {
        *error = INVARG;
        return res;
    }

    for (; i < str_len; )
    {
        res++;
        ctrl = (unsigned char) curr[i] & BYTE_MASK;
        if (ctrl <= ASCII_LIMIT)
        {
            /* TODO: move into ASCII handler */
            if (eq_bytes(smpl + i, curr + i) == 1)
            {
                *error = NOTEQS;
                break;
            }

            i++;
            continue;
        }

        if ((ctrl >= UTF8_2BYTES_RNG_START) && (ctrl <= UTF8_2BYTES_RNG_END))
            pos = is_utf8_2byte_symbol(smpl + i, curr + i, &i, &eq_bytes);

        else if ((ctrl >= UTF8_3BYTES_SEQ_START) && (ctrl <= UTF8_3BYTES_SEQ_END))
        {
            pos = is_utf8_3byte_symbol(smpl + i, curr + i, &i, &eq_bytes);
            if (pos == UTFBOM)
            {
                /* is required to skip UTF-8 BOM, so we
                 * decrement res, and set pos as 1 (as a valid UTF-8 symbol)
                 */
                res--, pos = 1;
            }
        }

        else if ((ctrl >= UTF8_4BYTES_SEQ_START) && (ctrl <= UTF8_4BYTES_SEQ_END))
            pos = is_utf8_4byte_symbol(smpl + i, curr + i, &i, &eq_bytes);

        if (pos <= 0)
        {
            /* means symbol mismatch */
            if (pos < 0)
                *error = pos;
            else {
                /* pos = 0, means no UTF symbol was detected */
                *error = NOTUTF;
            }
            break;
        }

        /* cleanup previous value */
        pos = 0;
    }

    return res;
}

int is_utf8_2byte_symbol(const char *str, const char *cur, int *pos,
                            int (*eq_func)(const char *a, const char *b))
{
    wchar_t symb = 0;
    int valid = 0;

    if (pos == NULL)
        return INVARG;

    valid = encode_utf8_symbol(str, cur, &symb, UTF8_2BYTES, eq_func);
    if (valid != 0)
        return valid;

    *pos += 2;
    if ((symb >= 0xC280) && (symb <= 0xDFBF))
    {
        if ((symb >= (wchar_t) UTF16_SURR_START) && (symb <= (wchar_t) UTF16_SURR_END))
            return NOTUTF;
        return 1;
    }
    return 0;
}

/** \fn set_utf8_wchar set utf8 encoded bytes
 * into smb
 * @param smb pointer on wchar_t var
 * @param bytes_cnt significant bytes count
 * @return 0 if done success or 1
 */
int encode_utf8_symbol(const char *str, const char *cur, wchar_t *smb,
                        int bytes_cnt, int (* eq_func)(const char *a, const char *b))
{
    int shift = 0, i = 0, equal = 0;

    if ((smb == NULL) || (str == NULL) || (cur == NULL) || (eq_func == NULL))
        return INVARG;

    if ((bytes_cnt <= 0) || (bytes_cnt > 4))
        return INVARG;

    for (i = 0; i < bytes_cnt; i++)
    {
        equal = eq_func(str + i, cur + i);
        if (equal != 0)
            return NOTEQS;

        shift = 8 * (bytes_cnt - (1 + i));
        if (shift < 0)
            /* means logical error here */
            return INTLGE;

        *smb |= ((wchar_t) str[i] & BYTE_MASK) << shift; 
    }

    return 0;
}

/** \fn is_utf8_3byte_symbol detect 3 bytes long utf-8 symbol
 * and incrment pos on 3 bytes.
 * @param str - string sample,
 * @param cur - current string,
 * @param pos - length in bytes (for shift ptr position),
 * @param eq_func - function that compare two bytes on equality
 * @return result code (x > 0) or error code (x < 0)
 */
int is_utf8_3byte_symbol(const char *str, const char *cur, int *pos,
                            int (*eq_func)(const char *a, const char *b))
{
    wchar_t symb = 0;
    int encoding_res = 0;

    if (pos == NULL)
        return INVARG;

    encoding_res = encode_utf8_symbol(str, cur, &symb, UTF8_3BYTES, eq_func);
    if (encoding_res != 0)
        return encoding_res;

    *pos += 3;
    if ((symb >= 0xE0A080) && (symb <= 0xE0BFBF))
        return 1;

    else if ((symb >= 0xE18080) && (symb <= 0xECBFBF))
        return 1;

    else if ((symb >= 0xED8080) && (symb <= 0xED9FBF))
        return 1;

    else if ((symb >= 0xEE8080) && (symb <= 0xEFBFBF))
    {
        /* check UTF8 BOM */
        if (symb == UTF8_BOM)
        {
            return UTFBOM;
        }
        return 1;
    }
    return 0;
}

int is_utf8_4byte_symbol(const char *str, const char *cur, int *pos,
                            int (*eq_func)(const char *a, const char *b))
{
    wchar_t symb = 0;
    int encoding_res = 0;

    if (pos == NULL)
        return INVARG;

    encoding_res = encode_utf8_symbol(str, cur, &symb, UTF8_4BYTES, eq_func);
    if (encoding_res != 0)
        return encoding_res;

    *pos += 4;
    if ((symb >= (wchar_t) 0xF0908080) && (symb <= (wchar_t) 0xF0BFBFBF))
        return 1;

    else if ((symb >= (wchar_t) 0xF1808080) && (symb <= (wchar_t) 0xF3BFBFBF))
        return 1;

    else if ((symb >= (wchar_t) 0xF4808080) && (symb <= (wchar_t) 0xF48FBFBF))
        return 1;

    return 0;
}

#ifdef __cplusplus
}
#endif                  /* __CPLUSPLUS */

#endif                  /* _CTEST_H */
