#include "head.h"
size_t plus_fraction(const char *pre_point, size_t p_len, const char *last_point, size_t l_len, u8 *carry, char **result);
void plus_int(const char *previous, const char *last, const char *pre_point, const char *last_point,
              u8 *carry, char **result, size_t position);

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
    u8 carry = 0;

    size_t length = max(strlen(previous), strlen(last));
    size_t pre_int_len;
    size_t last_int_len;
    size_t pre_fraction_len;
    size_t last_fraction_len;
    length = length * 2 + 1;
    *result = (char *)realloc(*result, length);
    memset(*result, 0, length);

    const char *pre_point = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    //按小数点分为四种情况
    if (pre_point && last_point) //都有小数点
    {
        pre_int_len = pre_point - previous;
        last_int_len = last_point - last;
        pre_fraction_len = strlen(previous) - pre_int_len - 1;
        last_fraction_len = strlen(last) - last_int_len - 1;

        if (pre_point != NULL && last_point != NULL)
        {
            plus_int(previous, last, pre_point, last_point, &carry, result,
                     plus_fraction(pre_point, pre_fraction_len, last_point, last_fraction_len, &carry, result));
        }
    }
    else if (pre_point == NULL && last_point == NULL)
    {
        plus_int(previous, last, previous + strlen(previous), last + strlen(last), &carry, result, 0);
    }
    else if (!pre_point)
    {
        last_int_len = last_point - last;
        last_fraction_len = strlen(last) - last_int_len - 1;
        plus_int(previous, last, previous + strlen(previous), last_point, &carry, result,
                 plus_fraction(NULL, 0, last_point, last_fraction_len, &carry, result));
    }
    else if (!last_point)
    {
        pre_int_len = pre_point - previous;
        pre_fraction_len = strlen(previous) - pre_int_len - 1;
        plus_int(previous, last, pre_point, last + strlen(last), &carry, result,
                 plus_fraction(pre_point, pre_fraction_len, NULL, 0, &carry, result));
    }
    if (signal == -1)
    {
        char *result_tail = strchr(*result, 0);
        *result_tail = '-';
        *(result_tail + 1) = 0;
    }
    reverse(result);
    delete_0(result);
}

/**
 * @brief
 *
 * @param previous
 * @param last
 * @param pre_point
 * @param last_point
 * @param carry
 * @param result
 * @param position
 */
void plus_int(const char *previous, const char *last, const char *pre_point, const char *last_point,
              u8 *carry, char **result, size_t position)
{
    size_t i = position;
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
    {
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
    }
    if (previous == pre_point)
    {
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
    }
    if (*carry)
        (*result)[i] = '1';
}

/**
 * @brief 小数部分相加
 *
 * @param pre_point 小数点指针
 * @param p_len 长度
 * @param last_point
 * @param l_len
 * @param carry 进位
 * @param result
 * @return size_t 小数和小数点加起来长度
 */
size_t plus_fraction(const char *pre_point, size_t p_len, const char *last_point, size_t l_len, u8 *carry, char **result)
{
    size_t i = 0;
    while (p_len != l_len)
        move();
    while (p_len)
    { // temp
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
