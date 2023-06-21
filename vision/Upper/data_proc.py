#coding=utf-8
#根据空格和换行对数据进行提取并输出
import os
def bia(target,manipulator,target_pre_position):
    threshold=0.01           #死区阈值
    threconf=0.5
    mflag=0                  #判断是否有机械臂
    tflag=0                 # 判断是否有目标
    filename = 'locdata.txt' # 给定文件路径
    lines = '' # 用于将存储行的变量提前声明为string格式，避免编译器自动声明时可能由于第一行的特殊情况造成的数据类型错误
    with open(filename, 'r') as file_to_read: # 打开文件，将其值赋予file_to_read
        while True:
            lines = file_to_read.readline() # 整行读取数据
            if not lines: # 若该行为空
                if tflag==0 or mflag==0:
                    if tflag==0:
                        if target_pre_position==[-1,-1]:  #若丢失目标位置且无前位置导入报错
                            bia=[3,3]
                            tc=target_pre_position  
                            return bia,tc
                        else:
                            tc=target_pre_position      #若丢失目标位置但有前位置导入将前位置赋tc
                    if mflag==0:            #若丢失执行器位置报错
                        bia=[3,3]
                        return bia,tc
                    break
                else:
                    break # 结束
            else:
                this_lines=lines.split() # 根据空格对字符串进行切割，由于切割后的数据类型有所改变(str-array)建议新建变量进行存储
                if this_lines[0]==manipulator:
                    conf=float(this_lines[5])       # 机械臂置信度
                    if conf>threconf:
                        mc=[(float(this_lines[1])-0.5),(float(this_lines[2])-0.5)]
                        mflag=1
                elif this_lines[0]==target:    
                    conf=float(this_lines[5])       # 目标置信度
                    if conf>threconf:
                        tc=[float(this_lines[1])-0.5,float(this_lines[2])-0.5]
                        tflag=1 

    bia= [tc[i]-mc[i] for i in range(0,len(mc))]    # 目标和操作臂偏差值

    if bia[0]>threshold:
        bia[0]=2        #01B
    elif bia[0]<-threshold:
        bia[0]=1        #10B
    else:
        bia[0]=0        #00B

    if bia[1]>threshold:
        bia[1]=1        #01B
    elif bia[1]<-threshold:
        bia[1]=2        #10B
    else:
        bia[1]=0        #00B
    return bia,tc

    