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
void divide(const char *previous, const char *last, size_t fraction_len, char **result);

#define move()                                                                          \
    do                                                                                  \
    {                                                                                   \
        (*result)[i] = *((p_len > l_len ? pre_point : last_point) + max(p_len, l_len)); \
        i++;                                                                            \
        p_len > l_len ? p_len-- : l_len--;                                              \
    } while (0)

void lib_plus(const char *previous, const char *last, char **result, char signal);
void reverse(char **result);
void delete_0(char **result);
