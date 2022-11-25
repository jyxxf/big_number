#include "head.h"
static void single_multiply_previous(const char *previous, const char last, char **result, size_t row);
static void add_point(char **result, size_t fraction_len);
static void lib_multiply(const char *previous, const char *last, char **result, char signal);
static void add_minus_signal(char **result, char signal);

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
        lib_multiply(previous + 1, last, result, -1);
        return;
    }
    if (*last == '-')
    {
        lib_multiply(previous, last + 1, result, -1);
        return;
    }
    lib_multiply(previous, last, result, 1);
}

static void lib_multiply(const char *previous, const char *last, char **result, char signal)
{
    size_t l_len = strlen(last); //减不减1再说
    size_t j = 0;
    char **temp = (char **)malloc(sizeof(char *) * l_len);
    for (size_t i = 0; i < l_len; i++)
    {
        if (last[l_len - i - 1] != '.')
        {
            single_multiply_previous(previous, last[l_len - i - 1], &temp[j], j);
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
    else //其中某一个有小数点
    {
        size_t position = pre_point == NULL ? strlen(last) - (l_point - last) - 1 : strlen(previous) - (pre_point - previous) - 1;
        add_point(result, position);
    }
    Del0(result);
    if (signal == -1 && !((*result)[0] == '0' && (*result)[1] == 0)) //-0不用加负号
        add_minus_signal(result, signal);
}

/**
 * @brief
 *
 * @param previous
 * @param last
 * @param result
 * @param row 得出的结果在第几行，第0行无需处理 第一行要*10 第二行*100
 */
static void single_multiply_previous(const char *previous, const char last, char **result, size_t row)
{
    size_t i = 0;
    u8 carry = 0;
    size_t pre_len = strlen(previous);
    *result = malloc(strlen(previous) + row + 2);
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
    Del0(result);
}

static void add_point(char **result, size_t fraction_len)
{
    if (fraction_len >= strlen(*result))
        return;
    *result = (char *)realloc(*result, strlen(*result) + 2);
    (*result)[strlen(*result) + 1] = 0; //添加字符串结束符
    size_t i = strlen(*result);
    while (fraction_len--)
    {
        (*result)[i] = (*result)[i - 1];
        i--;
    }
    (*result)[i] = '.';
}

static void add_minus_signal(char **result, char signal)
{
    *result = realloc(*result, strlen(*result) + 2);
    (*result)[strlen(*result) + 1] = 0;
    memmove(*result + 1, *result, strlen(*result));
    (*result)[0] = '-';
}
