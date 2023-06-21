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

//����һ���ַ�
void sendChar(uchar a)
{
	SBUF = a;
	while(TI==0);
	TI=0;
	
}
 
//�����ַ���
void sendString(uchar *s)
{
	while(*s!='\0')
	{
		sendChar(*s);
		s++;
	}
		
}
 
//��ʼ��ESP8266ģ��
void initEsp()
{
	TMOD=0x20;		//��ʱ��1�����ڷ�ʽ2
	TH1 = 0xfd;		//������9600
	TL1 = 0xfd;
	SM0=0;				//���ڹ����ڷ�ʽ1
	SM1=1;
	EA = 1;				//�����ж�
	REN = 1;			//ʹ�ܴ���
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
	delayms(2000);      //��ʱ��esp8266����ʱ��
	sendString("AT\r\n");		//ģʽ
	delayms(2000);      //��ʱ��esp8266����ʱ��
	sendString("AT+RST\r\n");		//ģʽ
	delayms(2000);
	sendString("AT+CWSAP=\"tesest\",\"123456789\",11,0\r\n");		//ģʽ
	delayms(2000);
	sendString("AT+CIPMUX=1\r\n");		//���������
	delayms(2000);	
	sendString("AT+CIPSERVER=1\r\n");	//����TCP Server
	delayms(2000);
   	sendString("AT+CIPSTO=0\r\n");  
	ES = 1;				//�������ж�
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
	
    if(RI == 1)//����������wifiģ������ݺ󿪹�led
     {
        RI = 0;//������ڽ��ձ�־λ
		move_x(0);
     }
}
