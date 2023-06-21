#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int

sbit in1=P1^0;       
sbit in2=P1^1;       
sbit pulse_x=P1^2;   
sbit dir_x=P1^3;   
sbit pulse_y=P1^4;   
sbit dir_y=P1^5;   
sbit pulse_z=P1^6;   
sbit dir_z=P1^7;   
sbit relay=P2^0;
sbit trig=P2^4;		               
sbit echo=P2^5;
sbit dula=P2^6;      
sbit wela=P2^7;      
sbit bee=P2^3;
		
bit  eflag=0;
uint temp1=0;
unsigned char rline=0xee;  
unsigned int time;
unsigned long s;	 
uchar flag=0;
uchar a;
uchar code table_dula[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar code table_wela[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
uchar Recive_table[15];
uint i;

void delay_us(uchar us);
void delayms(uint xms);
void delay(uint x);
uint bitnum(uint num);   
uchar matrixkeyscan();
void pump(uchar sta);          
void grab(bit dir);          
void manipulator(uchar dir);   
void smgdisplay(uchar num,uchar loc);
void start();
void count();
void run_ultrasonic();
void Init_timer();
// void Init_uart();
void Usart_Init();
void SENT_At(uchar *At_Comd);
void WIFI_Init();
// void Init_esp();
void Init();
void move_x(uchar dir);
void move_y(uchar dir);
void move_z(uchar dir);
void chuanxing();
void sendChar(uchar a);
void sendString(uchar *s);


void main()
{
  uchar value;
  Init();
  run_ultrasonic();
  while(1)
  {
    if(flag==0)
    {
      value=matrixkeyscan();
  	  manipulator(value);
    }
	    chuanxing();
  }
}

void delay_us(uchar us)
{
	while(us--);
}
 

void delayms(uint xms)
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=110;j>0;j--);
}

void delay(uint x)
{
  uint i,j;
  for(i=x;i>0;i--)
    for(j=10;j>0;j--);
}
uint bitnum(uint num)
{
  switch(num)
  {
    case 14: return 1;
    break;
    case 13: return 2;
    break;
    case 11: return 3;
    break;
    case 7: return 4;
    break;
  }
  return 0;
}

uchar matrixkeyscan()            //鐭╅樀閿洏鎵弿鍑芥暟
{
  unsigned char temp=0;
  unsigned char key=0;   
  unsigned int rnum;
  unsigned int cnum;  
  P3=0xf0+(rline&0x0f);       //灏嗘煇琛岀嚎缃綆鐢靛钩
  temp=P3;
  temp=temp&0xf0;
  if(temp!=0xf0)
  {
    //delay(10);                //鍘绘姈鍔?
    temp=P3;
    temp=temp&0xf0;
    
    if(temp!=0xf0)
    {
      cnum=bitnum(temp/16);   //寰楀埌鍒楃嚎鏁板€?
      temp=P3;
      temp=temp&0x0f;
      rnum=bitnum(temp);      //寰楀埌琛岀嚎鏁板€?
      key=(rnum-1)*4+cnum-1;  //璁＄畻寰楀埌key鍊?
      temp=P3;
      return key;
    }
  } 
  rline=_crol_(rline,1); 
  return key;
}

void move_x(uchar dir)
{
  dir_x = dir;        
  delay(1);
  pulse_x=0;
  delay(1);
  pulse_x=1;
  delay(1); 
}
void move_y(uchar dir)
{
  dir_y=dir;
  delay(1);
  pulse_y= 0;
  delay(1);
  pulse_y= 1;
  delay(1);
}

void move_z(uchar dir)
{
  dir_z=dir;
  delay(1);
  pulse_z=0;
  delay(1);
  pulse_z=1;
  delay(1); 
}

void grab(bit dir)  //0寮€锛?闂?
{
	in1=dir,in2=~dir;
}

void pump(uchar sta)//0寮€锛?鍏?
{
  relay=sta;		
}

void manipulator(uchar dir)
{
  switch(dir)
  {
    case 0 :
      in1=0,in2=0;
      relay=1;
      break;
    case 8 :
      move_z(1);
      break;
    case 9 :
      move_x(1);
      break;
    case 10 :
      move_z(0);
      break;
    case 11 :
      grab(0);
      break;
    case 12 :
      move_y(1);
      break;
    case 13 :
      move_x(0);
      break;
    case 14 :
      move_y(0);
      break;
    case 15 :
      grab(1);
      break;
  }
}

void chuanxing()
{
  if(flag==1)
  {
    flag=0;
    switch(a&0x0f)  //鍙栦綆4浣?
	  {
	    case 0:
        //涓嬫斁 	 
		    while((s>7)&&(RI==0))
	      {
				  if(temp1>=200)
				  {
				    run_ultrasonic();
				    temp1=0;
			    }
		      temp1=temp1+1;
	        move_z(0);
        }
        //鎵ц
        if(s<=7)
        {
          switch(a&0xf0)//鍙栭珮4浣?
          {
            case 16 :
              grab(1);
              delayms(5000);
              in1=0,in2=0;
              break;		
            case 32 : 
              pump(0);
              delayms(50);
              pump(1);
              break;
          }
          temp1=0;
          //涓婂崌	
          while(s<15)
          {
            if(temp1>=5000)
            {
              run_ultrasonic();
              temp1=0;
            }
            temp1=temp1+1;
            move_z(1);
          }
          if(s>=15)
          {
              grab(0);
              delayms(5000);
              in1=0,in2=0;
              ES=0;				
          }	 			
        }
			break;							
	    case 1:                    //0b0001:
        while(!flag)
        {
          move_y(1);      
        }
	      break;
	    case 2:                    //00000010B:
        while(!flag)
        {
          move_y(0);       
        }
	      break;
      case 4:                    //00000100B:
        while(!flag)
        {
          move_x(1);      
        }
	      break;
	    case 5:                    //00000101B:
        while(!flag)
        {
          move_y(1);
          move_x(1);
        }
	      break;
	    case 6:                      //00000110B:
	      while(!flag)
        {
          move_y(0);
          move_x(1);
        }
 	      break;
	    case 8:                       //00001000B:
	      while(!flag)
        {
          move_x(0);
        }
	      break;
	    case 11:                        //00001001B:
	      while(!flag)
        {
          move_y(1);
          move_x(0);
        }
	      break;
	    case 12:                       //00001010B:
	      while(!flag)
        {
          move_y(0);
          move_x(0);
        }
	      break;
      case 14:                       //00001111B:		
        while(!flag);
        break;
    }				 
  }
}

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
{   
  time=TH0*256+TL0;				
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
  smgdisplay(s,0);
}



//鍙戦€佷竴涓瓧绗?
void sendChar(uchar a)
{
	SBUF = a;
	while(TI==0);
	TI=0;
	
}
 
//鍙戦€佸瓧绗︿覆
void sendString(uchar *s)
{
	while(*s!='\0')
	{
		sendChar(*s);
		s++;
	}
		
}


void Init_timer()
{
  TMOD=0x01;			   
  TH0=0x00;			   
  TL0=0x00;			   		       
  ET0=1;	
}



void Usart_Init()
{
	SCON = 0x50;
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = TH1;
	PCON = 0;
	TR1 = 1;

}

void SENT_At(uchar *At_Comd)
{
	ES = 0;
	while(*At_Comd!='\0')
	{
		SBUF = *At_Comd;
		while(!TI);
		TI = 0;
		delay_us(5);
		At_Comd++;
	}
}

void WIFI_Init()
{
	SENT_At("AT+CIPMUX=1\r\n");//多连接模式
	delayms(10);
    bee=0;
	//发送成功后亮灯
	SENT_At("AT+CIPSERVER=1,8080\r\n");//设置端口号
	smgdisplay(0,1);//设置成功后亮灯
	delayms(10);
    bee=1;
	smgdisplay(0,1);//设置成功后亮灯
	ES = 1;
}
 


void Init()
{
  Init_timer();
  Usart_Init();
  WIFI_Init();
  //Init_esp();
  EA = 1;		
}

void InterruptTimer0() interrupt 1			  
{
	eflag=1;
}


void ser() interrupt 4 
{

	if(RI==1)
	{
		RI=0;
		Recive_table[i] = SBUF; 
		if(Recive_table[0]=='+')
		  i++;
		else
			i = 0;
		if(i>=10)
		{
			if((Recive_table[0]=='+')&&(Recive_table[1]=='I')&&(Recive_table[2]=='P')&&(Recive_table[3]=='D'))
			{
				a=Recive_table[9];
        smgdisplay(a,1);
        flag=1;       
			}
			i = 0;
		}		
	}
	else
   TI = 0;

}
