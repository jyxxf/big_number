#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

#define compare_result(result, aim)                    \
    do                                                 \
    {                                                  \
        if (strcmp(result, aim) != 0)                  \
        {                                              \
            printf("line %u error! \n", __LINE__ - 1); \
            printf("yours is %s\n", result);           \
            printf("true  is %s\n", aim);              \
        }                                              \
    } while (0);

static void test_plus(void);
static void test_minus(void);
static void test_multiply(void);
static void test_divide(void);

int main(void)
{
    test_plus();
    test_minus();
    test_multiply();
    test_divide();
    return 0;
}

static void test_plus(void)
{
    char *result = (char *)calloc(1, 1);
    plus("2.035", "+6541.25", &result);
    compare_result(result, "6543.285");
    plus("5646545654654646462262489849494.262254598498494949",
         "8948948489449448494494949849.6526586489489498494944494894944989", &result);
    compare_result(result, "5655494603144095910756984799343.9149132474474447984944494894944989");
    plus("556", "9999955410", &result);
    compare_result(result, "9999955966");
    plus("65069196000000", "976037940000000", &result);
    compare_result(result, "1041107136000000");
    plus("556", "9999955410.0358776543255678891", &result);
    compare_result(result, "9999955966.0358776543255678891");
    plus("-6699345645645624234333", "-332.015", &result);
    compare_result(result, "-6699345645645624234665.015");
    plus("2.010101", "-2.00", &result);
    compare_result(result, "0.010101");
    plus("-2.01", "+65412589.220201456987452", &result);
    compare_result(result, "65412587.210201456987452");
    plus("+0", "-0", &result);
    compare_result(result, "0");
    plus("+3.33", "0.07", &result);
    compare_result(result, "3.4");
    plus("+0.0000000000000", "-0.00", &result);
    compare_result(result, "0");
    plus("2.23", "-2.23", &result);
    compare_result(result, "0");

    result = realloc(result, strlen("+3454564538374.2344532") + 1);
    memcpy(result, "+3454564538374.2344532", strlen("+3454564538374.2344532") + 1);
    plus(result, "23555.235432888400", &result);
    compare_result(result, "3454564561929.4698860884");

    result = realloc(result, strlen("325345.98") + 1);
    memcpy(result, "325345.98", strlen("325345.98") + 1);
    plus(result, result, &result);
    compare_result(result, "650691.96");
    free(result);
}

static void test_minus(void)
{
    char *result = (char *)calloc(1, 1);
    minus("36542.265", "36542.265", &result);
    compare_result(result, "0");
    minus("0.00", "-0.000", &result);
    compare_result(result, "0");
    minus("+8956412.000", "+1.013546874456321459874563214566", &result);
    compare_result(result, "8956410.986453125543678540125436785434");
    minus("23555.235432888400", "3454564538374.2344532", &result);
    compare_result(result, "-3454564514818.9990203116");
    minus("-34765847658.32145354235453414", "47684567573468256482.231453556235523", &result);
    compare_result(result, "-47684567608234104140.55290709859005714");
    minus("1.1", "5596.254", &result);
    compare_result(result, "-5595.154");
    minus("-56.21", "-541.000", &result);
    compare_result(result, "484.79");
    minus("65564653121214", "2654645131454645484", &result);
    compare_result(result, "-2654579566801524270");
    minus("+435342535243543", "345345.234312435345", &result);
    compare_result(result, "435342534898197.765687564655");
    minus("+342535243543.657534523424", "9345344541345", &result);
    compare_result(result, "-9002809297801.342465476576");
    minus("999", "0.0", &result);
    compare_result(result, "999");
    minus("523.01", "23", &result);
    compare_result(result, "500.01");
    minus("2", "2.0000000000000000000001", &result);
    compare_result(result, "-0.0000000000000000000001");
    minus("231.021", "-6541.23482147", &result);
    compare_result(result, "6772.25582147");
    minus("444422", "3.0000000000", &result);
    compare_result(result, "444419");
    minus("-2.01", "+555.5555", &result);
    compare_result(result, "-557.5655");
    minus("156", "160", &result);
    compare_result(result, "-4");

    result = realloc(result, strlen("3458374.2344532") + 1);
    memcpy(result, "3458374.2344532", strlen("3458374.2344532") + 1);
    minus(result, "435254523555.235432888400", &result);
    compare_result(result, "-435251065181.0009796884");

    result = realloc(result, strlen("-325345.98") + 1);
    memcpy(result, "-325345.98", strlen("-325345.98") + 1);
    minus(result, result, &result);
    compare_result(result, "0");
    free(result);
}

static void test_multiply(void)
{
    char *result = (char *)calloc(1, 1);
    //测试0*0
    multiply("0.000", "0", &result);
    compare_result(result, "0");
    multiply("0", "-0", &result);
    compare_result(result, "0");
    multiply("-0", "+0.000", &result);
    compare_result(result, "0");
    multiply("-0.00", "-0.000", &result);
    compare_result(result, "0");
    //测试其中一方为0
    multiply("0.0000", "-0.334", &result);
    compare_result(result, "0");
    multiply("-0", "22.334", &result);
    compare_result(result, "0");
    multiply("-345.77", "-0", &result);
    compare_result(result, "0");
    multiply("-34.7534", "+0.000", &result);
    compare_result(result, "0");
    multiply("0", "+800", &result);
    compare_result(result, "0");
    multiply("456", "-0", &result);
    compare_result(result, "0");

    multiply("1.00000", "1.001", &result);
    compare_result(result, "1.001");
    multiply("3.13", "4.441", &result);
    compare_result(result, "13.90033");
    multiply("123456789.98765432", "9876543.123456", &result);
    compare_result(result, "1219326310196518.82533161172992");
    multiply("-3.0", "-4.441", &result);
    compare_result(result, "13.323");
    multiply("-313.13", "4.442487671", &result);
    compare_result(result, "-1391.07616442023");
    multiply("1.0", "+1.0", &result);
    compare_result(result, "1");
    multiply("-293324324548742", "91334534624242.00", &result);
    compare_result(result, "-26790640676629473861183803564");
    multiply("3232344567187", "746.9845323254576", &result);
    compare_result(result, "2414511394834914.8566937197712");
    multiply("+323.218723", "746", &result);
    compare_result(result, "241121.167358");
    multiply("-32345234", "4444441000", &result);
    compare_result(result, "-143756484144194000");
    multiply("0.001", "1000", &result);
    compare_result(result, "1");
    multiply("0.000000001", "-10", &result);
    compare_result(result, "-0.00000001");
    multiply("-1.20", "5.0", &result);
    compare_result(result, "-6");
    multiply("-325345.98", "-325345.98", &result);
    compare_result(result, "105850006702.1604");

    result = realloc(result, strlen("3458374.2344532") + 1);
    memcpy(result, "3458374.2344532", strlen("3458374.2344532") + 1);
    multiply(result, "-435254523555.235432888400", &result);
    compare_result(result, "-1505273029692629646.98031145567062288");

    result = realloc(result, strlen("-325345.98") + 1);
    memcpy(result, "-325345.98", strlen("-325345.98") + 1);
    multiply(result, result, &result);
    compare_result(result, "105850006702.1604");
    free(result);
}

static void test_divide(void)
{
    char *result = (char *)calloc(1, 1);
    // 0相关
    divide("-0", "-75435", 10, &result);
    compare_result(result, "0.0000000000");
    divide("-0", "754786858678456435.3454353453544", 10, &result);
    compare_result(result, "-0.0000000000");
    divide("-0.000000", "+754786858678456435.3454353453544", 10, &result);
    compare_result(result, "-0.0000000000");
    divide("-0.000000", "+754786858678456435", 10, &result);
    compare_result(result, "-0.0000000000");
    //整数除以整数
    divide("53", "52", 30, &result);
    compare_result(result, "1.019230769230769230769230769230");
    divide("52", "-53", 30, &result);
    compare_result(result, "-0.981132075471698113207547169811");
    divide("43857629876489230856", "98765", 10, &result);
    compare_result(result, "444060445263901.4919860274");
    divide("-1", "45342554365498765", 10, &result);
    compare_result(result, "-0.0000000000"); //不需要消除负号
    divide("1", "45342554365498765", 20, &result);
    compare_result(result, "0.00000000000000002205");
    divide("44", "44", 10, &result);
    compare_result(result, "1.0000000000");
    divide("44", "-44", 0, &result);
    compare_result(result, "-1");
    divide("434534255434", "-4565453424", 0, &result);
    compare_result(result, "-95");
    divide("434534255434", "+456587453424", 1, &result);
    compare_result(result, "0.9");
    divide("+4", "7", 20, &result);
    compare_result(result, "0.57142857142857142857");
    //小数除以整数
    divide("3.33", "4", 5, &result);
    compare_result(result, "0.83250");
    divide("-3.33", "+4", 0, &result);
    compare_result(result, "-0");
    divide("+333.000", "-333", 7, &result);
    compare_result(result, "-1.0000000");
    divide("3.0000", "7", 64, &result);
    compare_result(result, "0.4285714285714285714285714285714285714285714285714285714285714285");
    divide("333.000", "333", 0, &result);
    compare_result(result, "1");
    divide("2342345435345.234242352353", "2342435544", 28, &result);
    compare_result(result, "999.9615320664867107021464322520");
    divide("+97723.89732390472209", "-9678434352", 25, &result);
    compare_result(result, "-0.0000100970770446679289611");
    //整数除以小数
    divide("-234", "0.00001", 10, &result);
    compare_result(result, "-23400000.0000000000");
    divide("89734", "3.321", 0, &result);
    compare_result(result, "27020");
    divide("43523534653", "7.0000", 16, &result);
    compare_result(result, "6217647807.5714285714285714");
    divide("234534534564635234764545563425475636", "1.0", 3, &result);
    compare_result(result, "234534534564635234764545563425475636.000");
    divide("453532465345624352", "53452345233.312312548675621", 24, &result);
    compare_result(result, "8484800.121791027392187393132871");
    //小数除以小数
    divide("45.543", "-53433.3242876076", 39, &result);
    compare_result(result, "-0.000852333269681341065489332675114320114");

    result = realloc(result, strlen("3458374.2344532") + 1);
    memcpy(result, "3458374.2344532", strlen("3458374.2344532") + 1);
    divide(result, "-435254523555.235432888400", 20, &result);
    compare_result(result, "-0.00000794563651218278");

    result = realloc(result, strlen("-325345.98") + 1);
    memcpy(result, "-325345.98", strlen("-325345.98") + 1);
    divide(result, result, 10, &result);
    compare_result(result, "1.0000000000");
    free(result);
}

void reverse(char **result) //第一个是负号不翻转，其余逆序输出
{
    size_t last = 0;
    while ((*result)[last])
        last++;
    for (size_t i = 0; i < last / 2; i++)
    {
        char temp = (*result)[i];
        (*result)[i] = (*result)[last - i - 1];
        (*result)[last - i - 1] = temp;
    }
}

void delete_0(char **result)
{
    if ((*result)[0] == '+' || (*result)[0] == '-')
    {
        char *temp = *result + 1;
        delete_0(&temp);
        if ((*result)[0] == '+')
            memmove(*result, *result + 1, strlen(*result)); //+号消除
        else if ((*result)[1] == '0' && (*result)[2] == 0)
            memmove(*result, *result + 1, 2); //-0变为0
        return;
    }
    //消除前导0
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
    if (point == NULL)
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
