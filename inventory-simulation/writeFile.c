/* 写文件的程序 */

#include <stdio.h>

/* 写文件的函数 */
/* fileString是文件路径和名称，字符数组类型
 * 其他各个参数就分别是需要写入文件的值，此处已固定，可根据实际需要修改
*/
int writeFile(char *fileString, int t, double S, int T_Valve, double inv, double backlog, int deliveringTimes, int j, 
		double TA, double B, double L, double F, double Total)
{
	static int times = 0;  /* 定义一个static的变量来记录读写文件的次数*/
	FILE *fp;
	times++;  

	if ((fp = fopen(fileString, "at+")) == NULL) /* open file **.txt  追加方式打开*/
	{
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}

	fprintf(fp, "--------------第%d次运算------------\n",times);
	fprintf(fp, "仿真时间长度t=%d\n",t);
	fprintf(fp, "库存定制点  S=%f\n",S);
	fprintf(fp, "发货周期或者发货数量阀门  T_Valve=%d\n",T_Valve);
	fprintf(fp, "当前库存量inv=%f\n",inv);
	fprintf(fp, "当前为满足的需求backlog=%f\n",backlog);
	fprintf(fp, "发货次数deliveringTimes=%d\n",deliveringTimes);
	fprintf(fp, "进货次数   j=%d\n",j);
	fprintf(fp, "订货费用  TA=%f\n",TA);
	fprintf(fp, "存储费用   B=%f\n",B);
	fprintf(fp, "缺货损失   L=%f\n",L);
	fprintf(fp, "发货费用  TF=%f\n",F);
	fprintf(fp, "总费用 Total=%f\n",Total);

	fprintf(fp,"\n");

	if (fclose(fp) == 1 )  /* close file */
	{
		printf("Error occured when closing file..\n"); 
	}
	else 
	{
		printf("Write && Close file...success\n");
	}
	return 0;
}
