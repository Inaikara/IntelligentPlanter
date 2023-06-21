'''
此时电脑作为客户端
8266作为服务器开启自身的热点，服务器必须为多链接方式，无法实现透传
第一次配置：
 AT+RST
 AT+CWMODE=2,此时8266为AP模式
 AT+CWSAP="test","1234567890HMZ",11,0  ，热点名字、密码、通道11通道与其他的互不干扰，选择这种最好，0不需要密码接入
 AT+CIPMUX=1 多链接
 AT+CIPSERVER=1 开启服务器模式,不写端口号，默认为333
重新上电，只有wifi保留
再次上电，需要重新配置连接方式以及是否监听，所以连接wifi需要后，8266需要
 AT+CIPMUX=1 
 AT+CIPSERVER=1 
并且在本py文件需要重新执行
'''
import socket
import struct
import time

TCP_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# s此时是一个Socket对象，拥有发送和接受网络数据的功能
# AF_INET（IPV4协议用于 Internet 进程间通信）， AF_UNIX（用于同一台机器进程间通信）
# 套接字类型：可以是 SOCK_STREAM（流式套接字，用于TCP协议） 或者 SOCK_DGRAM（数据报套接字，用于UDP协议）
print ('looking for server')
try:
 TCP_client.connect(("192.168.4.1", 8080))
 #这里的IP是8266作为热点后的IP地址
 print ('done.')
except:
 print('server not find')

while(1):
 try :
    #Set the whole string
    
    send_code=0x0b
    if send_code=="exit":
       break
    TCP_client.send(struct.pack('B',send_code))
    time.sleep(0.2)
    print ('Message send successfully')
 except socket.error:
     #Send failed
     print ('Send failed')

'''   
 #receive  recvfrom
 recv_data=s.recv(4)
 if not recv_data:
    break

 print('receive successfully:',recv_data)
'''
 
 
 




