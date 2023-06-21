import data_proc
import time
import struct
import socket,sys

#种类
manipulator='3'
target='1'      #green0 blue1 red2
t_pre=[-1,-1]

TCP_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# s此时是一个Socket对象，拥有发送和接受网络数据的功能
# AF_INET（IPV4协议用于 Internet 进程间通信）， AF_UNIX（用于同一台机器进程间通信）
# 套接字类型：可以是 SOCK_STREAM（流式套接字，用于TCP协议） 或者 SOCK_DGRAM（数据报套接字，用于UDP协议）
print ('looking for server')
try:
 TCP_client.connect(("192.168.4.1", 8080))
 #这里的IP是8266作为热点后的IP地k  址
 print ('done.')
except:
 print('server not find')


while(1):
   #延时
   time.sleep(0.05)
   bia,tc=data_proc.bia(target,manipulator,t_pre) 
   bio=bia[0]*4+bia[1] #xy
   if bio==9:
      bio=11
   if bio==10:
      bio=12
   if bio==15:
      bio=14

   if target=='0':
      tar_label=0
   if target=='1':
      tar_label=1
   if target=='2':
      tar_label=2    

   t_pre=tc
   #加上品类标签00
   dat=tar_label*16+bio
   #转换成字节类型

   bydat=struct.pack('B',dat)
   try :
      #Set the whole string
      #send_code='0'
      #s.send(send_code.encode("gbk"))
      TCP_client.send(bydat)
      print(bydat)
      print ('Message send successfully')
   except socket.error:
      #Send failed
      print ('Send failed')

