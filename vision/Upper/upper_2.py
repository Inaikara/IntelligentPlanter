import data_proc
import time
import serial
import struct
import socket,sys

manipulator='3'
target='1'      #green0 blue1 red2
t_pre=[-1,-1]

ser = serial.Serial()
ser.baudrate = 9600 #设置波特率（这里使用的是stc89c52）
ser.port = 'COM3' #端口是COM3
print(ser)
ser.open()#打开串口
print(ser.is_open)#检验串口是否打开
while(1):
    #延时
    time.sleep(0.05)

    bia,tc=data_proc.bia(target,manipulator,t_pre)   
    bio=bia[1]*4+bia[0] #xy
    if bio==9:
        bio=11
    if bio==10:
        bio=12
    if target=='1':
        tar_label=1
    if target=='2':
        tar_label=2    

    #加上品类标签
    dat=tar_label*16+bio
    #转换成字节类型
    bydat=struct.pack('B',dat)
    #写串口
    ser.write(bybia)
    t_pre=tc

    #s = ser.read(1)


'''
while(1):
    time.sleep(0.05)
    bia,tc=data_proc.bia(target,manipulator,t_pre)   
    bio=bia[1]*4+bia[0] #xy
    if bio==9:
        bio=11
    if bio==10:
        bio=12
    if target=='1':
        tar_label=1
    if target=='2':
        tar_label=2    

    bio=tar_label*16+bio
    bybia=struct.pack('B',bio)
    print(bybia)
    t_pre=tc
'''
