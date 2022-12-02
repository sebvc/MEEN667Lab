import serial

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.reset_input_buffer()

ser.write(b"zero")

line=""
while line != "finish":
    line = ser.readline().decode('utf-8').rstrip()
    print(line)

