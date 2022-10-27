#include	"stc15f2k60s2.h"	    // 单片机STC15F2K60S2头文件
#include	<intrins.h>			    // 加入此头文件后,可使用_nop_库函数
#include	"delay.h"		        // 延时函数头文件
#include 	"lcd1602.h"	
#include	<math.h>  	          // 1602显示屏驱动程序头文件
#include 	<stdlib.h>		
#define		uchar unsigned char 
#define 	uchar unsigned char  
#define 	uint unsigned int 

void 	Uart_Init	(void);
void 	SendData	(uchar dat);
void 	receiveData	(void);
void	ADC_init	(void);
void 	InitTimer0	(void);//定时器0初始化
void	Delay1ms	(void);
void	DelayMS		(int	t);
uint	Read_value(void);//读值函数
void	timer1_initial();
void	duobi		(void);
void 	motor_zc	(void);
void 	motor_tz	(void);
void	motor_zz	(void);
void	motor_yz	(void);
sbit	en1=P1^0;  /* L298的Enable A */  
sbit 	en2=P1^1;  /* L298的Enable B */  
sbit 	s1=P2^3;  /* L298的Input 1 */  
sbit 	s2=P2^4;  /* L298的Input 2 */  
sbit 	s3=P2^5;  /* L298的Input 3 */  
sbit 	s4=P2^6;  /* L298的Input 4 */
sfr		ADC_LOW2=0xBE;
	  
uchar 	t=0;   /* 中断计数器 */  
uchar 	m1=0;   /* 电机1速度值 */  
uchar 	m2=0;   /* 电机2速度值 */  
uchar 	tmp1,tmp2; /* 电机当前速度值 */     
char	i;  
char	a;  
sbit	bf=P1^7;
sbit	zd=P1^6;
sbit 	tr		=	P1^2;	//trigger of detector
sbit 	ec		=	P1^3;	//echo of detector
uint	distance;
uint	r; 
int		adc_temp;
uchar	age;
		
//========================================================================
// 函数: void SYS_Init(void)
// 描述: 单片机端口初始化
// 说明：STC15W4K32S4系列单片机，在上电后与PWM相关的IO为高阻状态，需手动设置为普通双向IO
// PWM相关IO为 : P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
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

/* 电机控制函数 index-电机号(1,2); speed-电机速度(-100—100) */  
void motor(uchar index, char speed)  
{  
	if(speed>=-100 && speed<=100)  
	{  
  		if(index==1) /* 电机1的处理 */  
  		{  
  			m1=abs(speed); /* 取速度的绝对值 */  
   			if(speed<0) /* 速度值为负则反转 */  
   			{  
    			s1=0;  
    			s2=1;  
   			}  
   			else /* 不为负数则正转 */  
   			{  
    			s1=1;  
    			s2=0;  
   			}  
  		}  
  		if(index==2) /* 电机2的处理 */  
  		{	  
   			m2=abs(speed); /* 电机2的速度控制 */  
   			if(speed<0) /* 电机2的方向控制 */  
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

void delays(uint j) /* 简易延时函数 */  
{  
for(j;j>0;j--);  
}  

void	timer1_initial()
{	
	//100us 
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xA4;		//设置定时初值
	TH1 = 0xA4;		//设置定时重载值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA=1; // 开中断   
	ET1=1; // 定时器1允许中断  
	//
}

//小车逃跑
void	motor_zc()
{
	char s=50;
	motor(1,s);
	motor(2,s);
}

//小车停止
void	motor_tz()
{
	s1=0;
	s2=0;		
	s3=0;
	s4=0;
}

//小车左转
void	motor_zz()
{
	char s=50;
	motor(1,s);  
   	s3=0;
	s4=0;
}

//小车右转
void	motor_yz()
{
	char s=50;
	s1=0;
	s2=0;
	motor(2,s);  
}


void	lcd_tp()
{
	lcd_clear();                        // 清屏
 	DelayMS(5);	   			
	lcd_write_string(0,0,"   >     <   ");
	lcd_write_string(0,1,"      _      ");
}

void	lcd_kx()
{	
	lcd_clear();                        // 清屏
 	DelayMS(5);
	lcd_write_string(0,0,"   ^     ^   ");
	lcd_write_string(0,1,"      _      ");
}

void	lcd_cs()
{
	lcd_clear();                        // 清屏
 	DelayMS(5);				
	lcd_write_string(0,0,"    Welcome!    ");
 	lcd_write_string(0,1,"Long time no see");
}

void	ADC_init()
{
	unsigned int i;
    P1ASF=0x20;                         //设置P1.4为模拟量输入功能
    ADC_CONTR=0x84;                     //打开A/D转换电源，设置输入通道
    for(i=1000;i>0;i--);                //适当延时
    CLK_DIV|=0x20;                      //ADRJ=1.设置A/D转换结果的存储格式
    ADC_CONTR=0x8c;                     //启动A/D转换
	PADC=1;								// 高优先级
    EA=1;
    EADC=1;
}
void ADC_ISR() interrupt 5	using 1
{
	ADC_CONTR=0x84;                     //将ADC_FLAG清0；
    //P3=~P3;
	//internal of data
	//SendData(0);
	//SendData(0);                   
    ADC_CONTR=0x8c;                     //重新启动A/D转换
}	

//串口初始化函数
void Uart_Init()
{
	SCON = 0x5a; 
	T2L = 0xE0;		//设定定时初值
	T2H = 0xFE;		//设定定时初值9600
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

void	receiveData()
{
	if (RI){
	RI = 0; //clear
	age=SBUF;
	//SendData(age); 
	}
}

void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x00;
    TL0 = 0x00;
    TR0 = 0;//先关闭定时器0
}

void	freeze()
{
 	bf=0;
	zd=0;
	motor_tz();
}

void runfw()
{
	for(a=1;a<50;a++)
	{
		bf=1;			
		motor_zc();
		lcd_tp();
   		DelayMS(10);
	}
	freeze();
}
	

/********************读值函数***********************/
unsigned int Read_value()
{
	float temp;
	unsigned int result;
	tr=1;//触发引脚发出11us的触发信号（至少10us）
	Delay1ms();
	_nop_();
	tr=0;
	while(!ec);//度过回响信号的低电平
	TR0=1;//开启定时器0
	while(ec);//度过回响信号高电平
	TR0=0;//关闭定时器0
	ADC_init();
	//SendData(0xff);
	//SendData(0xff);
	//SendData(TH0);
	distance=TH0;
	//SendData(0xff);
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

void	rbark()
{
	r=rand()%10;
	if(r==0)
	{
		for(i=1;i<20;i++)  
		{	
			bf=1;
			
			//SendData(1);
			DelayMS(50);  			
		}

		//SendData(r);
	}
	else
		bf=0;
}
void duobi()
{	//SendData(distance); 
	if(distance<20)
	{
		for(i=1;i<50;i++)  
		{	
			motor_zz();
			DelayMS(10);  			
		}
		for(a=1;a<50;a++)  
		{
			motor_zc();
			DelayMS(10);
		}		  
 	}
	else
		motor_tz();
	
}

void	motor_sj()
{
	uint	sj;
	sj=rand()%10;
	
	if(sj==0)
	{
		for(i=1;i<50;i++)  
		{	
			zd=1;
			
			//SendData(1);
			DelayMS(1);  			
		}		
	}
	else
		freeze();
		
}		
void	zdfw()
{
	for(i=1;i<50;i++)  
		{	
			zd=1;
			
			//SendData(1);
			DelayMS(5);  			
		}
	zd=0;
}

void	main_initial()
{
	SYS_Init();                         // 系统初始化
	DelayMS(5);
	lcd_init();                         // 显示驱动初始化
	DelayMS(5);
	Uart_Init();
    ADC_init();
	lcd_cs;
	timer1_initial();
}

void main()
{
	main_initial();
	while(1)
	{
		receiveData();// 查询法接收串口信息
		//unsigned int distance;
		tr=0;//出发引脚首先拉低
		InitTimer0();//初始化定时器0
		distance=Read_value();//读值
		//SendData(distance); 
		//test
		//adc_temp=ADC_RES<<2;
		//adc_temp=adc_temp+ADC_LOW2;
		//SendData(0);
		//SendData(0);
		//SendData(ADC_RES); 					// 发送给串口
		//SendData(0);
				 
		switch(ADC_RES)
		{
		case  1:
			SendData(1);
			if(age==2)
			{
				runfw();
			}
			if(age==3)
			{
				lcd_tp();
				zdfw();
			}	
			break;			
		case 2:
			if(age==1)
			{
				duobi();
				rbark();		
				lcd_tp();
			}
			if(age==2)
			{
				motor_sj();
				lcd_kx();
			}
			if(age==3)
			{
				lcd_kx();
			}
			if(age==4)
			{	
				lcd_clear();                        // 清屏
 				DelayMS(5);
			}					
			break;
		default:
			//SendData(4);
			freeze();		
		}
											
	} 
}

void timer1() interrupt 3 /* T1中断服务程序 */  
{  
if(t==0) /* 1个PWM周期完成后才会接受新数值 */  
{  
  tmp1=m1;  
  tmp2=m2;  
}  
if(t<tmp1) en1=1; else en1=0; /* 产生电机1的PWM信号 */  
if(t<tmp2) en2=1; else en2=0; /* 产生电机2的PWM信号 */  
t++;  
if(t>=100) t=0; /* 1个PWM信号由100次中断产生 */  
}  













