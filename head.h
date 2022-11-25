#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char u8;

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void plus(const char *previous, const char *last, char **result);
void minus(const char *previous, const char *last, char **result);
void multiply(const char *previous, const char *last, char **result);
void devide(const char *previous, const char *last, size_t fraction_len, char **result);

#define move()                                                                          \
    do                                                                                  \
    {                                                                                   \
        (*result)[i] = *((p_len > l_len ? pre_point : last_point) + max(p_len, l_len)); \
        i++;                                                                            \
        p_len > l_len ? p_len-- : l_len--;                                              \
    } while (0)

void lib_plus(const char *previous, const char *last, char **result, char signal);
void reverse(char **result);
void add_MinusSign(char **result);
void Del0(char **result);

#define Bisection()                                       \
    _Bool big_flag = 0;                                   \
    char small = '0';                                     \
    char big = '9';                                       \
    char now[2];                                          \
    now[0] = '5';                                         \
    now[1] = 0;                                           \
    char *mul_result = (char *)malloc(1);                 \
    while (!(*result)[index])                             \
    {                                                     \
        multiply(now, last, &mul_result);                 \
        switch (compare(mul_result, temp_p))              \
        {                                                 \
        case 0:                                           \
            (*result)[index] = now[0];                    \
            break;                                        \
        case 1:                                           \
            big = now[0];                                 \
            now[0] = (now[0] + small) / 2;                \
            break;                                        \
        case -1:                                          \
            if (now[0] == '8')                            \
            {                                             \
                minus(temp_p, mul_result, &minus_result); \
                if (compare(minus_result, last) >= 0)     \
                {                                         \
                    now[0] = '9';                         \
                    (*result)[index] = now[0];            \
                    multiply(now, last, &mul_result);     \
                    break;                                \
                }                                         \
            }                                             \
            if (big - small <= 2)                         \
                (*result)[index] = now[0];                \
            small = now[0];                               \
            now[0] = (now[0] + big + 1) / 2;              \
            break;                                        \
        }                                                 \
    }                                                     \
    minus(temp_p, mul_result, &minus_result);             \
    break
