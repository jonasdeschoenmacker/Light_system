#!/usr/bin/env python
import smbus
import time
import sys
#import cgi
#import cgitb
#cgitb.enable()

#print("Status: 204 No Content")
#print("Content-type: text/plain")
#print("")

I2C_ADDRESS = 0x08

bus = smbus.SMBus(1)

#lamp=int(sys.argv[1])+16
#timer=int(sys.argv[2])
#print lamp
#print timer

#bus.write_byte(I2C_ADDRESS,int(lamp))
#bus.write_i2c_block_data(I2C_ADDRESS,42,[0])
bus.write_i2c_block_data(I2C_ADDRESS,42,[int(sys.argv[1]),int(sys.argv[2])])