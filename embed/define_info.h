//include part
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
	
//define port
sbit in1=P1^0;       //抓手控制脉冲输入
sbit in2=P1^1;       //同上
sbit pulse_x=P1^2;   //x	dirver
sbit   dir_x=P1^3;   //同上
sbit pulse_y=P1^4;   //y	dirver
sbit   dir_y=P1^5;   //同上
sbit pulse_z=P1^6;   //z	dirver
sbit   dir_z=P1^7;   //同上
sbit relay=P2^0;     //继电器控制口
sbit dula=P2^6;      //数码管锁存端
sbit wela=P2^7;      //数码管锁存端


//define variables
extern uchar flag,a;
extern uchar code table[];
					 
//define function
void delayms(uint xms);//长延时
void delay(uint x);   //短延时
uchar matrixkeyscan();//按键控制
void pump();          //水泵控制
void grap();          //抓手控制
void init();          //串口通信初始化
void manipulator();   //ppp结构操作臂控制
										
										
										