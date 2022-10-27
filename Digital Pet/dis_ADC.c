switch(ADC_RES)
		{
		case  1:
			//SendData(1);	
			bf=1;
			motor(1,i);
			motor(2,i);
			lcd_clear();                        // 清屏
 			DelayMS(5);	   			
			lcd_write_string(0,0,"   >     <   ");
			lcd_write_string(0,1,"      _      ");
			 
   			//delays(5000);
			break;
		case 2:
			//SendData(2);	
			lcd_clear();                        // 清屏
 			DelayMS(5);
			lcd_write_string(0,0,"   ^     ^   ");
			lcd_write_string(0,1,"      _      ");
			for(i=0;i<=50;i++) // 正转加速   
  			{  
   				motor(1,i);  
   				motor(2,i);
				delays(5000);
      		}
			for(i=50;i>0;i--) // 正转减速   
  			{  
   				motor(1,i);  
   				motor(2,i);  
   				delays(5000);  
  			}  
  			for(i=0;i<=50;i++) // 反转加速   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}  
  			for(i=50;i>0;i--) // 反转减速   
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
			lcd_clear();                        // 清屏
 			DelayMS(5);				
			lcd_write_string(0,0,"    Welcome!    ");
 			lcd_write_string(0,1,"Long time no see");
		}




 for(i=0;i<=50;i++) // 正转加速   
  			{  
   				motor(1,i);  
   				motor(2,i);
				delays(5000);
      		}
			for(i=50;i>0;i--) // 正转减速   
  			{  
   				motor(1,i);  
   				motor(2,i);  
   				delays(5000);  
  			}  
  			for(i=0;i<=50;i++) // 反转加速   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}  
  			for(i=50;i>0;i--) // 反转减速   
  			{  
   				motor(1,-i);  
   				motor(2,-i);  
   				delays(5000);  
  			}


#include	"stc15f2k60s2.h"	    // 单片机STC15F2K60S2头文件
#include	<intrins.h>			    // 加入此头文件后,可使用_nop_库函数
#include	"delay.h"		        // 延时函数头文件
#include 	"lcd1602.h"	
#include	<math.h>  	          // 1602显示屏驱动程序头文件 			
#define		uchar unsigned char 
#define 	uchar unsigned char  
#define 	uint unsigned int 

void 	Uart_Init	(void);
void 	SendData	(uchar dat);
void 	receiveData	();
void	ADC_init	(void);
void 	InitTimer0	(void);//定时器0初始化
void	Delay1ms	(void);
void	DelayMS		(int	t);
unsigned int Read_value(void);//读值函数
void	duobi		(void); 
sbit	en1=P1^0;  /* L298的Enable A */  
sbit 	en2=P1^1;  /* L298的Enable B */  
sbit 	s1=P2^3;  /* L298的Input 1 */  
sbit 	s2=P2^4;  /* L298的Input 2 */  
sbit 	s3=P2^5;  /* L298的Input 3 */  
sbit 	s4=P2^6;  /* L298的Input 4 */  
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
uchar	distance;
 		
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



void	ADC_init(){
	unsigned int i;
    P1ASF=0x10;                         //设置P1.4为模拟量输入功能
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
    TR0 = 0;//先关闭定时器0
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
	
	SYS_Init();                         // 系统初始化
	DelayMS(5);
	lcd_init();                         // 显示驱动初始化
	DelayMS(5);
	Uart_Init();
    ADC_init();
	lcd_clear();                        // 清屏
 	DelayMS(5);
	lcd_write_string(0,0,"    Welcome!    ");
 	lcd_write_string(0,1,"Long time no see"); 

	//100us 
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xA4;		//设置定时初值
	TH1 = 0xA4;		//设置定时重载值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA=1; // 开中断   
	ET1=1; // 定时器0允许中断  
	// 

	while(1)
	{
		//receiveData();// 查询法接收串口信息
		unsigned int distance;
		tr=0;//出发引脚首先拉低
		InitTimer0();//初始化定时器0
		distance=Read_value();//读值
		i = 50;  
		//test//////////////////
		SendData(0);
		SendData(0);
		SendData(ADC_RES); 					// 发送给串口
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
				lcd_clear();                        // 清屏
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
				lcd_clear();                        // 清屏
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
			lcd_clear();                        // 清屏
 			DelayMS(5);				
			lcd_write_string(0,0,"    Welcome!    ");
 			lcd_write_string(0,1,"Long time no see");
		}
											
	} 
}

void timer1() interrupt 3 /* T0中断服务程序 */  
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















		