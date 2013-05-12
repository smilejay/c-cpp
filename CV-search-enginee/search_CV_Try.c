/* ----------------  CV Search Engine v1.0 --------------- */
/*  Copyright @ Try Team in Seedcoder programming contest. */
/*  Authors: Jay.Ren and Chy                               */
/*  Date in Produced: April 13th, 2008.                    */  
/*---------------------------------------------------------*/

#include "stdlib.h"    /* These .h files will be used in this program */
#include "stdio.h"
#include "string.h"
#include "dir.h"

struct words      /* 定义一个结构体用于保存输入的字符串以及搜索类型标志flag */
{
	char str1[128];
	char str2[128];
	int flag;       
};

/*声明需要调用的子函数*/
void display_0();   /* To display 'Welcome' interface */
void getword(char *str_in, char *str1, char *str2, int *flag);   /* To catch INPUT */
void find_file(char fname[][20],int *p_m);     /* To find .txt file */
void readfile(char *fname,char *p[7],char *files);  /*To read file and store the string */
int index_kmp(char S[], char T[]) ;            /*   Classic KMP Algorithm  */ 
int match(struct words words,char *p[7],char *applicant_name,char *one_item);
    /*match() 返回搜索结果的标志find_flag，为1则匹配成功，为0则没有成功*/ 

/* ———————— To  start main fuction ———————— */
void main()
{
	char ts[9990],s1[128],s2[128],*pc[7];/*fname[]="alex_cv.txt";*/
	struct words words;
	int  flag,find_flag=0,find_flag_1;
	int  i=0;
	char fname[1000][20];     /*To  store the .txt file names*/
	int  m=0;                 /*To count the NO. of the .txt files in current path*/
	char app_name[300][128];  /*满足某一项要求的最多限定在300人内*/
	char applicant_name[128],one_item[1000];
	char item[10][1000];      /*10用来表示同名的情况最多10人*/
	int  cou;                 /* To count how many CVs are matching */

	display_0();                /* To display 'Welcome' interface */
	while(1)                    /* 循环查找 */
	{ /**/
		cou = 0;
		find_flag_1 = 0;          /* 初始化 */

		do
		{
			gets(ts);             /*To get INPUT*/
		}
		while (ts[0]=='\0');      /* 防止循环查找出错 */
		if(strcmp(ts,"exit")==0 || strcmp(ts,"EXIT")==0)
			break;                /* 键入exit则结束程序 */
		getword(ts,s1,s2,&flag);
		strcpy(words.str1,s1);    /* 复制关键词串到结构体中，用于查找，下同 */
		strcpy(words.str2,s2);
		words.flag=flag;
		find_file(fname,&m);      /* 找目录下的所有txt文件名 */
		for(i=0;i<m;i++)          /*To read and match all the .txt files*/
		{
			readfile(fname[i],pc,ts);    /* 读一个文件 */
			if(pc[6]==&ts[0])
				continue;         /* pc[6]为存储串首址时，则为非简历文件，则不查找而continue循环 */
			find_flag=match(words,pc,applicant_name,one_item);     /* 内容查找匹配 */
			if(find_flag!=0)
			{
				if(flag==2) strcpy(item[cou],one_item);
				else strcpy(app_name[cou],applicant_name);
				cou++;           /* cou表示查找到简历的个数 */
				find_flag_1=1;
			}
		}       /*End for */
		if(find_flag_1 == 0) printf("Sorry! -- Can't find what you want!\n");
		else if(flag != 4)      /* 找到则输出结果 */
		{
			printf(" ************--------- Your search result --------**************\n");
			for(i=0;i<cou;i++)
			{		
				if(flag == 2) 
				{
					printf("%s\n",item[i]);
				}                /* 输出某项的内容 */
				else 
				{                /* 输出查找到的人名 */
					printf("%s",app_name[i]);
				}
			}

		}
		printf(" ***********------------ END search resut ---------*************\n");
		printf("Please input what you want to search in these CVs! (Input 'exit' to exit.)\n");
	}
	/*  display_1();
	 *   /*   free(applicant_name);
	 *       free(one_item); */
	printf(" **************Exit the CV Search Engine!************\n");
	printf(" -------------- See you next time !------------------\n");
}
/* —————— End main  ————————    */


void getword(char *str_in, char *str1, char *str2, int *flag)
{
	int i,j=0;
	char tmps[128];
	*flag=0;
	for(i=0; str_in[i]!='\0'; i++)    /* 输入串字符不是结束符\0，则循环 */
	{
		if(str_in[i]=='&')
		{
			tmps[j]='\0';
			*flag=1;             /* 与标志 */
			strcpy(str1,tmps);
			j=0;
		}
		else if(str_in[i]==':')
		{
			tmps[j]='\0';
			*flag=2;             /* 姓名标志 */
			strcpy(str1,tmps);
			j=0;
		}
		else if(str_in[i]=='|')
		{
			tmps[j]='\0';
			*flag=3;             /* 或标志 */
			strcpy(str1,tmps);
			j=0;
		}
		else if(str_in[i]==' '||str_in[i]=='	')
			;                    /* 空格和制表键忽略 */
		else
		{
			tmps[j]=str_in[i];
			if(tmps[j]>='A' && tmps[j]<='Z')
				tmps[j]=tmps[j]+'a'-'A';
			j++;
		}          /* 正常读字符，大写字母改为小写字母 */
	}
	tmps[j]='\0';
	if(j==0 && *flag==2)
		*flag=4;                 /* 标志flag=4,输出某人的全部资料 */
	if( *flag==1||*flag==2||*flag==3)
		strcpy(str2,tmps);       /* 如果是上述标志，则有两个关键字 */
	else if(*flag!=4)
	{     /* 如果是仅一个关键词的普通查找，则将临时串的内用复制至str1 */
		strcpy(str1,tmps);
		str2[0]='\0';
	}
}

void find_file(char fname[][20],int *p_m)   
{
	struct  ffblk  ffblk;       /*声明ffblk结构体存储每个文件的基本信息*/
	int done;
	int i=0;
	/*  int m=0;            /*To count the NO. of the .txt files in current dir*/
	/* printf("Directory   listing   of   *.txt\n");   /**/ 
	done = findfirst("*.txt",&ffblk,0);   /* 路径不对这里手动改!!! */
	if(done !=0) printf("Can't find txt file!\n");    /**/
	while (!done)     
	{
		strcpy(fname[i], ffblk.ff_name);  /*copy filename to fname[i]*/
		done = findnext(&ffblk);          /*To read next .txt file*/
		i++;    
	}  
	*p_m=i;

	return;
}

void readfile(char *fname,char *p[7],char *files) /*读取一份简历中的信息*/
{
	unsigned int i=0,j,k=0,len;
	char tmps[48],nospace[8120]; 
	char *item[6]={"Name:",
		"Education Background",
		"Position:",
		"Award",
		"Experience",
		"Technique",
	};                 /* 简历内容类别名称，条目名 */
	FILE *fp;

	if((fp=fopen(fname,"rb"))==NULL)
	{
		printf("can't open /%s/!!!\n",fname);
		exit(0);
	}                              /* 打不开文件则报错 */
	do
	{
		len=strlen(item[0]);       /* len是条目名称字符串的长度 */
		fread(tmps,len,1,fp);
		if(i>6)                    /* 如果读到文件位置地址大于6开始的串则跳出，说明这不是简历文本 */
			break;
		tmps[strlen(item[0])]='\0';
		fseek(fp,-(long)strlen(item[0])+1,SEEK_CUR);   /* 后退长度-1个位置，读下一地址开始的串 */
		i++;
	}
	while(strcmp(tmps,item[0])!=0);	    /* 是否为Name:? */
	if(i>6)
	{
		p[6]=&files[0];
		fclose(fp);
		return;
	}                /* 不是简历格式就跳出，函数返回时用p[6]是否为串首址来判断 */
	i=0;
	fseek(fp,(long)strlen(item[0])-1,SEEK_CUR);  /* 跳过条目 */
	p[0]=&files[0];
	for(j=1;j<6;j++)                      /* 循环读项目内容(不包括最后一个) */
	{
		do
		{
			do
			{
				fread(files+i,1,1,fp);
				if(files[i]!=' '&&files[i]!='	')
				{
					if(files[i]>='A'&&files[i]<='Z')
						nospace[k]=files[i]+'a'-'A';
					else
						nospace[k]=files[i];
					k++;            /* k为查找用的串(nospace临时暂存)的计数 */
				}                   /* 字符为非空格和制表键才另存，且大写改为小写 */
				i++;
			}while((files[i-1]!=(char)13)&&(feof(fp)==0));    /* 读内容，前后可能含空格 */
			files[i]=(char)10;		/* 0DH 0AH为回车符 */
			nospace[k]=files[i];
			i++;
			k++;
			if(feof(fp))
			{
				printf("\naddr=%x [%c]\t",ftell(fp),files[i]);
				break;
			}                        /* 这一个if语句是调试时用 */
			fseek(fp,1L,SEEK_CUR);   /* 暂时略去内容中的空格 */
			len=strlen(item[j]);
			fread(tmps,len,1,fp);    /* 读一行开始的条目长度的字符串 */
			tmps[len]='\0';
			fseek(fp,-(long)len,SEEK_CUR);    /* 文件位置指针返回 */
		}while(strcmp(tmps,item[j])!=0);      /* 读到条目名为止 */
		if(feof(fp))
			break;                   /* 这一个if语句是调试时用 */
		fseek(fp,(long)len,SEEK_CUR);         /* 跳过读过的字符，防读错 */
		files[i]='\0';
		i++;
		p[j]=&files[i];              /* 下一项简历内容指针存放 */
	}
	while(!feof(fp))               /* 读最后一项的内容，读到文件结束为止 */
	{
		fread(files+i,1,1,fp);
		if(files[i]!=' '&&files[i]!='	')
		{
			if(files[i]>='A'&&files[i]<='Z')
				nospace[k]=files[i]+'a'-'A';
			else
				nospace[k]=files[i];
			k++;
		}                  /* 非空格和制表键才另存，且大写改为小写 */
		i++;
	}
	files[i]='\0';
	i++;
	nospace[k]='\0';    /* 加上字符串结束符\0 */
	strcpy(files+i,nospace);      /* 将临时串的内容复制到文件总串的最后 */
	p[6]=files+i;       /* p[6]指向去空格制表键、大写改小写的总串 */
	fclose(fp);
}


/*   Classic KMP Algorithm  */ 
/*   Modified by Jay.Ren  2008.4.8    */      
void get_next(char T[], int next[])   /*计算修正后的next值*/
{
	int i, j, T_len;

	T_len = strlen(T);   
	i = 0;   j = -1;   
	next[0] = -1;   
	while (i < T_len) 
	{   
		if (j == -1 || T[i] == T[j]) 
		{   
			i++; j++;   
			next[i] = j; 
			if(T[i] != T[j])
			{next[i] = j;}                     
			else next[i] = next[j];
		}
		else j = next[j]; /* End if */     
	} /* End while */ 
}/* get_next */  

int index_kmp(char S[], char T[])   /* kmp法查找字符串 */
{   
	int i, j, *next;
	int S_len, T_len;   
	int k;   

	S_len = strlen(S);   
	T_len = strlen(T);   
	i = j = 0;   

	next = (int *)malloc(sizeof(char)*T_len);   
	if (!next)
	{    
		printf("-----Error!!!!-------Your input is illegal. ----\n");		
		printf("You must input something apart from space key !\n");  
		printf("Heap   full.\n");   
		exit(-1);  
	}  /**/ 
	get_next(T, next);  /* 载入修正后next */
	while (i < S_len && j < T_len)   
	{   
		if (j == -1 || S[i] == T[j])  
		{
			i++;  
			j++;   
		}
		else  
		{   
			j = next[j];   
		}   /* if */
	}/* while */   
	free(next);   
	if (j >= T_len) return (i - T_len);   
	else  return -1;    /*  未匹配成功，返回-1  */
}

int match(struct words words,char *p[7],char *applicant_name, char *one_item) /*对输入进行匹配*/
{
	int find_flag=0;   /*If these has benn found, find_flag=1; else  flag=0 */
	int i=0,j=0;
	char temp_name[20];    /* 暂存人名信息 */
	char *item[6]={"name:",
		"education background",
		"position:",
		"award",
		"experience",
		"technique",
	};        /* 统一用小写来判断 */
	for(i=0;p[0][i]!='\0';i++)   /**/
	{
		if(p[0][i]>='A' && p[0][i]<='Z')
		{
			temp_name[j]=p[0][i]+'a'-'A';
			j++;
		}
		else if(p[0][i]==' ' || p[0][i]=='	')
			;
		else
		{
			temp_name[j]=p[0][i];
			j++;
		}
	}                      /* 人名信息去空格、制表键、并将大写改为小写 */
	temp_name[j]='\0';
	i=0;                   /* i用完后，置零防错 */
	switch(words.flag)
	{
	case 0: /*search only item*/
		if(index_kmp(p[6],words.str1) != -1)
			find_flag=1;
		if(find_flag==1) strcpy(applicant_name,p[0])
			;
		else ;
		break;  /* break case 0 */
	case 1: /*search item_1 & item_2*/
		if(index_kmp(p[6],words.str1) != -1)
			find_flag=1;
		if(find_flag == 1)
		{
			find_flag=0;
			if(index_kmp(p[6],words.str2) != -1)
				find_flag=1;
			/*printf("find_flag=%d\n",find_flag);*/
			if(find_flag==1) strcpy(applicant_name,p[0])
				;
			else ;
		}
		else find_flag=0;
		break; /* break case 1 */
	case 2:    /*search one's item*/
		/* printf("p[0]=%s\tstr1=%s\n",p[0],words.str1);*/
		if(index_kmp(temp_name,words.str1) != -1)
		{
			for(i=0;i<6;i++)
			{
				if(index_kmp(item[i],words.str2) != -1)
					find_flag=1;
				if(find_flag==1)	break;
			}
			if(find_flag==1) strcpy(one_item,p[i])
				;
			else ;
		}
		else find_flag=0;
		break;  /* break case 2 */
	case 3: /*search item_1 or item_2*/
		if(index_kmp(p[6],words.str1) != -1)
			find_flag=1;
		if(find_flag != 1)
		{
			if(index_kmp(p[6],words.str2) != -1)
				find_flag=1;
			/*printf("find_flag=%d\n",find_flag);*/
		}
		if(find_flag==1) strcpy(applicant_name,p[0])
			;
		else ; /* end if(find_flag */
		break; /* break case 3 */
		case 4:   /* search one's integral CV content */
		if(index_kmp(p[6],words.str1) != -1)
		{
			find_flag=1;
			printf("Name:%s",p[0]);
			printf("Education background%s",p[1]);
			printf("Position:%s",p[2]);
			printf("Award%s",p[3]);
			printf("Experience%s",p[4]);
			printf("Technique%s",p[5]);
		}
		break;  /* end case 4 */
	default: break;   /* Default  */
	}  /* End swtich(words.flag) */
	return find_flag;   
}

void display_0()
{
	printf("     ********** Welcome To the CV Search Engine made by Try Team ! ********\n");
	printf("----------------------------- TIPS ---------------------------------------------\n");
	printf("     **----- 1. You may input any keyword to search.             -----**\n");
	printf("     **----- 2. You may use '&' to connet two keywords.          -----**\n");
	printf("     **----- 3. You may input 'A:item' to show A's item.         -----**\n");
	printf("     **----- 4. You may use '|' to search one of the two words.  -----**\n");
	printf("     **----- 5. You may input 'A:' to show A's integral CV.      -----**\n");
	printf("--------------------------------------------------------------------------------\n"); 
	printf("Please input what you want to search in these CVs! (Input 'exit' to exit.)\n"); 
}
/* —————————  CV Search Engine  ——————————— */

