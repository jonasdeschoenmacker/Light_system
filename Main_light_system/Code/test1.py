import smbus
import time
import subprocess

I2C_ADDRESS = 0x0a

bus = smbus.SMBus(1)

#bus.write_byte(I2C_ADDRESS,0xFF)

values = [0,0,0,0,0,0,0,0,0,0,0]
aanTijd="2"
while bus.read_byte(I2C_ADDRESS)!=0xFF:
        time.sleep(0.1)
        pass

while True:
        for i in range(0,11):
                values[i]=bus.read_byte(I2C_ADDRESS)
                print "Read data is %02d" % values[i]
#       time.sleep(0.1)
#       if(values[i]>0xF0):
#               temp=values[i]-0xF0
#               print "Read data is %02d" % temp
#               subprocess.call(['python','/home/pi/Documents/testsend.py',str(values[i]),aanTijd])
                time.sleep(0.01)

        for i in range(1,11):
                if(values[i]>0xF0):
                        temp=values[i]-0xF0
                        #print "%02d" % temp
                        print temp
                        print str(temp)
                        subprocess.call(['python','/home/pi/Documents/testsend.py',str(temp),aanTijd])
                        time.sleep(0.01)
        time.sleep(1)