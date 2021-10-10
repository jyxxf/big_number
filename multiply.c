#include "head.h"
static void multip(const char *previous, const char last, char **result, size_t row);
static void add_point(char **result, size_t fraction_len);

void multiply(const char *previous, const char *last, char **result)
{
    if (*previous == '+')
    {
        multiply(previous + 1, last, result);
        return;
    }
    if (*last == '+')
    {
        multiply(previous, last + 1, result);
        return;
    }
    if (*previous == '-' && *last == '-')
    {
        multiply(previous + 1, last + 1, result);
        return;
    }
    if (*previous == '-')
    {
        multiply(previous + 1, last, result);
        add_MinusSign(result);
        return;
    }
    if (*last == '-')
    {
        multiply(previous, last + 1, result);
        add_MinusSign(result);
        return;
    }
    char **temp = (char **)malloc(sizeof(char *) * (strlen(last) - 1));
    size_t j = 0;
    size_t l_len = strlen(last);
    for (size_t i = 0; i < strlen(last); i++)
    {
        if (last[l_len - i - 1] != '.')
        {
            temp[j] = (char *)malloc(1);
            multip(previous, last[l_len - i - 1], &temp[j], j);
            j++;
        }
    }
    char *plus_temp = (char *)malloc(2);
    plus_temp[0] = '0';
    plus_temp[1] = 0;
    while (j--)
    {
        plus(temp[j], plus_temp, result);
        plus_temp = (char *)realloc(plus_temp, strlen(*result) + 1);
        memset(plus_temp, 0, strlen(*result) + 1);
        memcpy(plus_temp, *result, strlen(*result));
        free(temp[j]);
    }
    free(plus_temp);
    free(temp);
    size_t pre_fraction_len = strlen(previous) - (strchr(previous, '.') - previous) - 1;
    size_t l_fraction_len = strlen(last) - (strchr(last, '.') - last) - 1;
    add_point(result, pre_fraction_len + l_fraction_len);
}

static void multip(const char *previous, const char last, char **result, size_t row)
{
    size_t i = 0;
    u8 carry = 0;
    size_t pre_len = strlen(previous);
    *result = realloc(*result, strlen(previous) + row + 2);
    memset(*result, 0, strlen(previous) + row + 2);
    while (row--)
    {
        (*result)[i] = '0';
        i++;
    }
    for (size_t j = 0; j < strlen(previous); j++)
    {
        if (previous[strlen(previous) - j - 1] == '.')
            continue;
        if ((last - '0') * (previous[pre_len - j - 1] - '0') + carry >= 10)
        {
            (*result)[i] = ((last - '0') * (previous[pre_len - j - 1] - '0') + carry) % 10 + '0';
            carry = ((last - '0') * (previous[pre_len - j - 1] - '0') + carry) / 10;
        }
        else
        {
            (*result)[i] = (last - '0') * (previous[pre_len - j - 1] - '0') + carry + '0';
            carry = 0;
        }
        i++;
    }
    if (carry)
        (*result)[i] = carry + '0';
    reverse(result);
}

static void add_point(char **result, size_t fraction_len)
{
    *result = (char *)realloc(*result, strlen(*result) + 2);
    (*result)[strlen(*result) + 1] = 0; //添加字符串结束符
    size_t i = 0;
    while ((*result)[i])
        i++;
    while (fraction_len--)
    {
        (*result)[i] = (*result)[i - 1];
        i--;
    }
    (*result)[i] = '.';
}
