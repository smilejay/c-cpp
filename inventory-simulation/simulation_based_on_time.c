/* 
 *VMI模式下供应商易腐品库存系统仿真
 *模型一：基于时间的库存控制模型
 *-------------------------------------------------------------------------------------------------
 *| 参数意义：                                                                                    |
 *|    T:发货的时间周期; S:库存定制点；thet:变质率；bl:backlog累计未满足订货；                    |
 *|    inv:inventory，库存(inv0为初始库存)； deliveringTimes，发货次数； j:进货次数；             |
 *|    A:一次订货费用；TA:订货总费用；F:一次发货费用；TF:发货总费用；                             |
 *|    B:存储费用(2*inv)； L:缺货损失(3*bl)； Total：总费用；Lamda：需求的总体平均数；            |
 *|    Times:计算次数；t:计算0~t的时间段； fileString：生成数据的路径和文件名。                   |
 *|------------------------------------------------------------------------------------------------
*/

#include "stdio.h"
#include "math.h"
#include "possion.c"
#include "writeFile.c"

#define S 500    /* S 为库存订制点，此处定义为一个宏 */

int demand(int t);
int count(int T, int t, int *p_deliveringTimes);
float backlog(int T, int t);

extern double inv = 0, inv0 = 1000;  /*inv0为初始库存，inv为库存   都设为全局变量*/

void main()
{
	int t, T, j, deliveringTimes;
	double A, TA, B, L, F,TF, Total,bl;
	char fileString[128]="E:\\workspace\\simulation\\Result_based_on_time.txt";
	int i,Times;   
	int flag;    /* 写文件函数 成功与否的标志  */
	Times = 5;  /* 设置产生多少次数据 */
	T = 3;
	t = 200;
	inv = inv0;
	deliveringTimes=0; 
	for(i=1;i<=Times;i++)
	{
		deliveringTimes=0;
		j = count(T,t,&deliveringTimes);
		printf("%d次\n",j);
		printf("----------------华丽的分割线-----------\n",j);
		A = 60;
		TA = A * j;
		B = 2 * inv;
		bl = backlog(T,t);
		L = 3 * bl;   /* 缺货损失 L*/
		F = 40; 
		TF = F* deliveringTimes;
		Total = TA + B + L + TF;
		flag = writeFile(fileString,t,S,T,inv,bl,deliveringTimes,j,TA,B,L,TF,Total);
		if (flag == 0) 
		{
			printf("---the %dth time: OK---\n",i);
		}
		else printf("writeFile error.\n");
	}
	printf("\n------------------------------------------------------------------------------\n");
	printf("To find your data at \"%s\"\n",fileString);
	printf("------------------------------------------------------------------------------\n");
}

/* 计算进货次数，每T个单位时间发一次货，0~t 时间范围内进货次数*/
int count(int T, int t, int *p_deliveringTimes)
{
	int i=0, j=0;
	double thet = 0.03;   /*thet为变质率*/
	for (i=0;i<=t;i++)
	{
		if ( i%T == 0 && i != 0)
		{
			float bl = backlog (T,i);
			if( inv >= bl )  /* 发货，不用进货*/
			{
				inv -= bl;
			}
			else      /*先进货，再发货，维持库存订制点S，记录发货次数 */
			{
				j++;   /* 进货次数加1 */
				inv = S;
			}
			(*p_deliveringTimes)++;   /* 发货次数加1 */
		}
		inv *= (1-thet);
	}	
	return j;

}

float backlog(int T, int t)   /*累计未满足订货量*/
{
	float backlog=0.0;
	int t1, loopCount=1;
	if (t==0) return demand(0);
	if (t<=T && t>0)    /*对于t<=T的情况比较特殊，需要添加一个demand(0)*/
	{
		backlog = demand(0);    
	}
	else
	{
		backlog = 0.0;
	}
	if (t % T == 0 && T>0) 
	{
		loopCount = T;	
	}
	else
	{
		loopCount = t % T;
	}
	for (t1=1; t1<=loopCount; t1++)
	{
		int tt = t-T+t1;
		backlog += demand(tt);
	}
	return backlog;
}

int demand(int t)   /* 零售商的需求，直接返回一个泊松分布的随机数 */
{
	int d;
	d = possion();
	return d;
}
