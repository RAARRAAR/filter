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
unsigned int T_Array[16],T_tempA,T_temp;

unsigned int fiter(unsigned int);
int fiter2(unsigned int TA,unsigned int TA_C,int *TA_T);
int main(void) {
	FILE *fp1;  //�����ļ���ָ�룬���ڴ򿪶�ȡ���ļ�
	char text[1024];//����һ���ַ������飬���ڴ洢��ȡ���ַ�
	fp1 = fopen("test.txt","r");//ֻ����ʽ���ļ�a.txt
	T_tempA=1;
	while(fgets(text,1024,fp1)!=NULL)//���ж�ȡfp1��ָ���ļ��е����ݵ�text��
	{
		T_temp=atof(text)+1;
		T_temp=fiter(T_temp);
		T_tempA=T_temp;
		sprintf(text,"%d",T_temp);
		puts(text);//�������Ļ
	}
	fclose(fp1);//�ر��ļ�a.txt���д򿪾�Ҫ�йر�
	return EXIT_SUCCESS;
}

unsigned int fiter(unsigned int TA)
{
	 unsigned int T_tempA_020;       //��ǰ�߶�20%
	 int T_Delt;
     static unsigned int UpCount,DownCount;
     static unsigned int TA_C;
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
        if (DownCount==0)
        {
            TA_C=0;
        }
        else
            TA_C++;
        DownCount++;
        switch (fiter2(TA,TA_C,&T_Delt))
        {
            case 0:
            {
                return T_tempA;//ԭ�˲��ƻ�
            }
            case 1:
            {
                return T_tempA+T_Delt;//ԭ�˲��ƻ�+�仯��
            }
            case 2:
            {
                DownCount=LEN;//�����˲�����
                return TA;
            }
            default:
            {
                return T_tempA;//ԭ�˲��ƻ�
            }
        }
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
	DownCount=0; //�����ͼ���������
	return TA;
}
int fiter2(unsigned int TA,unsigned int TA_C,int *TA_T)
{
    static unsigned int TA_J,UP_C,DOWN_C,TA_Max,TA_Min,MAX_C,MIN_C,Count;
    static int TA_Temp;
    if (TA_C<=1)
    {
        TA_J=TA;
        TA_Min=TA;
        TA_Max=TA;
        Count=0;
        MIN_C=0;
        MAX_C=0;
        *TA_T=0;
        return 0;//ʹ����һ�β��ֵ
    }
    if(TA>TA_Max)
    {
        TA_Max=TA;
        MAX_C=Count;
    }
    if(TA<TA_Min)
    {
        TA_Min=TA;
        MIN_C=Count;
    }
    Count++;
    if (Count%10==1)
    {
        UP_C=0;
        DOWN_C=0;
        MIN_C=0;
        MAX_C=0;
        TA_Min=TA;
        TA_Max=TA;
    }
    if (TA>TA_J)
        UP_C++;
    if (TA<TA_J)
        DOWN_C++;
    if ((abs(MAX_C-MIN_C)>1))//��������
    {
        if( (((TA_Max-TA_Min)/abs(MAX_C-MIN_C))>10)&&(abs(UP_C-DOWN_C)>8))
        {
           *TA_T=500;
           return 2;//�ָ����ֵ
       }
    }
    TA_Temp=TA-TA_J;
    TA_J=TA;
    *TA_T=TA_Temp;
    return 1;    //ʹ�ò�ֵ
}
