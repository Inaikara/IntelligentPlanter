#include "define_info.h"
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
void display(uchar num)
{
  P0=table[num];
  dula=1;
  dula=0;
}
uchar matrixkeyscan()
{
  uchar temp,key;  
  P3=0xfe;
  temp=P3;
  temp=temp&0xf0;
  if(temp!=0xf0)
  {
    delayms(10);
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      temp=P3;
      switch(temp)
      {
      case 0xee:
      //key=0;
      break;

      case 0xde:
      key=1;
      break;

      case 0xbe:
      //key=2;
      break;
 
      case 0x7e:
      //key=3;
	  key=7;
      break;
      }
      while(temp!=0xf0)
      {
       temp=P3;
       temp=temp&0xf0;
      }
      display(key);
    }
  }
  P3=0xfd;
  temp=P3;
  temp=temp&0xf0;
  if(temp!=0xf0)
  {
    delayms(10);
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      temp=P3;
      switch(temp)
      {
      case 0xed:
      //key=4;
	  key=3;
      break;

      case 0xdd:
      //key=5;
	  key=2;
      break;

      case 0xbd:
      //key=6;
	  key=4;
      break;

      case 0x7d:
      //key=7;
	  key=8;
      break;
      }
      while(temp!=0xf0)
      {
        temp=P3;
        temp=temp&0xf0;
      }
      display(key);
    }
  }
  P3=0xfb;
  temp=P3;
  temp=temp&0xf0;
  if(temp!=0xf0)
  {
    delayms(10);
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      temp=P3;
      switch(temp)
      {
      case 0xeb:
      //key=8;
      break;

      case 0xdb:
      //key=9;
	  key=5;
      break;

      case 0xbb:
      //key=10;
      break;

      case 0x7b:
      //key=11;
	  key=9;
      break;
      }
      while(temp!=0xf0)
      {
        temp=P3;
        temp=temp&0xf0;
      }
      display(key);
    }
  }
  P3=0xf7;
  temp=P3;
  temp=temp&0xf0;
  if(temp!=0xf0)
  {
    delayms(10);
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      temp=P3;
      switch(temp)
      {
        case 0xe7:
        //key=12;
        break;

        case 0xd7:
        //key=13;
		key=6;
        break;

        case 0xb7:
        //key=14;
        break;

        case 0x77:
        //key=15;
		key=10;
        break;
      }
      while(temp!=0xf0)
      {
        temp=P3;
        temp=temp&0xf0;
      }
      display(key);
    }
  }
  return key;
}
void pump()
{
 if(matrixkeyscan()==10)
   {
    delayms(1);           
    if(matrixkeyscan()==10)              
     {
      relay=0;
 	 }
   }
 if(matrixkeyscan()!=10)
   {
    delayms(1);
    if(matrixkeyscan()!=10)
	{
     relay=1;
	}
   }
}
void grap()
{
  if (matrixkeyscan()==7)
  {
   delayms(10);
   if (matrixkeyscan()==7)
   {
   in1=1,in2=0;
   }
  }
  if (matrixkeyscan()==8)
  {
   delayms(10);
   if (matrixkeyscan()==8)
   {
   in1=0,in2=1;
   }
  }
  if (matrixkeyscan()==9)
  {
   delayms(10);
   if (matrixkeyscan()==9)
   {
   in1=0,in2=0;
   }
  }
}
void init()
{
	P0=0;
  dula=1;
  dula=0;
  P0=0xc0;
  wela=1;
  wela=0;
  TMOD=0x20;
  TH1=0xfd;
  TL1=0xfd;
  TR1=1;
  REN=1;
  SM0=0;
  SM1=1;	
  EA=1;
  ES=1;
}
void manipulator()
{
  if(matrixkeyscan()==1)//x轴正转
  {
    delayms(1);
    if(matrixkeyscan()==1)
    {
      dir_x = 1;
  	  while(matrixkeyscan()==1)
      {
        delay(1);
        pulse_x=0;
        delay(1);
        pulse_x=1;
        delay(1);        
      }
    }
  }
  if(matrixkeyscan()==2)//x轴反转
  {
    delayms(1);
    if(matrixkeyscan()==2)
    {
      dir_x = 0;
      while(matrixkeyscan()==2)
      {
        delay(1);
        pulse_x=0;
        delay(1);
        pulse_x=1;
        delay(1);        
      }
    } 
  }
  if(matrixkeyscan()==3)//y轴正转
  {
	delayms(1);
	if(matrixkeyscan()==3)
	{
      dir_y = 1;
	  while(matrixkeyscan()==3)
      {
        delay(1);
        pulse_y=0;
        delay(1);
        pulse_y=1;
        delay(1);        
      }
    }
  }
  if(matrixkeyscan()==4)//y轴反转
  {
	delayms(1);
	if(matrixkeyscan()==4)
	{
      dir_y = 0;
	  while(matrixkeyscan()==4)
      {
        delay(1);
        pulse_y=0;
        delay(1);
        pulse_y=1;
        delay(1);        
      }
    }
  }
  if(matrixkeyscan()==5)//z轴正转
  {
	delayms(1);
	if(matrixkeyscan()==5)
	{
      dir_z = 1;
	  while(matrixkeyscan()==5)
      {
        delay(1);
        pulse_z=0;
        delay(1);
        pulse_z=1;
        delay(1);        
      }
    }
  }
  if(matrixkeyscan()==6)//z轴反转
  {
	delayms(1);
	if(matrixkeyscan()==6)
	{
      dir_z = 0;
	  while(matrixkeyscan()==6)
      {
        delay(1);
        pulse_z=0;
        delay(1);
        pulse_z=1;
        delay(1);        
      }
    }
  }
  if(flag==1)
  {
    RI=0;
    switch(a)
	{
	  case 0:  					 //00000000B:
	  break;								
	  case 1:                    //00000001B:
	  dir_x = 1;
      while(!RI)
      {
        delay(1);
        pulse_x=0;
        delay(1);
        pulse_x=1;
        delay(1);        
      }
	  break;
	  case 2:                    //00000010B:
	  dir_x = 0;
      while(!RI)
      {
        delay(1);
        pulse_x= 0;
        delay(1);
        pulse_x= 1;
        delay(1);        
      }
	  break;
      case 4:                    //00000100B:
	  dir_y = 1;
      while(!RI)
      {
        delay(1);
        pulse_y= 0;
        delay(1);
        pulse_y= 1;
        delay(1);        
      }
	  break;
	  case 5:                    //00000101B:
      dir_x = 1;
	  dir_y = 1;
      while(!RI)
      {
        delay(1);
        pulse_x= 0;
        delay(1);
        pulse_x= 1;
        delay(1);  
        pulse_y= 0;
        delay(1);
        pulse_y= 1;
        delay(1);  
      }
	  break;
	  case 6:                      //00000110B:
	  dir_x = 0;
	  dir_y = 1;
      while(!RI)
      {
        delay(1);
        pulse_x= 0;
        delay(1);
        pulse_x= 1;
        delay(1);  
        pulse_y= 0;
        delay(1);
        pulse_y= 1;
        delay(1);  
      }
 	  break;
	  case 8:                       //00001000B:
	  dir_y = 0;
      while(!RI)
      {
        delay(1);
        pulse_y= 0;
        delay(1);
        pulse_y= 1;
        delay(1);        
      }
	  break;
	  case 11:                        //00001001B:
	  dir_x = 1;
	  dir_y = 0;
	  while(!RI)
      {
        delay(1);
        pulse_x= 0;
        delay(1);
        pulse_x= 1;
        delay(1);  
        pulse_y= 0;
        delay(1);
        pulse_y= 1;
        delay(1);  
      }
	  break;
	  case 12:                       //00001010B:
	  dir_x = 0;
	  dir_y = 0;
	  while(!RI)
      {
        delay(1);
        pulse_x= 0;
        delay(1);
        pulse_x= 1;
        delay(1);  
        pulse_y= 0;
        delay(1);
        pulse_y= 1;
        delay(1);  			
      }		
	  break;
      case 15:                       //00001111B:		
      break;
    }				 
			flag=0;
  }
}				
