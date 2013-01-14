void swap1(int*a,int*b)//第一种，也是最常用的一种
{
	intt;
	t=*a;
	*a=*b;
	*b=t;
}

void swap2(int*a,int*b)//第二种，不需要额外的内存空间（不用临时变量）
{
	*a=*a+*b;
	*b=*a-*b;
	*a=*a-*b;
}

void swap3(int*a,int*b)//第三种，不需要额外的内存空间，位运算实现
{
	*a^=*b;
	*b^=*a;
	*a^=*b;
}
