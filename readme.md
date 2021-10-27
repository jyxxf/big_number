1. The zero before the number is illegal. For example `plus("09", "6541.25", &result);`
If you do this, the result may be unpredictable.
2. The '+' before the number is legal.
3. If the divisor is 0, the result will be _"999999.99999"_.
4. The program will delete the additional zero in the end. For example `plus("3.33", "0.07", &result);`
the result is _"3.4"_ but not _"3.40"_.
----------
~~1.加法：
考虑到了开头为-号的情况，其余位清零
按小数点分为4种情况，总是先加小数再加整数，随后反转
\
2.减法
先进行比较大小
大的减小的正常，小的减大的加负号
反转
\
3.乘法
像小学列竖式那样挨个相乘，保存在temp数组中，
从第二个结果开始依次乘10 100······再相加，最后考虑添加小数点，
\
4.除法
除数和被除数先同乘10的倍数，保证除数为整数，
再用被除数的每个数字挨个除以除数~~
