#include "head.h"
static void plus_digit(char a, char b, char *carry, char **result, size_t index);

void plus(const char *previous, const char *last, char **result)
{
    if (*result == previous || *result == last) //结果和来源共用
    {
        char *temp_result = malloc(1);
        plus(previous, last, &temp_result);
        *result = realloc(*result, strlen(temp_result) + 1);
        memcpy(*result, temp_result, strlen(temp_result) + 1);
        free(temp_result);
        return;
    }
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
    if (*previous == '-' && *last == '-') //两个都是负号，将结果第一个也置为负号
    {
        (*result)[0] = '-';
        lib_plus(previous + 1, last + 1, result, -1);
        return;
    }
    if (*previous == '-')
    {
        minus(last, previous + 1, result);
        return;
    }
    if (*last == '-')
    {
        minus(previous, last + 1, result);
        return;
    }
    lib_plus(previous, last, result, 1);
}

void lib_plus(const char *previous, const char *last, char **result, char signal)
{
    char carry = 0;

    size_t length = max(strlen(previous), strlen(last));
    length = length * 2 + 1;
    *result = (char *)realloc(*result, length);
    memset(*result, 0, length);

    const char *pre_piont = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    const char *pre_point_or_tail = pre_piont != NULL ? pre_piont : strchr(previous, 0);
    const char *last_point_or_tail = last_point != NULL ? last_point : strchr(last, 0);
    size_t fraction_plus_times = 0;
    if (pre_piont == NULL)
    {
        if (last_point == NULL)
            fraction_plus_times = 0;
        else
            fraction_plus_times = strchr(last, 0) - last_point - 1;
    }
    else
    {
        if (last_point == NULL)
            fraction_plus_times = strchr(previous, 0) - pre_piont - 1;
        else
            fraction_plus_times = max(strchr(previous, 0) - pre_piont, strchr(last, 0) - last_point) - 1;
    }

    size_t integer_plus_times = max(pre_point_or_tail - previous, last_point_or_tail - last);
    size_t i = 0, j = 0;
    int is_add_point = fraction_plus_times;

    while (fraction_plus_times--)
    {
        plus_digit(get_fraction_number(pre_point_or_tail, strchr(previous, 0), fraction_plus_times + 1),
                   get_fraction_number(last_point_or_tail, strchr(last, 0), fraction_plus_times + 1), &carry, result, i);
        i++;
    }
    if (is_add_point)
    {
        (*result)[i] = '.';
        is_add_point = 0;
        i++;
    }
    while (j++ < integer_plus_times)
    {
        plus_digit(get_int_number(previous, pre_point_or_tail, j),
                   get_int_number(last, last_point_or_tail, j), &carry, result, i);
        i++;
    }
    if (carry)
        (*result)[i] = '1';
    if (signal == -1)
    {
        char *result_tail = strchr(*result, 0);
        *result_tail = '-';
        *(result_tail + 1) = 0;
    }
    reverse(result);
    delete_0(result);
}

static void plus_digit(char a, char b, char *carry, char **result, size_t index)
{
    int temp = a - '0' + b - '0' + *carry;
    if (temp >= 10)
    {
        *carry = 1;
        temp -= 10;
    }
    else
    {
        *carry = 0;
    }
    (*result)[index] = '0' + temp;
}
