/* 
 *VMI模式下供应商易腐品库存系统仿真
 *模型二：基于需求量的库存控制模型
 *-------------------------------------------------------------------------------------------------
 *| 参数意义：                                                                                    |
 *|    Valve:阀门，当需求累计到Valve时发货; S:库存定制点；thet:变质率；bl:backlog累计未满足订货； |
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

#define S 500            /* S 为库存订制点，这里定义为一个宏*/

int demand(int t);
int count(int t, int Valve, double * bl,  double * inv, int * p_deliveringTime);

extern double inv = 0, inv0 = 1000;  /*inv0为初始库存，inv为库存   都设为全局变量*/

void main()
{
	int t, j, deliveringTimes, Valve;  /*  Valve阀门，当需求累计到Valve时就发货 */
	double A, TA, B, L, F, TF, Total, bl;   /* bl->backlog累计未满足订货 */
	char fileString[128]="E:\\workspace\\simulation\\Result_based_on_quantity.txt";
	int i,Times;
	int flag;   /* 写文件函数 成功与否的标志  */
	Times = 5;  /* 设置产生多少次数据 */
	t = 200;
	inv = inv0;
	bl = 0;
	Valve = 80;
	for(i=1;i<=Times;i++)
	{
		deliveringTimes=0;
		j = count(t, Valve, &bl, &inv, &deliveringTimes);
		A = 60;
		TA = A * j;
		B = 2 * inv;
		L = 3 * bl;   /* 缺货损失 L*/
		F = 40;
		TF = F * deliveringTimes;
		Total = TA + B + L + TF;
		flag = writeFile(fileString,t,S,Valve,inv,bl,deliveringTimes,j,TA,B,L,TF,Total);
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

/* 返回进货次数，以指针作为参数>，是为了在main函数中使用指针所指的值*/
int count(int t, int Valve, double * p_bl,  double * p_inv, int * p_deliveringTimes)
{
	int i=0, j=0;
	double thet = 0.03;   /*thet为变质率*/
	for (i=0;i<=t;i++)
	{
		*p_bl += demand(i);
		if ( *p_bl >= Valve)   /* 超过阀门则发货 */ 
		{
			if (*p_inv >= *p_bl)    /* 发货，不用进货*/
			{
				*p_inv -= *p_bl;  
			}
			else   /*先进货，再发货，维持库存订制点S，记录发货次数 */
			{
				*p_inv = S;   
				j++;  
			}
			*p_bl = 0;
			(*p_deliveringTimes)++;   /* 发货次数加1 */
		}
		*p_inv *= (1-thet);	
	}	
	return j;

}

int demand(int t)  /* 零售商的需求，直接返回一个泊松分布的随机数 */
{
	int d;
	d = possion();
	return d;
}
