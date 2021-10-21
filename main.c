#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

static void compare(char **result, const char *aim);

int main(void)
{
    char *result = (char *)calloc(1, 1);
#if 0
    printf("\n plus\n");
    plus("2.035", "+6541.25", &result);
    compare(&result, "6543.285");
    plus("99.99", "9.9", &result);
    compare(&result, "109.89");
    plus("5646545654654646462262489849494.262254598498494949",
         "8948948489449448494494949849.6526586489489498494944494894944989", &result);
    compare(&result, "5655494603144095910756984799343.9149132474474447984944494894944989");
    plus("556", "9999955410", &result);
    compare(&result, "9999955966");
    plus("556", "9999955410.01", &result);
    compare(&result, "9999955966.01");
    plus("8484551.3221546", "3547", &result);
    compare(&result, "8488098.3221546");
    plus("-669933", "-332.015", &result);
    compare(&result, "-670265.015");
    plus("2.010101", "-2.00", &result);
    compare(&result, "0.010101");
    plus("-2.01", "+65412589.220201456987452", &result);
    compare(&result, "65412587.210201456987452");

    printf("\n minus\n");
    minus("36542.265", "36542.265", &result);
    compare(&result, "0");
    minus("+8956412.0", "+1.013546874456321459874563214566", &result);
    compare(&result, "8956410.986453125543678540125436785434");
    minus("1.1", "5596.254", &result);
    compare(&result, "-5595.154");
    minus("-56.21", "-541.000", &result);
    compare(&result, "484.79");
    minus("65564653121214", "2654645131454645484", &result);
    compare(&result, "-2654579566801524270");
    minus("999", "0", &result);
    compare(&result, "999");
    minus("523.01", "23", &result);
    compare(&result, "500.01");
    minus("2", "2.0000000000000000000001", &result);
    compare(&result, "-0.0000000000000000000001");
    minus("231.021", "-6541.23482147", &result);
    compare(&result, "6772.25582147");
    minus("-2.01", "+555.5555", &result);
    compare(&result, "-557.5655");
    minus("156", "160", &result);
    compare(&result, "-4");

    printf("\n multiply\n");
    multiply("3.13", "4.441", &result);
    compare(&result, "13.90033");
    multiply("123456789.98765432", "9876543.123456", &result);
    compare(&result, "1219326310196518.82533161172992");
    multiply("-3.0", "-4.441", &result);
    compare(&result, "13.3230");
    multiply("-313.13", "4.442487671", &result);
    compare(&result, "-1391.07616442023");
    multiply("1.0", "+1.0", &result);
    compare(&result, "1.00");
    multiply("-293324324548742", "91334534624242", &result);
    compare(&result, "-26790640676629473861183803564");
    multiply("3232187", "746.9876", &result);
    compare(&result, "2414403609.8812");
    multiply("+323.218723", "746", &result);
    compare(&result, "241121.167358");
    multiply("-3", "2", &result);
    compare(&result, "-6");
    multiply("3", "0.0", &result);
    compare(&result, "0.0");
    multiply("3.3", "1000", &result);
    compare(&result, "3300");
    multiply("-3", "1000", &result);
    compare(&result, "-3000");

    printf("\n devide\n");

    devide("53", "52", 30, &result);
    compare(&result, "1.019230769230769230769230769230");
    devide("52", "-53", 30, &result);
    compare(&result, "-0.981132075471698113207547169811");
    devide("43857629876489230856", "98765", 10, &result);
    compare(&result, "444060445263901.4919860274");
    devide("-1", "45342554365498765", 10, &result);
    compare(&result, "-0.0000000000");
    devide("1", "45342554365498765", 20, &result);
    compare(&result, "0.00000000000000002205");
    devide("44", "44", 10, &result);
    compare(&result, "1.0000000000");
    devide("44", "-44", 0, &result);
    compare(&result, "-1");
    devide("4", "7", 20, &result);
    compare(&result, "0.57142857142857142857");
    devide("0", "75435", 10, &result);
    compare(&result, "0.0000000000");


    devide("3.33", "4", 5, &result);
    compare(&result, "0.83250");
    devide("3.33", "4", 0, &result);
    compare(&result, "0");
    devide("333.000", "333", 7, &result);
    compare(&result, "1.0000000");
    devide("333.000", "333", 0, &result);
    compare(&result, "1");
    devide("2342345435345.234242352353", "2342435544", 28, &result);
    compare(&result, "999.9615320664867107021464322520");
    devide("97723.89732390472209", "9678434352", 25, &result);
    compare(&result, "0.0000100970770446679289611");
    devide("0", "75435.43535", 10, &result);
    compare(&result, "0.0000000000");
#endif
    multiply("0.001", "1000", &result);
    compare(&result, "1");

    free(result);
    return 0;
}

static void compare(char **result, const char *aim) //比较完成后全部置0
{
    size_t i = 0;
    while (aim[i])
        if ((*result)[i] == aim[i])
            i++;
        else
        {
            printf("error!");
            printf(" %s\n", *result);
            return;
        }
    printf("OK\n");
    memset(*result, 0, i);
}

void reverse(char **result) //第一个是负号不翻转，其余逆序输出
{
    if ((*result)[0] == '-')
    {
        char *temp = *result + 1;
        reverse(&temp);
        return;
    }
    size_t last = 0;
    while ((*result)[last])
        last++;
    for (size_t i = 0; i < last / 2; i++)
    {
        u8 temp = (*result)[i];
        (*result)[i] = (*result)[last - i - 1];
        (*result)[last - i - 1] = temp;
    }
}

void add_MinusSign(char **result) //向后挪一位，增加负号
{
    (*result) = (char *)realloc(*result, strlen(*result) + 2);
    for (size_t i = strlen(*result); i > 0; i--)
        (*result)[i] = (*result)[i - 1];
    (*result)[0] = '-';
}

//0.001*100=
void erase0(char **result, char calculate)
{
    if ((*result)[0] == '+' || (*result)[0] == '-')
    {
        char *temp = *result + 1;
        erase0(&temp, calculate);
        return;
    }
    if (calculate == '-') //反着的
    {
        size_t i = strlen(*result);
        if (i == 1)
            return;
        if ((*result)[i - 2] == '.')
            return;
        while ((*result)[i - 1] == '0')
        {
            (*result)[i - 1] = (*result)[i];
            (*result)[i] = 0;
            i--;
            
        }
    }
    else
    {
    }
}
