#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char u8;

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void plus(const char *previous, const char *last, char **result);

#define move()                                                                          \
    do                                                                                  \
    {                                                                                   \
        (*result)[i] = *((p_len > l_len ? pre_point : last_point) + max(p_len, l_len)); \
        i++;                                                                            \
        p_len > l_len ? p_len-- : l_len--;                                              \
    } while (0)

size_t plus_fraction(const char *pre_point, size_t p_len, const char *last_point, size_t l_len, u8 *carry, char **result);
void plus_int(const char *previous, const char *last, const char *pre_point, const char *last_point,
              u8 *carry, char **result, size_t *position);
void reverse(char **result);
void minus(const char *previous, const char *last, char **result);
void multiply(const char *previous, const char *last, char **result);
void add_MinusSign(char **result);
void devide(const char *previous, const char *last, size_t fraction_len, char **result);
void erase0(char **result);

#define DIV()                                                                    \
    do                                                                            \
    {                                                                             \
        combine(minus_result, *tail, &temp_p);                                    \
        switch (compare(temp_p, last))                                            \
        {                                                                         \
        case 0:                                                                   \
            (*result)[index] = '1';                                               \
            minus_result = (char *)realloc(minus_result, 1);                      \
            minus_result[0] = 0;                                                  \
            break;                                                                \
        case 1:                                                                   \
        {                                                                         \
            char small = '0';                                                     \
            char big = '9';                                                       \
            char now[2];                                                          \
            now[0] = '5';                                                         \
            now[1] = 0;                                                           \
            char *mul_result = (char *)malloc(1);                                 \
            while (!(*result)[index])                                             \
            {                                                                     \
                multiply(now, last, &mul_result);                                 \
                switch (compare(mul_result, temp_p))                              \
                {                                                                 \
                case 0:                                                           \
                    (*result)[index] = now[0];                                    \
                    break;                                                        \
                case 1:                                                           \
                    if (big - small == 1 || big - small == 2)                     \
                        (*result)[index] = now[0];                                \
                    big = now[0];                                                 \
                    now[0] = (now[0] + small) / 2;                                \
                    break;                                                        \
                case -1:                                                          \
                    if (big - small == 1 || big - small == 2)                     \
                        (*result)[index] = now[0];                                \
                    small = now[0];                                               \
                    now[0] = (now[0] + big) / 2;                                  \
                    break;                                                        \
                }                                                                 \
            }                                                                     \
            minus(temp_p, mul_result, &minus_result);                             \
            temp_p = (char *)realloc(temp_p, strlen(minus_result) + 1);           \
            memcpy(temp_p, minus_result, strlen(minus_result) + 1);               \
            break;                                                                \
        }                                                                         \
        case -1:                                                                  \
            if (index)                                                            \
            {                                                                     \
                (*result)[index] = '0';                                           \
            }                                                                     \
            else                                                                  \
            {                                                                     \
                minus_result = (char *)realloc(minus_result, strlen(temp_p) + 1); \
                memcpy(minus_result, temp_p, strlen(temp_p));                     \
                minus_result[strlen(temp_p)] = 0;                                 \
            }                                                                     \
            break;                                                                \
        }                                                                         \
        if ((*result)[index])                                                     \
            index++;                                                              \
        tail++;                                                                   \
    } while (0)
