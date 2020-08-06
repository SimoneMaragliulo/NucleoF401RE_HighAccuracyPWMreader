import serial
import re

ser = serial.Serial("COM5", 115200)
ser.flush()

while True:
     
     cc=str(ser.readline())
     cc = cc[2:][:-5]
     a = re.findall(r'\d+', cc)
     b = float(a[0])/100
     c = float(a[1])/100
     d = float(a[2])/100
     e = float(a[3])/100
     
     print(str(b) + ',' + str(c)+ ',' + str(d) + ',' + str(e))
