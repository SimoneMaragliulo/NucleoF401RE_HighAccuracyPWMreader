import serial
import re

ser = serial.Serial("COM5", 115200)
ser.flush()

while True:
     cc=str(ser.readline())
     # print(cc)
     cc = cc[2:][:-5]
     # cc1 = cc[9:][:-12]
     # print(cc)
     a = re.findall(r'\d+', cc)
     # print(a)
     # a1 = re.findall(r'\d+', cc1)
     b = float(a[0])/100
     c = float(a[1])/100
     d = float(a[2])/100
     e = float(a[3])/100
     # b1 = float(a1[0])/100
     # c1 = float(a1[1])/100
     print(str(b) + ',' + str(c)+ ',' + str(d) + ',' + str(e))
