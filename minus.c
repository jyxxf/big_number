#include "head.h"
char compare(const char *previous, const char *last);
static void big_minus_small(const char *previous, const char *last, char **result);

void minus(const char *previous, const char *last, char **result)
{
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
        plus(previous + 1, last, result);
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
    switch (compare(previous, last))
    {
    case 1:
        big_minus_small(previous, last, result);
        break;
    case -1:
        big_minus_small(last, previous, result);
        size_t i = 0;
        while ((*result)[i])
            i++;
        (*result)[i] = '-';
        break;
    case 0:
        *result = (char *)realloc(*result, 2);
        (*result)[0] = '0';
        (*result)[1] = 0;
    }
    reverse(result);
    Del0(result);
}

static void big_minus_small(const char *previous, const char *last, char **result)
{
    size_t i = 0;
    u8 borrow = 0;
    const char *pre_point = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    if (pre_point && last_point) //按有无小数点也分为4种情况
    {
        size_t pre_fraction_len = strlen(previous) - (pre_point - previous) - 1;
        size_t l_fraction_len = strlen(last) - (last_point - last) - 1;
        size_t index = max(pre_fraction_len, l_fraction_len);
        (*result) = (char *)realloc(*result, max(pre_fraction_len, l_fraction_len) + 3 + pre_point - previous);
        memset(*result, 0, max(pre_fraction_len, l_fraction_len) + 3 + pre_point - previous);
        u8 temp;
        while (index)
        {
            if (pre_fraction_len < index)
            {
                (*result)[i] = 10 - (last_point[index] - '0') + '0' - borrow;
                borrow = 1;
            }
            else if (l_fraction_len < index)
            {
                (*result)[i] = pre_point[index];
            }
            else
            {
                if (pre_point[index] - borrow >= last_point[index])
                {
                    (*result)[i] = pre_point[index] - borrow - last_point[index] + '0';
                    borrow = 0;
                }
                else
                {
                    (*result)[i] = pre_point[index] - '0' + 10 - borrow - (last_point[index] - '0') + '0';
                    borrow = 1;
                }
            }
            index--;
            i++;
        }
        (*result)[i] = '.';
        i++;
        index = 1;
        while (index <= pre_point - previous)
        {
            if (index > last_point - last)
                if (*(pre_point - index) - borrow - '0' >= 0)
                {
                    (*result)[i] = *(pre_point - index) - borrow;
                    borrow = 0;
                }
                else
                {
                    (*result)[i] = '9';
                    borrow = 1;
                }
            else if (*(pre_point - index) - borrow >= *(last_point - index))
            {
                (*result)[i] = *(pre_point - index) - borrow - *(last_point - index) + '0';
                borrow = 0;
            }
            else
            {
                (*result)[i] = *(pre_point - index) - '0' + 10 - borrow - (*(last_point - index) - '0') + '0';
                borrow = 1;
            }
            i++;
            index++;
        }
    }
    else if (pre_point == NULL && last_point == NULL) //都没有小数点
    {
        size_t pre_len = strlen(previous);
        size_t l_len = strlen(last);
        size_t times = max(pre_len, l_len);
        *result = (char *)realloc(*result, times + 2);
        memset(*result, 0, times + 2);
        while (i < times)
        {
            if (i > l_len - 1)
                if (previous[pre_len - 1 - i] - borrow < '0')
                    (*result)[i] = '9';
                else
                {
                    (*result)[i] = previous[pre_len - 1 - i] - borrow;
                    borrow = 0;
                }
            else
            {
                if (previous[pre_len - 1 - i] - borrow < last[l_len - 1 - i])
                {
                    (*result)[i] = 10 + previous[pre_len - 1 - i] - borrow - last[l_len - 1 - i] + '0';
                    borrow = 1;
                }
                else
                {
                    (*result)[i] = previous[pre_len - 1 - i] - borrow - last[l_len - 1 - i] + '0';
                    borrow = 0;
                }
            }
            i++;
        }
    }
    else if (!pre_point)
    {
        size_t l_fraction_len = strlen(last) - (last_point - last) - 1;
        (*result) = (char *)realloc(*result, l_fraction_len + strlen(previous) + 3);
        memset(*result, 0, l_fraction_len + strlen(previous) + 3);
        size_t times = strlen(last) - (last_point - last) - 1; //小数点后次数
        while (times--)
        {
            (*result)[i] = 10 - (last_point[times + 1] - '0') - borrow + '0';
            borrow = 1;
            i++;
        }
        (*result)[i] = '.';
        i++;
        times = max(strlen(previous), last_point - last);
        size_t j = 1;
        while (times--)
        {
            if (j <= last_point - last)
                if (previous[times] - borrow >= *(last_point - j))
                {
                    (*result)[i] = previous[times] - borrow - *(last_point - j) + '0';
                    borrow = 0;
                }
                else
                {
                    (*result)[i] = 10 + previous[times] - borrow - *(last_point - j) + '0';
                    borrow = 1;
                }
            else
            {
                if (previous[times] - borrow < '0')
                {
                    (*result)[i] = '9';
                    borrow = 1;
                }
                else
                {
                    (*result)[i] = previous[times] - borrow;
                    borrow = 0;
                }
            }
            j++;
            i++;
        }
    }
    else if (!last_point)
    {
        size_t l_len = strlen(last);
        size_t pre_int_len = pre_point - previous;
        size_t pre_fraction_len = strlen(previous) - pre_int_len - 1;
        size_t length = pre_fraction_len + max(pre_int_len, l_len) + 3;
        *result = (char *)realloc(*result, length);
        memset(*result, 0, length);
        size_t times = pre_fraction_len;
        while (i < times) //小数减法
        {
            (*result)[i] = pre_point[pre_fraction_len - i];
            i++;
        }
        (*result)[i] = '.';
        i++;
        times = 0;
        while (times < pre_int_len) //整数减法
        {
            if (times < l_len)
                if (*(pre_point - times - 1) - borrow - last[l_len - times - 1] >= 0)
                {
                    (*result)[i] = *(pre_point - times - 1) - borrow - last[l_len - times - 1] + '0';
                    borrow = 0;
                }
                else
                {
                    (*result)[i] = 10 + *(pre_point - times - 1) - borrow - last[l_len - times - 1] + '0';
                    borrow = 1;
                }
            else if (*(pre_point - times - 1) - borrow >= '0')
            {
                (*result)[i] = *(pre_point - times - 1) - borrow;
                borrow = 0;
            }
            else
            {
                (*result)[i] = '9';
                borrow = 1;
            }
            i++;
            times++;
        }
    }
}

char compare(const char *previous, const char *last) //前面大则返回1 相同返回0
{
    const char *pre_point = strchr(previous, '.');
    const char *last_point = strchr(last, '.');
    if (last_point && pre_point)
    {
        if (strlen(previous) - strlen(pre_point) > strlen(last) - strlen(last_point))
            return 1;
        if (strlen(previous) - strlen(pre_point) < strlen(last) - strlen(last_point))
            return -1;
        if (strlen(previous) - strlen(pre_point) == strlen(last) - strlen(last_point))
        {
            if (strcmp(previous, last) < 0)
                return -1;
            if (strcmp(previous, last) > 0)
                return 1;
            return 0;
        }
    }
    if (last_point == NULL && pre_point == NULL)
    {
        if (strlen(previous) > strlen(last))
            return 1;
        if (strlen(previous) < strlen(last))
            return -1;
        if (strlen(previous) == strlen(last))
        {
            if (strcmp(previous, last) < 0)
                return -1;
            if (strcmp(previous, last) > 0)
                return 1;
            return 0;
        }
    }
    if (pre_point == NULL)
    {
        if (strlen(previous) > strlen(last) - strlen(last_point))
            return 1;
        if (strlen(previous) < strlen(last) - strlen(last_point))
            return -1;
        if (strlen(previous) == strlen(last) - strlen(last_point))
        {
            int temp = strncmp(previous, last, strlen(previous));
            if (temp > 0)
                return 1;
            if (temp < 0)
                return -1;
            if (temp == 0)
            {
                size_t i = 0;
                while (last_point[i++])
                    if (last_point[i] == '0')
                        continue;
                    else
                        return -1;
                return 0;
            }
        }
    }
    if (last_point == NULL)
    {
        if (strlen(last) > strlen(previous) - strlen(pre_point))
            return -1;
        if (strlen(last) < strlen(previous) - strlen(pre_point))
            return 1;
        if (strlen(last) == strlen(previous) - strlen(pre_point))
        {
            int temp = strncmp(previous, last, strlen(last));
            if (temp > 0)
                return 1;
            if (temp < 0)
                return -1;
            if (temp == 0)
            {
                size_t i = 0;
                while (pre_point[i++])
                    if (pre_point[i] == '0')
                        continue;
                    else
                        return 1;
                return 0;
            }
        }
    }
}
