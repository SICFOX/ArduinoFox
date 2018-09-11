#! -*- coding: utf-8 -*-

import serial
import time

ser = serial.Serial('/dev/cu.wchusbserial1420', 9600)

v = 0
vc = 1

while True:
    v += vc
    if v > 255:
        v = 0
    print v
    ser.write(v)

    time.sleep(0.02)
