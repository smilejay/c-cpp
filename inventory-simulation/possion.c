#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double U_Random();

int possion()  /* 产生一个泊松分布的随机数，Lamda为总体平均数*/
{
	int Lambda = 20, k = 0;
	long double p = 1.0;
	long double l=exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
	while (p>=l)
	{
		double u = U_Random();
		p *= u;
		k++;
	}
	return k-1;
}

double U_Random()  /* 产生一个0~1之间的随机数 */
{
	static int done = 0;
	int number;
	if(!done)  /*srand种子只产生一次*/
	{  
		srand((int)time(0));
		done = 1;
	}
	number=1+(int)(100.0*rand()/(RAND_MAX+1.0));
	return number/100.0;
}

