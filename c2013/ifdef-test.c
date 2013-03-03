/*
 * a demo to use ifdef  or  defined()
 *
*/
#include    <stdio.h>

#if defined(linux) || defined(__linux__)
	#define SYS "Linux"
#else 
	#ifdef WIN32
		#define SYS "Win32"
	#else
		#define SYS "unknown-sys"
	#endif
#endif


int main(int argc, char *argv[])
{
	printf("This system is a/an %s\n", SYS);
}
