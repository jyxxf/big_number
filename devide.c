#include "head.h"
extern char compare(const char *previous, const char *last);

void devide(const char *previous, const char *last, size_t fraction_len, char **result)
{
    /*
    char *last_point = strchr(last, '.');
    if (last_point)
    {
        size_t p_fraction_len = strlen(last) - (last_point - last) - 1;
        char* ten_times = (char*)calloc(p_fraction_len + 2, sizeof(char));
        ten_times[0] = '1';
        memset(ten_times + 1, 0, p_fraction_len);
        char* temp_p = (char*)malloc(1);
        char* temp_l = (char*)malloc(1);
        multiply(previous, ten_times, &temp_p);
        multiply(last, ten_times, &temp_l);
        devide(temp_p, temp_l, fraction_len, result);
        return;
    }
    char* temp = malloc(2);
    memcpy(temp, previous, 1);
    temp[1] = 0;
    switch(compare(temp, last))
    {
    case 1:
    case 0:

        break;
    case -1:
    }
*/
}

void RemainderQuotient(const char *previous, const char *last, char **Remainder, char **Quotient) //求两个整数的余数和商
{
    (*Quotient) = (char *)realloc(*Quotient, strlen(previous) + 1);
    memset(*Quotient, 0, strlen(previous) + 1);
    (*Remainder) = (char *)realloc(*Remainder, strlen(last) + 1);
    memset(*Remainder, 0, strlen(last) + 1);

    char *temp_result = (char *)malloc(1); //减出来的结果
    char *temp_p = (char *)malloc(1); //被除数
    char *head = previous, *tail = previous;
    size_t Q_index = 0;
    while (tail != previous + strlen(previous))
    {
        temp_p = (char *)realloc(temp_p, tail - head + 2 + strlen(temp_result));
        memset(temp_p, 0,  + 1);
        memcpy(temp_p, head, tail - head);

        switch (compare(temp_p, last))
        {
        case 0:
            (*Quotient)[Q_index] = '1';
            tail++;
            head = tail;
            break;
        case 1:
        {
            char *temp = (char *)malloc(2);
            char small = '0';
            char big = '9';
            char now = '5';
            temp[0] = now;
            temp[1] = 0;
            u8 big_flag = 1, small_flag = 1;
            char *dividend = (char *)malloc(1);
            while (!(*Quotient)[Q_index])
            {
                temp[0] = now;
                multiply(temp, "last", &dividend);
                switch (compare(dividend, temp_p))
                {
                case 0:
                    (*Quotient)[Q_index] = now;
                    break;
                case 1: //要小一点
                    if (big - small == 1)
                        (*Quotient)[Q_index] = now;
                    big = now;
                    now = (now + small) / 2;
                    break;
                case -1:
                    if (big - small == 1)
                        (*Quotient)[Q_index] = now;
                    small = now;
                    now = (now + big) / 2;
                    break;
                }
            }
            minus(temp_p, dividend, &temp_result);
            temp_p = (char *)realloc(temp_p, strlen(temp_result) + 1);
            memcpy(temp_p, temp_result, strlen(temp_result) + 1);
            break;
        }
        case -1:
            if (Q_index)
            {
                (*Quotient)[Q_index] = '0';
            }
            else
                tail++;
            break;
        }
        Q_index++;
    }
}
