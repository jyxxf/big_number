#include "head.h"
extern char compare(const char *previous, const char *last);
static void combine(const char *str, const char num, char **result);

//void devide(const char *previous, const char *last, size_t fraction_len, char **result)
//{
//    char *last_point = strchr(last, '.');
//    if (last_point)
//    {
//        size_t p_fraction_len = strlen(last) - (last_point - last) - 1;
//        char* ten_times = (char*)calloc(p_fraction_len + 2, sizeof(char));
//        ten_times[0] = '1';
//        memset(ten_times + 1, 0, p_fraction_len);
//        char* temp_p = (char*)malloc(1);
//        char* temp_l = (char*)malloc(1);
//        multiply(previous, ten_times, &temp_p);
//        multiply(last, ten_times, &temp_l);
//        devide(temp_p, temp_l, fraction_len, result);
//        return;
//    }
//    char* temp = malloc(2);
//    memcpy(temp, previous, 1);
//    temp[1] = 0;
//    switch(compare(temp, last))
//    {
//    case 1:
//    case 0:
//
//        break;
//    case -1:
//    }
//}

void devide(const char *previous, const char *last, size_t fraction_len, char **result) //求两个整数的余数和商
{
    //previous被除数 last除数
    size_t pre_len = strlen(previous);
    (*result) = (char *)realloc(*result, strlen(previous) + 1); //商
    memset(*result, 0, strlen(previous) + 1);
    char *minus_result = (char *)calloc(1, 1); //减出来的结果
    char *temp_p = (char *)malloc(1);          //要除的被除数
    const char* tail = previous;
    size_t index = 0; //商的下标
    while (*tail != '.' && *tail != 0)
    {
        combine(minus_result, *tail, &temp_p);
        switch (compare(temp_p, last))
        {
        case 0:
            (*result)[index] = '1';
            minus_result = (char *)realloc(minus_result, 1);
            minus_result[0] = 0;
            break;
        case 1:
        {
            char small = '0';
            char big = '9';
            char now[2];
            now[0] = '5';
            now[1] = 0;
            char *mul_result = (char *)malloc(1);
            while (!(*result)[index])
            {
                multiply(now, last, &mul_result);
                switch (compare(mul_result, temp_p))
                {
                case 0:
                    (*result)[index] = now[0];
                    break;
                case 1:
                    if (big - small == 1 || big - small == 2)
                        (*result)[index] = now[0];
                    big = now[0];
                    now[0] = (now[0] + small) / 2;
                    break;
                case -1:
                    if (big - small == 1 || big - small == 2)
                        (*result)[index] = now[0];
                    small = now[0];
                    now[0] = (now[0] + big) / 2;
                    break;
                }
            }
            minus(temp_p, mul_result, &minus_result);
            temp_p = (char *)realloc(temp_p, strlen(minus_result) + 1);
            memcpy(temp_p, minus_result, strlen(minus_result) + 1);
            break;
        }
        case -1:
            if (index)
            {
                (*result)[index] = '0';
            }
            else
            {
                minus_result = (char *)realloc(minus_result, strlen(temp_p) + 1);
                memcpy(minus_result, temp_p, strlen(temp_p));
                minus_result[strlen(temp_p)] = 0;
            }
            break;
        }
        if ((*result)[index])
            index++;
        tail++;
    }
    if (!fraction_len)
        return;
    (*result)[index] = '.';
    index++;

    tail++;
    for (size_t i = 0; i < fraction_len; i++)
    {
        if (tail - previous <= pre_len)
        {
        }
        else
        {
            combine(minus_result, '0', &temp_p);
            switch (compare(temp_p, last))
            {
            case 0:
                (*result)[index] = '1';
                minus_result = (char *)realloc(minus_result, 1);
                minus_result[0] = 0;
                break;
            case 1:
            {
                char small = '0';
                char big = '9';
                char now[2];
                now[0] = '5';
                now[1] = 0;
                char *mul_result = (char *)malloc(1);
                while (!(*result)[index])///////////////////////////搞成0
                {
                    multiply(now, last, &mul_result);
                    switch (compare(mul_result, temp_p))
                    {
                    case 0:
                        (*result)[index] = now[0];
                        break;
                    case 1:
                        if (big - small == 1 || big - small == 2)
                            (*result)[index] = now[0];
                        big = now[0];
                        now[0] = (now[0] + small) / 2;
                        break;
                    case -1:
                        if (big - small == 1 || big - small == 2)
                            (*result)[index] = now[0];
                        small = now[0];
                        now[0] = (now[0] + big) / 2;
                        break;
                    }
                }
                minus(temp_p, mul_result, &minus_result);
                temp_p = (char *)realloc(temp_p, strlen(minus_result) + 1);
                memcpy(temp_p, minus_result, strlen(minus_result) + 1);
                break;
            }
            case -1:
                if (index)
                {
                    (*result)[index] = '0';
                }
                else
                {
                    minus_result = (char *)realloc(minus_result, strlen(temp_p) + 1);
                    memcpy(minus_result, temp_p, strlen(temp_p));
                    minus_result[strlen(temp_p)] = 0;
                }
                break;
            }
            if ((*result)[index])
                index++;
            tail++;
        }
    }
}

static void combine(const char *str, const char num, char **result)
{
    if (*str)
    {
        *result = (char *)realloc(*result, strlen(*result) + 2);
        (*result)[strlen(*result) + 1] = 0;
        (*result)[strlen(*result)] = num;
        return;
    }
    *result = (char *)realloc(*result, 2);
    (*result)[0] = num;
    (*result)[1] = 0;
}
