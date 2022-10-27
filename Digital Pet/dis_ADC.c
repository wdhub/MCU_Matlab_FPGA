switch(ADC_RES)
		{
		case  1:
			//SendData(1);	
			bf=1;
			motor(1,i);
			motor(2,i);
			lcd_clear();                        // ����
 			DelayMS(5);	   			
			lcd_write_string(0,0,"   >     <   ");
			lcd_write_string(0,1,"      _      ");
			 
   			//delays(5000);
			break;
		case 2:
			//SendData(2);	
			lcd_clear();                        // ����
 			DelayMS(5);
			lcd_write_string(0,0,"   ^     ^   ");
			lcd_write_string(0,1,"      _      ");
			for(i=0;i<=50;i++) // ��ת����   
  			{  
   				motor(1,i);  
   				motor(2,i);
				delays(5000);
      		}
			for(i=50;i>0;i--) // ��ת����   
  			{  
   				motor(1,i);  
   				motor(2,i);  
   				delays(5000);  
  			}  
  			for(i=0;i<=50;i++) // ��ת����   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}  
  			for(i=50;i>0;i--) // ��ת����   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}
			break;
		case 3:
			//SendData(3);
			motor(1,a);
			motor(2,a);
			zd=1;
			break;
		default:
			//SendData(4);
			bf=0;
			zd=0;
			motor(1,a);
			motor(2,a);
			lcd_clear();                        // ����
 			DelayMS(5);				
			lcd_write_string(0,0,"    Welcome!    ");
 			lcd_write_string(0,1,"Long time no see");
		}




 for(i=0;i<=50;i++) // ��ת����   
  			{  
   				motor(1,i);  
   				motor(2,i);
				delays(5000);
      		}
			for(i=50;i>0;i--) // ��ת����   
  			{  
   				motor(1,i);  
   				motor(2,i);  
   				delays(5000);  
  			}  
  			for(i=0;i<=50;i++) // ��ת����   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}  
  			for(i=50;i>0;i--) // ��ת����   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}


#include	"stc15f2k60s2.h"	    // ��Ƭ��STC15F2K60S2ͷ�ļ�
#include	<intrins.h>			    // �����ͷ�ļ���,��ʹ��_nop_�⺯��
#include	"delay.h"		        // ��ʱ����ͷ�ļ�
#include 	"lcd1602.h"	
#include	<math.h>  	          // 1602��ʾ����������ͷ�ļ� 			
#define		uchar unsigned char 
#define 	uchar unsigned char  
#define 	uint unsigned int 

void 	Uart_Init	(void);
void 	SendData	(uchar dat);
void 	receiveData	();
void	ADC_init	(void);
void 	InitTimer0	(void);//��ʱ��0��ʼ��
void	Delay1ms	(void);
void	DelayMS		(int	t);
unsigned int Read_value(void);//��ֵ����
void	duobi		(void); 
sbit	en1=P1^0;  /* L298��Enable A */  
sbit 	en2=P1^1;  /* L298��Enable B */  
sbit 	s1=P2^3;  /* L298��Input 1 */  
sbit 	s2=P2^4;  /* L298��Input 2 */  
sbit 	s3=P2^5;  /* L298��Input 3 */  
sbit 	s4=P2^6;  /* L298��Input 4 */  
uchar 	t=0;   /* �жϼ����� */  
uchar 	m1=0;   /* ���1�ٶ�ֵ */  
uchar 	m2=0;   /* ���2�ٶ�ֵ */  
uchar 	tmp1,tmp2; /* �����ǰ�ٶ�ֵ */     
char	i;  
char	a;  
sbit	bf=P1^7;
sbit	zd=P1^6;
sbit 	tr		=	P1^2;	//trigger of detector
sbit 	ec		=	P1^3;	//echo of detector
uchar	distance;
 		
//========================================================================
// ����: void SYS_Init(void)
// ����: ��Ƭ���˿ڳ�ʼ��
// ˵����STC15W4K32S4ϵ�е�Ƭ�������ϵ����PWM��ص�IOΪ����״̬�����ֶ�����Ϊ��ͨ˫��IO
// PWM���IOΪ : P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//               P2.3/P2.7/P3.7/P4.2/P4.4/P4.5						 
//========================================================================
void SYS_Init()
{
	P0M0=0x20;
	P0M1=0x20;
	P1M0=0x3C;
	P1M1=0x3C;
	P2M0=0x00;
	P2M1=0x00;
	P3M0=0x00;
	P3M1=0x00;
	P4M0=0x00;
	P4M1=0x00;
	P5M0=0x00;
	P5M1=0x00;	
}

/* ������ƺ��� index-�����(1,2); speed-����ٶ�(-100��100) */  
void motor(uchar index, char speed)  
{  
if(speed>=-100 && speed<=100)  
{  
  if(index==1) /* ���1�Ĵ��� */  
  {  
   m1=abs(speed); /* ȡ�ٶȵľ���ֵ */  
   if(speed<0) /* �ٶ�ֵΪ����ת */  
   {  
    s1=0;  
    s2=1;  
   }  
   else /* ��Ϊ��������ת */  
   {  
    s1=1;  
    s2=0;  
   }  
  }  
  if(index==2) /* ���2�Ĵ��� */  
  {  
   m2=abs(speed); /* ���2���ٶȿ��� */  
   if(speed<0) /* ���2�ķ������ */  
   {  
    s3=0;  
    s4=1;  
   }  
   else  
   {  
    s3=1;  
    s4=0;  
   }  
  }  
}  
}  

void delays(uint j) /* ������ʱ���� */  
{  
for(j;j>0;j--);  
}  



void	ADC_init(){
	unsigned int i;
    P1ASF=0x10;                         //����P1.4Ϊģ�������빦��
    ADC_CONTR=0x84;                     //��A/Dת����Դ����������ͨ��
    for(i=1000;i>0;i--);                //�ʵ���ʱ
    CLK_DIV|=0x20;                      //ADRJ=1.����A/Dת������Ĵ洢��ʽ
    ADC_CONTR=0x8c;                     //����A/Dת��
	PADC=1;								// �����ȼ�
    EA=1;
    EADC=1;
}
void ADC_ISR() interrupt 5	using 1
{
	ADC_CONTR=0x84;                     //��ADC_FLAG��0��
    //P3=~P3;
	//internal of data
	//SendData(0);
	//SendData(0);                   
    ADC_CONTR=0x8c;                     //��������A/Dת��
}	
//���ڳ�ʼ������
void Uart_Init()
{
	SCON = 0x5a; 
	T2L = 0xE0;		//�趨��ʱ��ֵ
	T2H = 0xFE;		//�趨��ʱ��ֵ9600
	AUXR = 0x14; 
	AUXR |= 0x01;
	
	EA=1;
	ES=1;
	
}

void SendData(uchar dat)
{
	while (!TI); 
	TI = 0; 
	SBUF = dat;
}

void	receiveData(){
	if (RI){
	RI = 0; //clear
	P2 = SBUF; 
	}
}

void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x00;
    TL0 = 0x00;
    TR0 = 0;//�ȹرն�ʱ��0
}


/********************��ֵ����***********************/
unsigned int Read_value()
{
	float temp;
	unsigned int result;
	tr=1;//�������ŷ���11us�Ĵ����źţ�����10us��
	Delay1ms();
	_nop_();
	tr=0;
	while(!ec);//�ȹ������źŵĵ͵�ƽ
	TR0=1;//������ʱ��0
	while(ec);//�ȹ������źŸߵ�ƽ
	TR0=0;//�رն�ʱ��0
	ADC_init();
	SendData(0xff);
	SendData(0xff);
	SendData(TH0);
	distance=TH0;
	SendData(0xff);
	temp=TH0*256+TL0;
	temp/=1000.0;
	temp*=17.0;
	result=temp;
	if(temp-result>=0.5)
	{
		result+=1;
	}
	//SendData(result);
	return result;			
}

void duobi()
{	
	char	j=50;
	if(distance<03)
	{
		for(i=1;i<50;i++)  
		{	
			motor(1,j);  
   			s3=0;
			s4=0;
			DelayMS(10);  			
		}
		for(a=1;a<50;a++)  
		{
			motor(1,j);
			motor(2,j);
			DelayMS(10);
		}		  
 	}
	else
	{
		s1=0;
		s2=0;		
		s3=0;
		s4=0;
	}
	
}
	

void main()
{
	
	SYS_Init();                         // ϵͳ��ʼ��
	DelayMS(5);
	lcd_init();                         // ��ʾ������ʼ��
	DelayMS(5);
	Uart_Init();
    ADC_init();
	lcd_clear();                        // ����
 	DelayMS(5);
	lcd_write_string(0,0,"    Welcome!    ");
 	lcd_write_string(0,1,"Long time no see"); 

	//100us 
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xA4;		//���ö�ʱ��ֵ
	TH1 = 0xA4;		//���ö�ʱ����ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	EA=1; // ���ж�   
	ET1=1; // ��ʱ��0�����ж�  
	// 

	while(1)
	{
		//receiveData();// ��ѯ�����մ�����Ϣ
		unsigned int distance;
		tr=0;//����������������
		InitTimer0();//��ʼ����ʱ��0
		distance=Read_value();//��ֵ
		i = 50;  
		//test//////////////////
		SendData(0);
		SendData(0);
		SendData(ADC_RES); 					// ���͸�����
		SendData(0); 
		switch(ADC_RES)
		{
		case  1:
			//SendData(1);	
			for(a=1;a<50;a++)
			{
				bf=1;			
				motor(1,i);
				motor(2,i);
				lcd_clear();                        // ����
 				DelayMS(5);	   			
				lcd_write_string(0,0,"   >     <   ");
				lcd_write_string(0,1,"      _      ");
   				DelayMS(10);
			}	
				break;
			
		case 2:
			//SendData(2);	
			for(a=1;a<50;a++)
			{	
				lcd_clear();                        // ����
 				DelayMS(5);
				lcd_write_string(0,0,"   ^     ^   ");
				lcd_write_string(0,1,"      _      ");
				
				DelayMS(10);
			}			
				break;

		case 3:
			for(a=1;a<50;a++)
			{
				//SendData(3);
				duobi();
				zd=1;
				DelayMS(10);
			}
			break;
		default:
			//SendData(4);
			bf=0;
			zd=0;
			s1=0;
			s2=0;
			s3=0;
			s4=0;
			lcd_clear();                        // ����
 			DelayMS(5);				
			lcd_write_string(0,0,"    Welcome!    ");
 			lcd_write_string(0,1,"Long time no see");
		}
											
	} 
}

void timer1() interrupt 3 /* T0�жϷ������ */  
{  
if(t==0) /* 1��PWM������ɺ�Ż��������ֵ */  
{  
  tmp1=m1;  
  tmp2=m2;  
}  
if(t<tmp1) en1=1; else en1=0; /* �������1��PWM�ź� */  
if(t<tmp2) en2=1; else en2=0; /* �������2��PWM�ź� */  
t++;  
if(t>=100) t=0; /* 1��PWM�ź���100���жϲ��� */  
}  















		