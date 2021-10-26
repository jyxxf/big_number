#include "head.h"
static void multip(const char *previous, const char last, char **result, size_t row);
static void add_point(char **result, size_t fraction_len);

void multiply(const char *previous, const char *last, char **result)
{
    char Minus_Sign = 0;
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
        (*result)[0] = '-';
        multiply(previous + 1, last, result);
        return;
    }
    if (*last == '-')
    {
        (*result)[0] = '-';
        multiply(previous, last + 1, result);
        return;
    }
    if ((*result)[0] == '-')
    {
        Minus_Sign = 1;
        (*result)[0] = 0;
    }

    char **temp = (char **)malloc(sizeof(char *) * strlen(last));
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
        if (j == 0 && Minus_Sign)
            (*result)[0] = '-';
        plus(temp[j], plus_temp, result);
        plus_temp = (char *)realloc(plus_temp, strlen(*result) + 1);
        memcpy(plus_temp, *result, strlen(*result));
        plus_temp[strlen(*result)] = 0;
        free(temp[j]);
    }
    free(plus_temp);
    free(temp);

    char *pre_point = strchr(previous, '.');
    char *l_point = strchr(last, '.');
    if (pre_point && l_point)
    {
        size_t pre_fraction_len = strlen(previous) - (pre_point - previous) - 1;
        size_t l_fraction_len = strlen(last) - (l_point - last) - 1;
        add_point(result, pre_fraction_len + l_fraction_len);
    }
    else if (pre_point == NULL && l_point == NULL)
        ;
    else if (strlen(*result) != 1) //其中某一个有小数点
    {
        size_t position = pre_point == NULL ? strlen(last) - (l_point - last) - 1 : strlen(previous) - (pre_point - previous) - 1;
        add_point(result, position);
    }
    Del0(result);
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
