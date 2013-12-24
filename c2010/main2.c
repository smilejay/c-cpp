/* 例2    main2.c
 * 演示C语言中的内存分配。
 */

#include <stdio.h>

//返回char型指针
char *f()
{
    //s数组存放于栈上
    char s[4] = {'1','2','3','0'};
    return s; //返回s数组的地址，但程序运行完s数组就被释放了
}

int main()
{
    char *s;
    s = f();
    printf("%s", s); //打印出来乱码。因为s所指向地址已经没有数据
    return 0;
}
