#!/usr/bin/env python3

import serial

serialPort = serial.Serial('/dev/ttyACM1', 9600)
print(serialPort.name)


while(1):
    print('Waiting fot info')
    if(serialPort.in_waiting > 0):
        serialString = serialPort.readline()
        print(serialString.decode('Ascii'), end='')
