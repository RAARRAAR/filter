/*
 ============================================================================
 Name        : fiter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 前提条件：使用米作为单位，使用秒作为单位，处理部分由于平均造成的虚假数据
           时间加长到80s，高度提升到800米
 ============================================================================
 */
#define LEN 80
#include <stdio.h>
#include <stdlib.h>
unsigned int static T_tempA,T_temp;

unsigned int fiter(unsigned int);
int fiter2(unsigned int TAB,unsigned int TA_C,int *TA_T);
int main(void)
{
	FILE *fp1;  //定义文件流指针，用于打开读取的文件
	char text[1024];//定义一个字符串数组，用于存储读取的字符
	fp1 = fopen("test.txt","r");//只读方式打开文件a.txt
	int i;
	T_tempA=1;
	i=0;
	while(fgets(text,1024,fp1)!=NULL)//逐行读取fp1所指向文件中的内容到text中
	{
	    T_temp=atof(text)+1;
		T_temp=fiter(T_temp);
		T_tempA=T_temp;
		sprintf(text,"%d",T_temp);
		puts(text);//输出到屏幕
		i=i+1;
	}
	fclose(fp1);//关闭文件a.txt，有打开就要有关闭
	return EXIT_SUCCESS;
}

unsigned int fiter(unsigned int TA)
{
	 unsigned int T_tempA_020;       //当前高度20%
     static unsigned int UpCount,DownCount;
     static unsigned int TA10,TA20;
     static unsigned int LostCount;
	 T_tempA_020=T_tempA*0.2;
     if (TA==0)
    	 TA=1;
	//**************************************************************************
	//防止由低高度向高高度跳变的滤波程序
	//**************************************************************************
	//      滤波时间5秒          报版本号后                   跳大值            跳变大于10倍              当前高度小于10米
	if((UpCount<5)&&(T_tempA<TA)&&((TA/T_tempA)>=10)&&(T_tempA<=10))
	{
        TA=T_tempA;//输出上次正常值
        UpCount++;
        return TA;
	}
	//      滤波时间1秒          报版本号后                   跳大值              差大于20%                       当前高度大于10米	  当前高度小于50米
	if((UpCount<2)&&(T_tempA<TA)&&((TA-T_tempA)>=T_tempA_020)&&(T_tempA>10)&&(T_tempA<=50))
	{
        TA=T_tempA;//输出上次正常值
        UpCount++;
        return TA;
	}
	//      滤波时间3秒          报版本号后                   跳大值              差大于20%                        当前高度大于50米	  当前高度小于300米
	if((UpCount<5)&&(T_tempA<TA)&&((TA-T_tempA)>=T_tempA_020)&&(T_tempA>50)&&(T_tempA<=300))
	{
        TA=T_tempA;//输出上次正常值
        UpCount++;
        return TA;
	}
	//      滤波时间5秒          报版本号后                   跳大值              差大于20%                         当前高度大于300米	  当前高度小于1700米
	if((UpCount<5)&&(T_tempA<TA)&&((TA-T_tempA)>=T_tempA_020)&&(T_tempA>300)&&(T_tempA<=1700))
	{
		TA=T_tempA;//输出上次正常值
	    UpCount++;
		return TA;
	}
	UpCount=0;//低跳高计数器清零
	//**************************************************************************
	//防止由高高度向低高度跳变的滤波程序
	//**************************************************************************
	//      滤波时间1秒          报版本号后                   跳小值              差大于20%                    	    当前高度小于50米
	if((DownCount<2)&&(T_tempA>TA)&&((T_tempA-TA)>=T_tempA_020)&&(T_tempA<=50))
	{
        DownCount++;
        return T_tempA;
	}
	//      滤波时间30秒          报版本号后                   跳小值              跳变大于2倍             当前高度大于50米	    当前高度小于300米
	if((DownCount<LEN)&&(T_tempA>TA)&&((T_tempA/TA)>=2)&&(T_tempA>50)&&(T_tempA<=800))
	{
	    DownCount++;
        if (DownCount==(LEN-100))
            TA10=TA;
        if (DownCount==LEN)
        {
            TA20=TA;
            if (abs(TA20-TA10)<20)       //计算1s高度变化率
            {
                DownCount=DownCount-12;
                LostCount++;
                if (LostCount==60)
                    LostCount--;
            }
        }
        return T_tempA;//原滤波计划
    }
	//             滤波时间5秒           报版本号后                跳小值              差大于20%                           当前高度大于50米	   当前高度小于300米
    if((DownCount<10)&&(T_tempA>TA)&&((T_tempA-TA)>=T_tempA_020)&&(T_tempA>50)&&(T_tempA<=600))
	{
        DownCount++;
        return T_tempA;
	}
	//      滤波时间5秒          报版本号后                   跳小值                   差大于20%                     当前高度大于300米	   当前高度小于1700米
	if((DownCount<10)&&(T_tempA>TA)&&((T_tempA-TA)>=T_tempA_020)&&(T_tempA>600)&&(T_tempA<=1700))
	{
        DownCount++;
        return T_tempA;
	}
	LostCount=0; //失锁计数器清零
	DownCount=0; //高跳低计数器清零
	return TA;
}
