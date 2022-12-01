#include "head.h"
char nonnegative_compare(const char *previous, const char *last);
static void lib_minus(const char *previous, const char *last, char **result);
static void minus_digit(char a, char b, char *borrow, char **result, size_t index);

void minus(const char *previous, const char *last, char **result)
{
    if (*result == previous || *result == last) //结果和来源共用
    {
        char *temp_result = malloc(1);
        minus(previous, last, &temp_result);
        *result = realloc(*result, strlen(temp_result) + 1);
        memcpy(*result, temp_result, strlen(temp_result) + 1);
        free(temp_result);
        return;
    }
    if (*previous == '-' && *last == '-')
    {
        minus(last + 1, previous + 1, result);
        return;
    }
    else if (*last == '-')
    {
        plus(previous, last + 1, result);
        return;
    }
    else if (*previous == '-')
    {
        (*result)[0] = '-';
        lib_plus(previous + 1, last, result, -1);
        return;
    }
    if (*previous == '+')
    {
        minus(previous + 1, last, result);
        return;
    }
    if (*last == '+')
    {
        minus(previous, last + 1, result);
        return;
    }
    switch (nonnegative_compare(previous, last))
    {
    case 1:
        lib_minus(previous, last, result);
        break;
    case 0:
        (*result) = realloc(*result, 2);
        (*result)[0] = '0';
        (*result)[1] = 0;
        break;
    default:
        lib_minus(last, previous, result);
        (*result)[strlen(*result)] = '-';
        (*result)[strlen(*result)] = 0;
    }
    reverse(result);
    delete_0(result);
}

static void lib_minus(const char *previous, const char *last, char **result)
{
    const char *pre_point = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    const char *pre_point_or_tail = pre_point != NULL ? pre_point : strchr(previous, 0);
    const char *last_point_or_tail = last_point != NULL ? last_point : strchr(last, 0);
    const char *pre_tail = strchr(previous, 0);
    const char *last_tail = strchr(last, 0);
    size_t fraction_times;
    if (pre_point || last_point)
        fraction_times = max(pre_tail - pre_point_or_tail, last_tail - last_point_or_tail) - 1;
    else
        fraction_times = 0;
    size_t integer_times = max(pre_point_or_tail - previous, last_point_or_tail - last);
    *result = realloc(*result, fraction_times + integer_times + 3);
    memset(*result, 0, fraction_times + integer_times + 3);
    size_t i = 0, j = 0;
    char borrow = 0;
    size_t is_add_point = fraction_times;
    while (fraction_times--)
    {
        minus_digit(get_fraction_number(pre_point_or_tail, strchr(previous, 0), fraction_times + 1),
                    get_fraction_number(last_point_or_tail, strchr(last, 0), fraction_times + 1), &borrow, result, i);
        i++;
    }
    if (is_add_point)
    {
        (*result)[i] = '.';
        i++;
    }
    while (j++ < integer_times)
    {
        minus_digit(get_int_number(previous, pre_point_or_tail, j),
                    get_int_number(last, last_point_or_tail, j), &borrow, result, i);
        i++;
    }
}

/**
 * @brief  前面大则返回1 相同返回0 前面小返回-1
 *
 * @param previous
 * @param last
 * @return char
 */
char nonnegative_compare(const char *previous, const char *last)
{
    const char *pre_point = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    const char *pre_point_or_tail = pre_point != NULL ? pre_point : strchr(previous, 0);
    const char *last_point_or_tail = last_point != NULL ? last_point : strchr(last, 0);
    if (pre_point_or_tail - previous > last_point_or_tail - last)
        return 1;
    else if (pre_point_or_tail - previous < last_point_or_tail - last)
        return -1;
    else //整数部分位数一样
    {
        for (size_t i = 0; i < pre_point_or_tail - previous; i++)
        {
            if (previous[i] > last[i])
                return 1;
            else if (previous[i] < last[i])
                return -1;
        }
        if (pre_point == NULL && last_point == NULL)
            return 0;
        //小数部分比较
        const char *pre_tail = strchr(previous, 0);
        const char *last_tail = strchr(last, 0);
        size_t i = 0;
        while (++i)
        {
            if (((pre_point_or_tail + i >= pre_tail) ? '0' : *(pre_point_or_tail + i)) > ((last_point_or_tail + i >= last_tail) ? '0' : *(last_point_or_tail + i)))
                return 1;
            else if (((pre_point_or_tail + i >= pre_tail) ? '0' : *(pre_point_or_tail + i)) < ((last_point_or_tail + i >= last_tail) ? '0' : *(last_point_or_tail + i)))
                return -1;
            else if (pre_point_or_tail + i >= pre_tail && last_point_or_tail + i >= last_tail)
                break;
        }
        return 0;
    }
}

static void minus_digit(char a, char b, char *borrow, char **result, size_t index)
{
    char temp = a - b - *borrow;
    if (temp >= 0)
    {
        (*result)[index] = temp + '0';
        *borrow = 0;
    }
    else
    {
        (*result)[index] = temp + 10 + '0';
        *borrow = 1;
    }
}
