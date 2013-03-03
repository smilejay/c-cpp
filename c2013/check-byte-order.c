/*
 * to check the byte order of a system using a union's policy of storing its items.
 * date: 2013-03-03
*/

#include    <stdio.h>

int check_byte_order()
{
	union myunion {
		int a;
		char b;
	} u;
	u.a = 1;
	if ( 1 == u.b )
		return 1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	if ( check_byte_order() )
		printf("This system is Little-Endian.\n");
	else
		printf("This system is Big-Endian.\n");
}
