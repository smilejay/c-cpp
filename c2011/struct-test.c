/* 
 * This sample shows definition and initiation of a struct and a union in a struct. using GCC
 * Author: Jay Ren
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
	struct my_struct1 {
		int num1;
		union {
			int num2;
			char ch;
		};
	};
	
	struct my_struct1 my_st1 = {
		.num1 = 111,
		/* the following commented line will cause a syntax error. */
		/* .num2 = 123456,*/
	};

	/* num2 or ch in the union of the struct can't be initiated before. */
	my_st1.num2 = 123456;

	printf("my_st1.num1 = %d\n", my_st1.num1);
	printf("my_st1.num2 = %d\n", my_st1.num2);
	
	struct my_struct2 {
		int num1;
		union my_union {
			int num2;
			char ch;
		} my_u;
	};
	
	struct my_struct2 my_st2 = {
		.num1 = 222,
		/*  the following line for initiating num2 works fine. */
		.my_u.num2 = 123456,
	};

	printf("my_st2.num1 = %d\n", my_st2.num1);
	printf("my_st2.num2 = %d\n", my_st2.my_u.num2);
	
	return 0;
}
