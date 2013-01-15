#include <stdio.h>
#include <string.h>
#include <assert.h>

int myStrlen(const char *str);
int myStrlen1(const char *str);
int myStrlen2(const char *str);

int main()
{
	char *str=NULL;
	str = "Hello Jay!";
	printf("original strlen():%d\n",strlen(str));
	printf("myStrlen():%d\n",myStrlen(str));
	printf("myStrlen1():%d\n",myStrlen1(str));
	printf("myStrlen2():%d\n",myStrlen2(str));
}

int myStrlen(const char *str)   /* 不用中间变量，用递归实现，很容易看懂 */
{
	if ( (str == NULL) || (*str == '\0') ) {
		return 0;
	}
	else {
		return myStrlen(str+1)+1;
	}
}

int myStrlen1(const char *str)  /* 不用中间变量，也是用递归实现，写得更简洁而已 */
{
	assert(str != NULL);
	return *str ? (myStrlen1(++str) + 1) : 0;
}

int myStrlen2(const char *str)  /* 使用了一个int型变量 */
{
	if(str==NULL) return 0;
	int len = 0;
	for(; *str++ != '\0'; )
	{
		len++;
	}
	return len;
}
