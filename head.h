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
