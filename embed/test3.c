//#include <reg52.h>
//#define uchar unsigned char
//#define uint unsigned int
//sbit dula=P2^6;					//??
//sbit wela=P2^7;					//??
//uchar code table1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
//                    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};			//??????
//uchar code table2[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};			//??????
//void delayms(uint);				//????
//void main()
//{
//	while(1)
//	{
//		uint a;
//		for(a=0;a<6;a++)
//		{
//			dula=1;
//			P0=table1[a];
//			dula=0;				//??
//			P0=table2[a];
//			wela=1;
//			wela=0;				//??
//			delayms(1);			//????
//		}
//	}
//}
//void delayms(uint xms)
//{
//	uint i,j;
//	for(i=xms;i>0;i--)
//		for(j=113;j>0;j--);
//}
