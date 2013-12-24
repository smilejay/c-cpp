/* 例1    main1.c
 * 演示C程序中的内存分配方式。
*/
#include <stdlib.h>
#include <string.h>

int a = 0; //全局初始化区
char *p1; //全局未初始化区

int main()
{
    int b; //栈
    char s[] = "abc"; //s在栈,"abc\0"在文字常量区
    char *p2; //栈
    char *p3 = "123456"; //"123456\0"在常量区，p3在栈上
    static int c =0; //全局区
    p1 = (char *)malloc(10); //p1在栈，分配的10字节在堆
    p2 = (char *)malloc(20); //p2在栈，分配的20字节在堆
    strcpy(p1, "123456"); //"123456"放在常量区，编译器可能会优化为和p3的指向同一块区域
    return 0;
}
