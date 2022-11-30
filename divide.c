#include "head.h"
extern char nonnegative_compare(const char *previous, const char *last);
static void lib_divide(const char *previous, const char *last, size_t fraction_len, char **result, char signal);
static void erase_last_point(const char *previous, const char *last, char **process_previous, char **process_last);
static void add_previous_point(const char *previous, char **has_point_previous);
static void lib_div(const char *previous, const char *last, size_t fraction_len, char **result, char signal);
static void get_minus_result(const char *tail, const char *last, char *quotient);
static void add_previous_0(const char *previous, char **previous_has_add_0, size_t fraction_len);

void divide(const char *previous, const char *last, size_t fraction_len, char **result) //求两个整数的余数和商
{
    if (*result == previous || *result == last) //结果和来源共用
    {
        char *temp_result = malloc(1);
        divide(previous, last, fraction_len, &temp_result);
        *result = realloc(*result, strlen(temp_result) + 1);
        memcpy(*result, temp_result, strlen(temp_result) + 1);
        free(temp_result);
        return;
    }
    if (*previous == '+')
    {
        divide(previous + 1, last, fraction_len, result);
        return;
    }
    if (*last == '+')
    {
        divide(previous, last + 1, fraction_len, result);
        return;
    }
    if (*last == '-' && *previous == '-')
    {
        divide(previous + 1, last + 1, fraction_len, result);
        return;
    }
    if (*previous == '-')
    {
        lib_divide(previous + 1, last, fraction_len, result, -1);
        return;
    }
    if (*last == '-')
    {
        lib_divide(previous, last + 1, fraction_len, result, -1);
        return;
    }
    lib_divide(previous, last, fraction_len, result, 1);
}

static void lib_divide(const char *previous, const char *last, size_t fraction_len, char **result, char signal)
{
    if (strchr(last, '.')) //去掉除数的小数点
    {
        char *process_previous = malloc(1);
        char *process_last = malloc(1);
        erase_last_point(previous, last, &process_previous, &process_last);
        lib_divide(process_previous, process_last, fraction_len, result, signal);
        free(process_previous);
        free(process_last);
        return;
    }
    if (strchr(previous, '.') == NULL) //被除数加上小数点
    {
        char *has_point_previous = malloc(1);
        add_previous_point(previous, &has_point_previous);
        lib_divide(has_point_previous, last, fraction_len, result, signal);
        free(has_point_previous);
        return;
    }
    if (fraction_len > strlen(previous) - (strchr(previous, '.') - previous) - 1) //被除数小数位数不够
    {
        char *previous_has_add_0 = malloc(1);
        add_previous_0(previous, &previous_has_add_0, fraction_len);
        lib_divide(previous_has_add_0, last, fraction_len, result, signal);
        free(previous_has_add_0);
        return;
    }
    lib_div(previous, last, fraction_len, result, signal);
}

static void lib_div(const char *previous, const char *last, size_t fraction_len, char **result, char signal)
{
    (*result) = realloc(*result, max(strlen(previous), strlen(last)) + fraction_len + 2);
    memset(*result, 0, max(strlen(previous), strlen(last)) + fraction_len + 2);
    size_t i = 0;
    if (signal == -1)
    {
        (*result)[0] = '-';
        i = 1;
    }
    char *tail = malloc(2);
    char *temp_tail = malloc(1);
    tail[0] = '0';
    tail[1] = 0;
    const char *point = previous;
    while (1)
    {
        if (*point == '.')
        {
            if (fraction_len == 0)
            {
                (*result)[i] = 0;
                free(tail);
                free(temp_tail);
                return;
            }
            else
            {
                (*result)[i] = '.';
                point++;
                i++;
            }
        }
        else
        {
            char multiply_10[3] = {'1', '0', 0};
            multiply(tail, multiply_10, &temp_tail);
            char temp_plus[2] = {*point, 0};
            plus(temp_tail, temp_plus, &tail);
            switch (nonnegative_compare(tail, last))
            {
            case -1:
            {
                if (strchr(*result, '.') == NULL)
                {
                    if (*(point + 1) == '.') //结果还没有小数点 但是后面有小数点 要加0
                    {
                        (*result)[i] = '0';
                    }
                    else if (i && (*result)[i - 1] >= '0' && (*result)[i - 1] <= '9') //结果没有小数点 但前面有数了 加0
                    {
                        (*result)[i] = '0';
                    }
                    else
                        i--;
                }
                else
                    (*result)[i] = '0';
                break;
            }
            case 0:
            case 1:
            {
                char quotient = 0;
                get_minus_result(tail, last, &quotient); //得到商
                (*result)[i] = quotient + '0';
                char *temp = malloc(2);
                temp[0] = (*result)[i];
                temp[1] = 0;
                multiply(temp, last, &temp_tail);
                minus(tail, temp_tail, &tail); //新的竖式差
                free(temp);
                break;
            }
            };
            i++;
            point++;
            if (fraction_len && strchr(*result, '.')) //已经添加了小数点 且需要小数后精度
            {
                size_t signal_and_int_and_point_len = strchr(*result, '.') - *result + 1;
                if (i - signal_and_int_and_point_len == fraction_len)
                {
                    (*result)[i] = 0;
                    free(tail);
                    free(temp_tail);
                    return;
                }
            }
        }
    }
}

static void erase_last_point(const char *previous, const char *last, char **process_previous, char **process_last)
{
    char multiply_10[3] = {'1', '0', 0};
    *process_previous = realloc(*process_previous, strlen(previous) + 1);
    *process_last = realloc(*process_last, strlen(last) + 1);
    memcpy(*process_previous, previous, strlen(previous) + 1);
    memcpy(*process_last, last, strlen(last) + 1);

    size_t fraction_len = strlen(last) - (strchr(last, '.') - last) - 1;
    while (fraction_len--)
    {
        multiply(*process_previous, multiply_10, process_previous);
        multiply(*process_last, multiply_10, process_last);
    }
}

static void add_previous_point(const char *previous, char **has_point_previous)
{
    size_t previous_len = strlen(previous);
    *has_point_previous = realloc(*has_point_previous, previous_len + 3);
    memcpy(*has_point_previous, previous, previous_len);
    (*has_point_previous)[previous_len] = '.';
    (*has_point_previous)[previous_len + 1] = '0';
    (*has_point_previous)[previous_len + 2] = 0;
}

static void get_minus_result(const char *tail, const char *last, char *quotient)
{
    char *result = malloc(1);
    minus(tail, last, &result);
    if (result[0] != '-')
    {
        (*quotient)++;
        get_minus_result(result, last, quotient);
    }
    free(result);
}

static void add_previous_0(const char *previous, char **previous_has_add_0, size_t fraction_len)
{
    size_t previous_fraction_len = strlen(previous) - (strchr(previous, '.') - previous) - 1;
    *previous_has_add_0 = realloc(*previous_has_add_0, strlen(previous) + fraction_len - previous_fraction_len + 1);
    memcpy(*previous_has_add_0, previous, strlen(previous));
    memset(*previous_has_add_0 + strlen(previous), '0', fraction_len - previous_fraction_len);
    (*previous_has_add_0)[strlen(previous) + fraction_len - previous_fraction_len] = 0;
}
