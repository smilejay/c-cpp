#include <stdio.h>

/* void swap(unsigned char *a, unsigned char *b);*/
void swap(unsigned int *a, unsigned int *b);

int main()
{
	/* unsigned char aa,bb; */
	unsigned int aa,bb;
	aa = 100000000;
	bb = 200000000;
	swap(&aa,&bb);
	printf("aa=%d,bb=%d\n",aa,bb);
	return 0;
}

/* void swap(unsigned char *a, unsigned char *b)
{
	*a = *a+*b;
	*b = *a-*b;
	*a = *a-*b;
}
*/

void swap(unsigned int *a, unsigned int *b)
{
	*a = *a+*b;
	*b = *a-*b;
	*a = *a-*b;
}
