/* 
 *VMI模式下供应商易腐品库存系统仿真
 *模型二：基于需求量的库存控制模型
 *-------------------------------------------------------------------------------------------------
 *| 参数意义：                                                                                    |
 *|    Valve:阀门，当需求累计到Valve时发货; S:库存定制点；thet:变质率；bl:backlog累计未满足订货； |
 *|    inv:inventory，库存(inv0为初始库存)； deliveringTimes，发货次数； j:进货次数；             |
 *|    A:一次订货费用；TA:订货总费用；F:一次发货费用；TF:发货总费用；sumInv/sumBl库存和缺货累计   |
 *|    B:存储费用(2*inv)； L:缺货损失(3*bl)； Total：总费用；Lamda：需求的总体平均数；            |
 *|    Times:计算次数；t:计算0~t的时间段； fileString：生成数据的路径和文件名。                   |
 *|------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define S 500            /* S 为库存订制点，这里定义为一个宏*/

int demand(int t);
int count(int t, int Valve, double * p_sumBl,  double * p_sumInv, int * p_deliveringTime, double *p_deterioration);
double U_Random();
int possion();
void printResult(int t, double storage, int T_Valve, double inv, double backlog, int deliveringTimes, int j,
		double TA, double B, double L, double F, double TD, double Total);

void main()
{
	int t, j, deliveringTimes, Valve, storage;  /*  Valve阀门，当需求累计到Valve时就发货 */
	double A, TA, B, L, F, TF, Total, D, TD, sumInv, sumBl;   /* bl->backlog累计未满足订货 */
	double deterioration;
	/* char fileString[128]="E:\\workspace\\simulation\\Result_based_on_quantity.txt"; */
	int i,Times;
	Times = 2;  /* 设置产生多少次数据 */
	t = 200;
	Valve = 80;
	storage = S;  /* 用变量保存库存订制点，S为库存订制点  */
	for(i=1;i<=Times;i++)
	{
		sumInv = 0;
		sumBl = 0;
		deliveringTimes=0;
		deterioration = 0;
		j = count(t, Valve, &sumBl, &sumInv, &deliveringTimes, &deterioration);
		A = 60;
		TA = A * j;
		B = 2 * sumInv;   /* 累计库存损失 B */
		L = 3 * sumBl;   /* 累计缺货损失 L */
		F = 40;
		TF = F * deliveringTimes;
		D = 10;   /* 单位数量的货物变质的损失 */
		TD = D * deterioration;
		Total = TA + B + L + TF + TD;
		printResult(t,storage,Valve,sumInv,sumBl,deliveringTimes,j,TA,B,L,TF,TD,Total);
		printf("------------------------------------------------------------------------------\n");
	}
	/* printf("\n------------------------------------------------------------------------------\n");
	   printf("To find your data at \"%s\"\n",fileString);
	   printf("------------------------------------------------------------------------------\n"); */
}

/* 返回进货次数，以指针作为参数，是为了在main函数中使用指针所指的值*/
int count(int t, int Valve, double * p_sumBl,  double * p_sumInv, int * p_deliveringTimes, double *p_deterioration)
{
	double bl=0, inv, inv0 = 1000;  /*inv0为初始库存，inv为当前时刻库存 bl为当前时刻的缺货损失*/
	int i=0, j=0;
	double thet = 0.03;   /*thet为变质率*/
	inv = inv0;
	for (i=0;i<=t;i++)
	{
		bl += demand(i);
		if ( bl >= Valve)   /* 超过阀门则发货 */ 
		{
			if (inv >= bl)    /* 发货，不用进货*/
			{
				inv -= bl;  
			}
			else   /*先进货，再发货，维持库存订制点S，记录发货次数 */
			{
				inv = S;   
				j++;  
			}
			bl = 0;
			(*p_deliveringTimes)++;   /* 发货次数加1 */
		}
		*p_sumBl += bl;
		*p_sumInv += inv;
		*p_deterioration += (inv * thet);
		inv *= (1-thet);        
	}       
	return j;

}

int demand(int t)    /* 零售商的需求，直接返回一个泊松分布的随机数 */
{
	int d;
	d = possion();
	return d;
}

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

double U_Random()   /* 产生一个0~1之间的随机数 */
{
	static int done = 0;
	int number;
	if(!done)    /*srand种子只产生一次*/
	{  
		srand((int)time(0));
		done = 1;
	}
	number=1+(int)(100.0*rand()/(RAND_MAX+1.0));
	return number/100.0;
}

/* 打印输出结果函数 */
/* 
 *其他各个参数就分别是需要写入文件的值，此处已固定，可根据实际需要修改
 *
*/
void printResult(int t, double storage, int T_Valve, double sumInv, double sumBl, int deliveringTimes, int j,
		double TA, double B, double L, double F, double TD, double Total)
{   
	printf("仿真时间长度t=%d\n",t);
	printf("库存定制点  S=%f\n",storage);
	printf("发货数量阀门  Valve=%d\n",T_Valve);
	printf("累计库存量sumInv=%f\n",sumInv);
	printf("累计未满足的需求sumBl=%f\n",sumBl);
	printf("发货次数deliveringTimes=%d\n",deliveringTimes);
	printf("进货次数   j=%d\n",j);
	printf("订货费用  TA=%f\n",TA);
	printf("存储费用   B=%f\n",B);
	printf("缺货损失   L=%f\n",L);
	printf("发货费用  TF=%f\n",F);
	printf("变质损失费TD=%f\n",TD);
	printf("总费用 Total=%f\n",Total);
}
