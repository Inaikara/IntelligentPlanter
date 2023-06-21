//include part
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
	
//define port
sbit in1=P1^0;       //ץ�ֿ�����������
sbit in2=P1^1;       //ͬ��
sbit pulse_x=P1^2;   //x	dirver
sbit   dir_x=P1^3;   //ͬ��
sbit pulse_y=P1^4;   //y	dirver
sbit   dir_y=P1^5;   //ͬ��
sbit pulse_z=P1^6;   //z	dirver
sbit   dir_z=P1^7;   //ͬ��
sbit relay=P2^0;     //�̵������ƿ�
sbit dula=P2^6;      //����������
sbit wela=P2^7;      //����������


//define variables
extern uchar flag,a;
extern uchar code table[];
					 
//define function
void delayms(uint xms);//����ʱ
void delay(uint x);   //����ʱ
uchar matrixkeyscan();//��������
void pump();          //ˮ�ÿ���
void grap();          //ץ�ֿ���
void init();          //����ͨ�ų�ʼ��
void manipulator();   //ppp�ṹ�����ۿ���
										
										
										