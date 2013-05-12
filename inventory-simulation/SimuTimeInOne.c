/* 
 *VMI模式下供应商易腐品库存系统仿真
 *模型一：基于时间的库存控制模型
 *----------------------------------------------------------------------------------------------------
 *| 参数意义：                                                                                       |
 *|    T:发货的时间周期; S:库存定制点；thet:变质率；bl:backlog未满足订货；sumInv/sumBl库存和缺货累计 |
 *|    inv:inventory，库存(inv0为初始库存)； deliveringTimes，发货次数； j:进货次数；                |
 *|    A:一次订货费用；TA:订货总费用；F:一次发货费用；TF:发货总费用；TD:变质部分的损失费用;          |
 *|    B:存储费用(2*inv)； L:缺货损失(3*bl)； Total：总费用；Lamda：需求的总体平均数；               |
 *|    Times:计算次数；t:计算0~t的时间段； fileString：生成数据的路径和文件名。                      |
 *|---------------------------------------------------------------------------------------------------
 *
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define S 500    /* S 为库存订制点，此处定义为一个宏 */

int demand(int t);
int count(int T, int t, int *p_deliveringTimes, double *p_deterioration, double *p_sumInv, double *p_sumBl);
double backlog(int T, int t);
double U_Random();
int possion();
void printResult(int t, double storage, int T_Valve, double sumInv, double sumBl, int deliveringTimes, int j, 
		double TA, double B, double L, double F, double TD, double Total);

void main()
{
	int t, T, j, deliveringTimes, storage;  /* 因变质带来的损失量 */
	double A, TA, B, L, F, TF, Total, D, TD, sumBl, sumInv;
	double deterioration;
	/* char fileString[128]="E:\\workspace\\simulation\\Result_based_on_time.txt"; */
	int i,Times;   
	Times = 2;  /* 设置产生多少次数据 */
	T = 3;  /* 设置发货周期 */
	t = 200;
	storage = S;  /* 用变量保存库存订制点，S为库存订制点  */
	deliveringTimes=0; 
	for(i=1;i<=Times;i++)
	{
		sumBl = 0;
		sumInv = 0;
		deliveringTimes=0;
		deterioration = 0;
		j = count(T,t,&deliveringTimes,&deterioration,&sumInv,&sumBl);
		A = 60;
		TA = A * j;
		B = 2 * sumInv;  /* 累计库存损失  B */
		L = 3 * sumBl;   /* 累计缺货损失 L */
		F = 40; 
		TF = F* deliveringTimes;
		D = 10;   /* 单位数量的货物变质的损失 */
		TD = D * deterioration;
		Total = TA + B + L + TF + TD;
		printResult(t,storage,T,sumInv,sumBl,deliveringTimes,j,TA,B,L,TF,TD,Total);
		printf("------------------------------------------------------------------------------\n");
	}
	/* printf("------------------------------------------------------------------------------\n");
	   printf("To find your data at \"%s\"\n",fileString);
	   printf("------------------------------------------------------------------------------\n"); */
}

/* 计算进货次数，每T个单位时间发一次货，0~t 时间范围内进货次数*/
int count(int T, int t, int *p_deliveringTimes, double *p_deterioration, double * p_sumInv, double *p_sumBl)
{
	double inv, inv0 = 1000;  /*inv0为初始库存，inv为库存   都设为全局变量*/
	int i=0, j=0;
	double thet = 0.03;   /*thet为变质率*/
	inv = inv0;
	for (i=0;i<=t;i++)
	{
		double bl = backlog (T,i);
		if ( i%T == 0 && i != 0)
		{
			if( inv >= bl )  /* 发货，不用进货*/
			{
				inv -= bl;
			}
			else      /*先进货，再发货，维持库存订制点S，记录发货次数 */
			{
				j++;   /* 进货次数加1 */
				inv = S;
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

double backlog(int T, int t)   /*t时刻 当前未满足订货量*/
{
	double backlog=0.0;  /* backlog为某时刻的未满足订货量 sumBl为累计的为满足订货量*/
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

/* 打印结果函数 */
/* 
 * 其他各个参数就分别是需要写入文件的值，此处已固定，可根据实际需要修改
 *
*/
void printResult(int t, double storage, int T_Valve, double sumInv, double sumBl, int deliveringTimes, int j, 
		double TA, double B, double L, double F, double TD, double Total)
{    
	printf("仿真时间长度t=%d\n",t);
	printf("库存定制点  S=%f\n",storage);
	printf("发货周期    T=%d\n",T_Valve);
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
