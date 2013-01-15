#include    <stdio.h>

#define    N 5

void printArray(int arr[], int len);
void printMin(int min, char* method_name);
void findMin_1(int arr[], int* pMin);
void findMin_2(int arr[], int* pMin);
void findMin_3(int arr[], int* pMin);


int main(int argc, char *argv[])
{
	int array[N]={70,65,20,80,50};
	int min;
	printArray(array,N);
	findMin_1(array,&min);
	printMin(min,"findMin_1");
	findMin_2(array,&min);
	printMin(min,"findMin_2");
	findMin_3(array,&min);
	printMin(min,"findMin_3");
}

/*打印原数列*/
void printArray(int arr[], int len)
{
	int i;   
	printf("the array is:\n");
	for( i=0 ; i<len ; i++ )
	{  
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

/*打印得到的最小数字，也打印出哪种方法计算的*/
void printMin(int min, char* method_name)
{
	printf("%s---the Minimum item is:\n%d\n",method_name,min);
}

/*用三目运算符来代替if*/
void findMin_1(int arr[], int* pMin)
{
	int i=0;
	*pMin=arr[0];
	for( i=1 ; i<N ; i++ )
	{  
		*pMin=(*pMin-arr[i]>0)?arr[i]:*pMin;
	} 
}

/*用switch来代替if，并且用了位运算来实现比较两个的大小(对二者之差的最高位为0或1的判断)*/
void findMin_2(int arr[], int* pMin)
{
	int i=0;
	*pMin=arr[0];
	for( i=1 ; i<N ; i++ )
	{
		switch ( (*pMin-arr[i])>>(8*sizeof(int)-1) )
		{
			case 0 :
				*pMin=arr[i];
				break;
			case 1 :
				break;
			default :
				break;
		}
	}

}

/*用while+break语句来替代了if*/
void findMin_3(int arr[], int* pMin)
{
	int i=0;
	*pMin=arr[0];
	for( i=1 ; i<N ; i++ )
	{
		while( *pMin - arr[i] > 0 )
		{
			*pMin=arr[i];
			break;
		}
	}
}
