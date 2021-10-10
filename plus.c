#include "head.h"

void plus(const char *previous, const char *last, char **result)
{
    if (*previous == '+')
    {
        plus(previous + 1, last, result);
        return;
    }
    if (*last == '+')
    {
        plus(previous, last + 1, result);
        return;
    }
    if (*previous == '-' && *last == '-')
    {
        (*result)[0] = '-';
        plus(previous + 1, last + 1, result);
        return;
    }
    if(*previous=='-')
    {
        minus(last, previous + 1, result);
        return;
    }
    if (*last == '-')
    {
        minus(previous, last + 1, result);
        return;
    }
    u8 carry = 0;

    size_t length = max(strlen(previous), strlen(last));
    size_t p_int_len;
    size_t l_int_len;
    size_t p_fraction_len;
    size_t l_fraction_len;
    length = length * 2 + 1;
    *result = (char *)realloc(*result, length);
    (*result)[0] == '-' ? memset(*result + 1, 0, length - 1) : memset(*result, 0, length);

    const char *pre_point = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    if (pre_point && last_point)
    {
        p_int_len = pre_point - previous;
        l_int_len = last_point - last;
        p_fraction_len = strlen(previous) - p_int_len - 1;
        l_fraction_len = strlen(last) - l_int_len - 1;

        if (pre_point != NULL && last_point != NULL)
        {
            size_t position = plus_fraction(pre_point, p_fraction_len, last_point, l_fraction_len, &carry, result);
            plus_int(previous, last, pre_point, last_point, &carry, result, &position);
            reverse(result);
        }
    }
    else if (pre_point == NULL && last_point == NULL)
    {
        size_t position = 0;
        if ((*result)[0] == '-')
            position = 1;
        plus_int(previous, last, previous + strlen(previous), last + strlen(last), &carry, result, &position);
        reverse(result);
    }
    else if (!pre_point)
    {
        l_int_len = last_point - last;
        l_fraction_len = strlen(last) - l_int_len - 1;
        size_t position = plus_fraction(NULL, 0, last_point, l_fraction_len, &carry, result);
        plus_int(previous, last, previous + strlen(previous), last_point, &carry, result, &position);
        reverse(result);
    }
    else if (!last_point)
    {
        p_int_len = pre_point - previous;
        p_fraction_len = strlen(previous) - p_int_len - 1;
        size_t position = plus_fraction(pre_point, p_fraction_len, NULL, 0, &carry, result);
        plus_int(previous, last, pre_point, last + strlen(last), &carry, result, &position);
        reverse(result);
    }
}

void plus_int(const char *previous, const char *last, const char *pre_point, const char *last_point,
              u8 *carry, char **result, size_t *position)
{
    size_t i = *position;
    while (last != last_point && previous != pre_point)
    {
        if ((*(last_point - 1) + *(pre_point - 1) - '0' - '0' + *carry) >= 10)
        {
            (*result)[i] = *(last_point - 1) + *(pre_point - 1) - '0' - '0' + *carry - 10 + '0';
            *carry = 1;
        }
        else
        {
            (*result)[i] = *(last_point - 1) + *(pre_point - 1) - '0' - '0' + *carry + '0';
            *carry = 0;
        }
        last_point--;
        pre_point--;
        i++;
    }
    if (last == last_point)
        while (pre_point != previous)
        {
            if (*(pre_point - 1) + *carry - '0' >= 10)
            {
                (*result)[i] = *(pre_point - 1) + *carry - '0' - 10 + '0';
                *carry = 1;
            }
            else
            {
                (*result)[i] = *(pre_point - 1) + *carry - '0' + '0';
                *carry = 0;
            }
            i++;
            pre_point--;
        }
    if (previous == pre_point)
        while (last != last_point)
        {
            if (*(last_point - 1) + *carry - '0' >= 10)
            {
                (*result)[i] = *(last_point - 1) + *carry - '0' - 10 + '0';
                *carry = 1;
            }
            else
            {
                (*result)[i] = *(last_point - 1) + *carry - '0' + '0';
                *carry = 0;
            }
            i++;
            last_point--;
        }
    if (*carry)
        (*result)[i] = '1';
}

size_t plus_fraction(const char *pre_point, size_t p_len, const char *last_point, size_t l_len, u8 *carry, char **result)
{
    size_t i = 0;
    if (*(result)[0] == '-')
        i++;
    while (p_len != l_len)
        move();
    while (p_len)
    { //temp
        if ((*(pre_point + p_len) + *(last_point + p_len) - '0' - '0' + *carry) >= 10)
        {
            (*result)[i] = *(pre_point + p_len) + *(last_point + p_len) - '0' - '0' + *carry - 10 + '0';
            *carry = 1;
        }
        else
        {
            (*result)[i] = *(pre_point + p_len) + *(last_point + p_len) - '0' - '0' + *carry + '0';
            *carry = 0;
        }
        p_len--;
        i++;
    }
    (*result)[i] = '.';
    i++;
    return i;
}
