/*
 ============================================================================
 Name        : fiter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ǰ��������ʹ������Ϊ��λ��ʹ������Ϊ��λ������������ƽ����ɵ��������
           ʱ��ӳ���80s���߶�������800��
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
	FILE *fp1;  //�����ļ���ָ�룬���ڴ򿪶�ȡ���ļ�
	char text[1024];//����һ���ַ������飬���ڴ洢��ȡ���ַ�
	fp1 = fopen("test.txt","r");//ֻ����ʽ���ļ�a.txt
	int i;
	T_tempA=1;
	i=0;
	while(fgets(text,1024,fp1)!=NULL)//���ж�ȡfp1��ָ���ļ��е����ݵ�text��
	{
	    T_temp=atof(text)+1;
		T_temp=fiter(T_temp);
		T_tempA=T_temp;
		sprintf(text,"%d",T_temp);
		puts(text);//�������Ļ
		i=i+1;
	}
	fclose(fp1);//�ر��ļ�a.txt���д򿪾�Ҫ�йر�
	return EXIT_SUCCESS;
}

unsigned int fiter(unsigned int TA)
{
	 unsigned int T_tempA_020;       //��ǰ�߶�20%
     static unsigned int UpCount,DownCount;
     static unsigned int TA10,TA20;
     static unsigned int LostCount;
	 T_tempA_020=T_tempA*0.2;
     if (TA==0)
    	 TA=1;
	//**************************************************************************
	//��ֹ�ɵ͸߶���߸߶�������˲�����
	//**************************************************************************
	//      �˲�ʱ��5��          ���汾�ź�                   ����ֵ            �������10��              ��ǰ�߶�С��10��
	if((UpCount<5)&&(T_tempA<TA)&&((TA/T_tempA)>=10)&&(T_tempA<=10))
	{
        TA=T_tempA;//����ϴ�����ֵ
        UpCount++;
        return TA;
	}
	//      �˲�ʱ��1��          ���汾�ź�                   ����ֵ              �����20%                       ��ǰ�߶ȴ���10��	  ��ǰ�߶�С��50��
	if((UpCount<2)&&(T_tempA<TA)&&((TA-T_tempA)>=T_tempA_020)&&(T_tempA>10)&&(T_tempA<=50))
	{
        TA=T_tempA;//����ϴ�����ֵ
        UpCount++;
        return TA;
	}
	//      �˲�ʱ��3��          ���汾�ź�                   ����ֵ              �����20%                        ��ǰ�߶ȴ���50��	  ��ǰ�߶�С��300��
	if((UpCount<5)&&(T_tempA<TA)&&((TA-T_tempA)>=T_tempA_020)&&(T_tempA>50)&&(T_tempA<=300))
	{
        TA=T_tempA;//����ϴ�����ֵ
        UpCount++;
        return TA;
	}
	//      �˲�ʱ��5��          ���汾�ź�                   ����ֵ              �����20%                         ��ǰ�߶ȴ���300��	  ��ǰ�߶�С��1700��
	if((UpCount<5)&&(T_tempA<TA)&&((TA-T_tempA)>=T_tempA_020)&&(T_tempA>300)&&(T_tempA<=1700))
	{
		TA=T_tempA;//����ϴ�����ֵ
	    UpCount++;
		return TA;
	}
	UpCount=0;//�����߼���������
	//**************************************************************************
	//��ֹ�ɸ߸߶���͸߶�������˲�����
	//**************************************************************************
	//      �˲�ʱ��1��          ���汾�ź�                   ��Сֵ              �����20%                    	    ��ǰ�߶�С��50��
	if((DownCount<2)&&(T_tempA>TA)&&((T_tempA-TA)>=T_tempA_020)&&(T_tempA<=50))
	{
        DownCount++;
        return T_tempA;
	}
	//      �˲�ʱ��30��          ���汾�ź�                   ��Сֵ              �������2��             ��ǰ�߶ȴ���50��	    ��ǰ�߶�С��300��
	if((DownCount<LEN)&&(T_tempA>TA)&&((T_tempA/TA)>=2)&&(T_tempA>50)&&(T_tempA<=800))
	{
	    DownCount++;
        if (DownCount==(LEN-100))
            TA10=TA;
        if (DownCount==LEN)
        {
            TA20=TA;
            if (abs(TA20-TA10)<20)       //����1s�߶ȱ仯��
            {
                DownCount=DownCount-12;
                LostCount++;
                if (LostCount==60)
                    LostCount--;
            }
        }
        return T_tempA;//ԭ�˲��ƻ�
    }
	//             �˲�ʱ��5��           ���汾�ź�                ��Сֵ              �����20%                           ��ǰ�߶ȴ���50��	   ��ǰ�߶�С��300��
    if((DownCount<10)&&(T_tempA>TA)&&((T_tempA-TA)>=T_tempA_020)&&(T_tempA>50)&&(T_tempA<=600))
	{
        DownCount++;
        return T_tempA;
	}
	//      �˲�ʱ��5��          ���汾�ź�                   ��Сֵ                   �����20%                     ��ǰ�߶ȴ���300��	   ��ǰ�߶�С��1700��
	if((DownCount<10)&&(T_tempA>TA)&&((T_tempA-TA)>=T_tempA_020)&&(T_tempA>600)&&(T_tempA<=1700))
	{
        DownCount++;
        return T_tempA;
	}
	LostCount=0; //ʧ������������
	DownCount=0; //�����ͼ���������
	return TA;
}
