#include "head.h"
extern char compare(const char* previous, const char* last);
static void RemainderQuotient(const char *previous, const char *last, char **Remainder, char **Quotient);

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

static void RemainderQuotient(const char* previous,const char* last,char** Remainder,char** Quotient) //求两个整数的余数和商
{
    switch(compare(previous,last))
    {
        case 0:
        
    }
}