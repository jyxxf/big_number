#include "head.h"
extern char compare(const char *previous, const char *last);
static void combine(const char *str, const char num, char **result);
static void expand(const char *previous, const char *last, char **p, char **l);
static char judge0(const char *str);

void devide(const char *previous, const char *last, size_t fraction_len, char **result) //求两个整数的余数和商
{
    if (*previous == '+')
    {
        devide(previous + 1, last, fraction_len, result);
        return;
    }
    if (*last == '+')
    {
        devide(previous, last + 1, fraction_len, result);
        return;
    }
    if (*last == '-' && *previous == '-')
    {
        devide(previous + 1, last + 1, fraction_len, result);
        return;
    }
    if (*previous == '-')
    {
        (*result)[0] = '-';
        devide(previous + 1, last, fraction_len, result);
        return;
    }
    if (*last == '-')
    {
        (*result)[0] = '-';
        devide(previous, last + 1, fraction_len, result);
        return;
    }

    if (strchr(last, '.'))
    {
        char *p = (char *)calloc(1, 1);
        char *l = (char *)calloc(1, 1);
        expand(previous, last, &p, &l);
        devide(p, l, fraction_len, result);
        return;
    }
    //previous被除数 last除数
    size_t pre_len = strlen(previous);
    (*result) = (char *)realloc(*result, pre_len + fraction_len + 3); //商
    if ((*result)[0] != '-')
        memset(*result, 0, pre_len + fraction_len + 3);
    else
        memset(*result + 1, 0, pre_len + fraction_len + 2);
    char *minus_result = (char *)calloc(1, 1); //减出来的结果
    char *temp_p = (char *)malloc(1);          //要除的被除数
    const char *tail = previous;
    size_t index = (*result)[0] == '-' ? 1 : 0; //商的下标
    while (*tail != '.' && *tail != 0)
    {
        combine(minus_result, *tail, &temp_p); //这边和下面不一样
        switch (compare(temp_p, last))
        {
        case 0: //相同商写1 减数结果为\0
            (*result)[index] = '1';
            minus_result = (char *)realloc(minus_result, 1);
            minus_result[0] = 0;
            break;
        case 1: //类似二分法
        {
            Bisection();
        }
        case -1:
            if ((*result)[0] == '-' ? index - 1 : index)
                (*result)[index] = '0';
            minus_result = (char *)realloc(minus_result, strlen(temp_p) + 1);
            memcpy(minus_result, temp_p, strlen(temp_p) + 1);
            break;
        }
        if ((*result)[index])
            index++;
        tail++;
    }

    if (!index || ((*result)[0] == '-' && (*result)[1] == 0)) //没有结果加0
    {
        (*result)[index] = '0';
        index++;
    }
    if (!fraction_len)
        return;

    (*result)[index] = '.';
    index++;
    if (*tail == '.')
        tail++;
    for (size_t i = 0; i < fraction_len; i++)
    {
        combine(minus_result, *tail == 0 ? '0' : *tail++, &temp_p); //没有就加'0'
        switch (compare(temp_p, last))
        {
        case 0:
            (*result)[index] = '1';
            minus_result = (char *)realloc(minus_result, 1);
            minus_result[0] = 0;
            break;
        case 1:
        {
            Bisection();
        }
        case -1:
            if (index)
                (*result)[index] = '0';
            minus_result = (char *)realloc(minus_result, strlen(temp_p) + 1);
            memcpy(minus_result, temp_p, strlen(temp_p) + 1);
            break;
        }
        if ((*result)[index])
            index++;
    }
    if (judge0(previous) && (*result)[0] == '-')
        memmove(*result, *result + 1, strlen(*result));
}

static void combine(const char *str, const char num, char **result)
{
    *result = (char *)realloc(*result, strlen(str) + 2);
    memset(*result, 0, strlen(str) + 2);
    if (*str == 0 || *str == '0')
    {
        (*result)[0] = num;
        return;
    }
    memcpy(*result, str, strlen(str));
    (*result)[strlen(str)] = num;
}

static void expand(const char *previous, const char *last, char **p, char **l)
{
    char *point = strchr(last, '.');
    char *mul = (char *)calloc(strlen(last) + 1, 1);
    mul[0] = '1';
    size_t i = 1;
    while (*(++point) != 0)
    {
        mul[i] = '0';
        i++;
    }
    multiply(previous, mul, p);
    multiply(last, mul, l);
}

static char judge0(const char *str)
{
    if (str[0] == '-' || str[0] == '+')
        judge0(str + 1);
    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] != '0' && str[i] != '.')
            return 0;
    }
    return 1;
}
