#include<reg52.h>	
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit trig=P2^4;		               
sbit echo=P2^5;		                	                   
sbit dula=P2^6;                      
sbit wela=P2^7;                                       
       
unsigned int time;
unsigned long s;
bit eflag=0;

uchar code table_dula[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar code table_wela[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};

void delayms(unsigned int xms);         
void smgdisplay(uchar num,uchar loc);
void start();
void count();
void display_loc();
void run_ultrasonic();
void Init_uart();
void Init_timer();
void Init();

void smgdisplay(uchar num,uchar loc)
{
			dula=1;
			P0=table_dula[num];
			dula=0;
			P0=0xff;	
			wela=1;
			P0=table_wela[loc];
			wela=0;
}

void start()                            //???????
{   
    trig=1;			                    
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    trig=0;			             
}

void count()                            //????
{   time=TH0*256+TL0;				
    s=time*1.7/100;				    		
    TH0=0x00;						
    TL0=0x00;	
}

void run_ultrasonic()
{
		start();
    while(echo==0);
		TR0=1;			   
    while((echo==1)||(eflag==1));	
    TR0=0;
		eflag=0;
    count();			   
    delayms(1);
		SBUF=s;
    while(TI==0);           //???TI????1
    TI = 0;                 //TI??0,???????	
}


void Init_uart()                             //??
{   
    TMOD |= 0x20;                       //?????1  
    TH1 = 0xFD;                         //???9600    
    TL1 = 0xFD;
    TR1 = 1;                            //?????
    REN = 1;                            //??????
    SM0 = 0;                            //???????1
    SM1 = 1;                            
    ES = 1;                             //??????
}

void Init_timer()
{
		TMOD=0x01;			   
    TH0=0x00;			   
    TL0=0x00;			   
    EA=1;			       
    ET0=1;	
}

void Init()
{
	Init_timer();
	Init_uart();
}

void main()
{   
    Init();	
    while(1)
    {
			smgdisplay(s,5);
			run_ultrasonic();
    }
}
void delayms(unsigned int xms)     
{ 
    unsigned int i,j;
    for(i=xms;i>0;i--)
        for(j=110;j>0;j--);
}
void InterruptTimer0() interrupt 1			  
{
	eflag=1;
}

