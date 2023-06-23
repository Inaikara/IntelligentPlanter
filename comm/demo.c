#include <reg52.h>
#define uchar unsigned char 
#define uint unsigned int 
uchar temp;
sbit pulse_x=P1^2; 
sbit dir_x=P1^3; 
 
void delayms(uint x)
{
	uint i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}

void delay(uint x)
{
	uint i,j;
	for(i=x;i>0;i--)
		for(j=10;j>0;j--);
}

//发送一个字符
void sendChar(uchar a)
{
	SBUF = a;
	while(TI==0);
	TI=0;
	
}
 
//发送字符串
void sendString(uchar *s)
{
	while(*s!='\0')
	{
		sendChar(*s);
		s++;
	}
		
}
 
//初始化ESP8266模块
void initEsp()
{
	TMOD=0x20;		//定时器1工作在方式2
	TH1 = 0xfd;		//波特率9600
	TL1 = 0xfd;
	SM0=0;				//串口工作在方式1
	SM1=1;
	EA = 1;				//开总中断
	REN = 1;			//使能串口
	TR1 = 1;			//定时器1开始计时
	delayms(2000);      //延时给esp8266处理时间
	sendString("AT\r\n");		//模式
	delayms(2000);      //延时给esp8266处理时间
	sendString("AT+RST\r\n");		//模式
	delayms(2000);
	sendString("AT+CWSAP=\"tesest\",\"123456789\",11,0\r\n");		//模式
	delayms(2000);
	sendString("AT+CIPMUX=1\r\n");		//允许多连接
	delayms(2000);	
	sendString("AT+CIPSERVER=1\r\n");	//建立TCP Server
	delayms(2000);
   	sendString("AT+CIPSTO=0\r\n");  
	ES = 1;				//开串口中断
}
 
uchar receiveTable[10];
uint i;

void move_x(uchar dir)
{
	dir_x = dir; 
 	delay(1);
	pulse_x=0;
 	delay(1);
 	pulse_x=1;
 	delay(1); 
}

void main()
{
	i=0;
	initEsp();
	
	while(1);
}
 
void uart() interrupt 4
{
	
    if(RI == 1)//接受完来自wifi模块的数据后开关led
     {
        RI = 0;//清除串口接收标志位
		move_x(0);
     }
}
