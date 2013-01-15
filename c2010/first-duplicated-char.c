#include    <string.h>
#include   <stdio.h>

int first_dup_char(char* str);

int main(int argc, char *argv[])
{
	char* str="abcdefgg";
	int num=0;
	num = first_dup_char(str);
	if( num == -1 )
	{  
		printf("There's no duplicated char in the string:\n");
		printf("%s\n",str);
	}  
	else {
		printf("the first duplicated char is str[%d]='%c' in the string:\n",num,str[num]);
		printf("%s\n",str);
	}  
}

int first_dup_char(char* str)
{
	int num=0;
	int j=0;
	for( num = 0 ; num<strlen(str) ; num++ )
	{  
		for( j=num+1 ; j<strlen(str) ; j++ )
		{  
			if( str[num] == str[j] )
			{  
				return num;
			}  
		}  
	}  
	if( num == strlen(str) )
	{  
		return -1;
	}  
}
