1. The variable to save the result must be allocated on the heap instead of the stack. 
In other words, the variable must be dynamically allocated.
2. The number in parameter is illegal and the string is legal. For example `multiply(9, 6, &result);`You should use `multiply("9", "6", &result);`
3. The zero before the number is illegal. For example `plus("09", "6541.25", &result);`If you do this, the result may be unpredictable.
4. The '+' before the number is legal.
5. If the divisor is 0, the result may also be unpredictable.
6. The program will delete the additional zero in the end except division. For example `plus("3.33", "0.07", &result);`
The result is _"3.4"_ but not _"3.40"_.
7. The result won't be *+0* or *-0* but will be *0* in plus, minus and multiply.
8. no memory leak
9. **You should look at the test cases in `main` function before you use it.**
10. E-mail jyygxxf@outlook.com if having any questions.
