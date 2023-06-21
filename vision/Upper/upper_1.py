import data_proc
import time
import serial
import struct

manipulator='3'
target='0'      #green0 blue1 red2 
                #不干   抓取   喷水
t_pre=[-1,-1]


ser = serial.Serial()
ser.baudrate = 9600 #设置波特率（这里使用的是stc89c52）
ser.port = 'COM5' #端口是COM3
print(ser)
ser.open()#打开串口
print(ser.is_open)#检验串口是否打开

'''
while(1):
    time.sleep(0.5)
    bia=data_proc.bia('0')
    bio=bia[0]*4+bia[1] #xy
    bybia=struct.pack('B', bio)
    print(bybia)
    ser.write(bybia)
    #s = ser.read(1)
    #print(s)
'''

while(1):

    time.sleep(0.5)
    bia,tc=data_proc.bia(target,manipulator,t_pre)   

    #bia=[1,1] #xy 1:y- 1:x-

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

    #加上品类标签
    dat=tar_label*16+bio
    #转换成字节类型
    bydat=struct.pack('B',dat)
    #写串口
    print(tc)
    #print(bydat)
    ser.write(bydat)
    t_pre=tc

'''
    heightbyte = ser.read(1)
    height = struct.unpack('>B', heightbyte)
    print(height[0])
'''

