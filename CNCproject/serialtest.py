#import serial

#if __name__ == '__main__':
#    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
#    ser.reset_input_buffer()

#ser.write(b"zero")
    
#while True:
#    line = ser.readline().decode('utf-8').rstrip()
#    print(line)  


#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time


def zero():
    # script for proper zeroing
    #ser.write(b"zero")
    #wait()
    cmd="zero"
    time.sleep(1)
    arduino.write(cmd.encode())
    print(1)
    #time.sleep(0.1) #wait for arduino to answer
    #while arduino.inWaiting()==0: pass 
    print(2)
    answer=""
    
    while (answer != "finish"):
        #print(3)
        if  arduino.inWaiting()>0:
            answer=arduino.readline().decode('utf-8').rstrip()
            print("4\n",answer)
    
    print(answer)
    arduino.flushInput() #remove data after reading


if False:#__name__ == '__main__':
    
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    cmd=input("Enter command : ")
                    arduino.write(cmd.encode())
                    if (cmd == "move"):
                        cmd=input("Enter X target : ")
                        arduino.write(cmd.encode())
                        cmd=input("Enter Y target : ")
                        arduino.write(cmd.encode())
                    #time.sleep(0.1) #wait for arduino to answer
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0: 
                        answer=arduino.readline().decode('utf-8').rstrip()
                        print(answer)
                        arduino.flushInput() #remove data after reading
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")



if __name__ == '__main__':
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                print("Zero")
                zero()
                print("done")
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")
