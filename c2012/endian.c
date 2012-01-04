/*
 * To check CPU is Little endian or Big endian.
 *                 x86 is little-endian, most of other CPUs (e.g. ARM) are big-endian.
 * Author: Jay Ren
 * Date: 2012.01.04
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	int num = 1;
	if(*(char*)&num == 1)
		printf("Your CUP is Little Endian.\n");
	else
		printf("Your CUP is Big Endian.\n");
}
