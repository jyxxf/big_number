#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void plus(const char *previous, const char *last, char **result);
void minus(const char *previous, const char *last, char **result);
void multiply(const char *previous, const char *last, char **result);
void divide(const char *previous, const char *last, size_t fraction_len, char **result);

void lib_plus(const char *previous, const char *last, char **result, char signal);
void reverse(char **result);
void delete_0(char **result);

#define get_fraction_number(head, tail, index_after_point) \
    ((head) + (index_after_point) >= (tail) ? '0' : *((head) + (index_after_point)))

#define get_int_number(head, point_or_tail, index_before_point) \
    ((point_or_tail) - (index_before_point) < (head) ? '0' : *((point_or_tail) - (index_before_point)))
