#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
static void compare(char **result, const char *aim);
static void test_plus(void);
static void test_minus(void);
static void test_multiply(void);
static void test_divide(void);

int main(void)
{
    //test_plus();
    //test_minus();
    //test_multiply();
    test_divide();
    return 0;
}

static void test_plus(void)
{
    char *result = (char *)calloc(1, 1);
    printf("\n plus\n");
    plus("2.035", "+6541.25", &result);
    compare(&result, "6543.285");
    plus("5646545654654646462262489849494.262254598498494949",
         "8948948489449448494494949849.6526586489489498494944494894944989", &result);
    compare(&result, "5655494603144095910756984799343.9149132474474447984944494894944989");
    plus("556", "9999955410", &result);
    compare(&result, "9999955966");
    plus("556", "9999955410.01", &result);
    compare(&result, "9999955966.01");
    plus("-669933", "-332.015", &result);
    compare(&result, "-670265.015");
    plus("2.010101", "-2.00", &result);
    compare(&result, "0.010101");
    plus("-2.01", "+65412589.220201456987452", &result);
    compare(&result, "65412587.210201456987452");
    plus("+0", "-0", &result);
    compare(&result, "0");
    plus("+3.33", "0.07", &result);
    compare(&result, "3.4");
    plus("+0.000", "-0.00", &result);
    compare(&result, "0");
    plus("2.23", "-2.23", &result);
    compare(&result, "0");
    free(result);
}

static void test_minus(void)
{
    char *result = (char *)calloc(1, 1);
    printf("\n minus\n");
    minus("36542.265", "36542.265", &result);
    compare(&result, "0");
    minus("0.00", "-0.000", &result);
    compare(&result, "0");
    minus("+8956412.0", "+1.013546874456321459874563214566", &result);
    compare(&result, "8956410.986453125543678540125436785434");
    minus("1.1", "5596.254", &result);
    compare(&result, "-5595.154");
    minus("-56.21", "-541.000", &result);
    compare(&result, "484.79");
    minus("65564653121214", "2654645131454645484", &result);
    compare(&result, "-2654579566801524270");
    minus("999", "0.0", &result);
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
    free(result);
}

static void test_multiply(void)
{
    char *result = (char *)calloc(1, 1);
    printf("\n multiply\n");
    //测试0*0
    multiply("0.000", "0", &result);
    compare(&result, "0");
    multiply("0", "-0", &result);
    compare(&result, "0");
    multiply("-0", "+0.000", &result);
    compare(&result, "0");
    multiply("-0.00", "-0.000", &result);
    compare(&result, "0");
    //测试其中一方为0
    multiply("0.0000", "-0.334", &result);
    compare(&result, "0");
    multiply("-0", "22.334", &result);
    compare(&result, "0");
    multiply("-345.77", "-0", &result);
    compare(&result, "0");
    multiply("-34.7534", "+0.000", &result);
    compare(&result, "0");
    multiply("0", "+800", &result);
    compare(&result, "0");
    multiply("456", "-0", &result);
    compare(&result, "0");

    multiply("1.00000", "1.001", &result);
    compare(&result, "1.001");
    multiply("3.13", "4.441", &result);
    compare(&result, "13.90033");
    multiply("123456789.98765432", "9876543.123456", &result);
    compare(&result, "1219326310196518.82533161172992");
    multiply("-3.0", "-4.441", &result);
    compare(&result, "13.323");
    multiply("-313.13", "4.442487671", &result);
    compare(&result, "-1391.07616442023");
    multiply("1.0", "+1.0", &result);
    compare(&result, "1");
    multiply("-293324324548742", "91334534624242.00", &result);
    compare(&result, "-26790640676629473861183803564");
    multiply("3232187", "746.9876", &result);
    compare(&result, "2414403609.8812");
    multiply("+323.218723", "746", &result);
    compare(&result, "241121.167358");
    multiply("-3", "1000", &result);
    compare(&result, "-3000");
    multiply("0.001", "1000", &result);
    compare(&result, "1");
    multiply("-1.20", "5.0", &result);
    compare(&result, "-6");
    free(result);
}

static void test_divide(void)
{
    char *result = (char *)calloc(1, 1);
    printf("\n devide\n");
    devide("53", "52", 30, &result);
    compare(&result, "1.019230769230769230769230769230");
    devide("52", "-53", 30, &result);
    compare(&result, "-0.981132075471698113207547169811");
    devide("43857629876489230856", "98765", 10, &result);
    compare(&result, "444060445263901.4919860274");
    devide("-1", "45342554365498765", 10, &result);
    compare(&result, "-0.0000000000"); //不需要消除负号
    devide("1", "45342554365498765", 20, &result);
    compare(&result, "0.00000000000000002205");
    devide("44", "44", 10, &result);
    compare(&result, "1.0000000000");
    devide("44", "-44", 0, &result);
    compare(&result, "-1");
    devide("+4", "7", 20, &result);
    compare(&result, "0.57142857142857142857");
    devide("-0", "-75435", 10, &result);
    compare(&result, "0.0000000000");
    devide("3.33", "4", 5, &result);
    compare(&result, "0.83250");
    devide("-3.33", "+4", 0, &result);
    compare(&result, "-0");
    devide("+333.000", "-333", 7, &result);
    compare(&result, "-1.0000000");
    devide("333.000", "333", 0, &result);
    compare(&result, "1");
    devide("2342345435345.234242352353", "2342435544", 28, &result);
    compare(&result, "999.9615320664867107021464322520");
    devide("+97723.89732390472209", "-9678434352", 25, &result);
    compare(&result, "-0.0000100970770446679289611");
    devide("-0", "75435.43535", 10, &result);
    compare(&result, "0.0000000000");
    devide("-234", "0.00001", 10, &result);
    compare(&result, "-23400000.0000000000");
    devide("89734", "3.321", 0, &result);
    compare(&result, "27020");
    devide("453532465345624352", "53452345233.312312548675621", 24, &result);
    compare(&result, "8484800.121791027392187393132871");
    devide("45.543", "-53433.3242876076", 14, &result);
    compare(&result, "-0.00085233326968");
    free(result);
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
    printf(" OK\n");
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

void Del0(char **result)
{
    if ((*result)[0] == '+' || (*result)[0] == '-')
    {
        char *temp = *result + 1;
        Del0(&temp);
        if ((*result)[0] == '+')
            memmove(*result, *result + 1, strlen(*result));
        else if ((*result)[1] == '0' && (*result)[2] == 0)
            memmove(*result, *result + 1, 2);
        return;
    }
    //分为前导0 和 小数点后的零
    size_t i = 0;
    size_t length = strlen(*result);
    while (1)
    {
        if ((*result)[i] == '0' && (*result)[i + 1] != 0 && (*result)[i + 1] != '.')
            i++;
        else
            break;
    }
    if (i)
    {
        memmove(*result, *result + i, length - i);
        for (size_t j = 0; j < i; j++)
            (*result)[length - i + j] = 0;
    }
    //清除小数点后的0
    char *point = strchr(*result, '.');
    if (!point)
        return;
    else
    {
        length = strlen(*result);
        while ((*result)[length - 1] == '0')
        {
            (*result)[length - 1] = 0;
            length--;
        }
        if ((*result)[length - 1] == '.')
            (*result)[length - 1] = 0;
    }
}
