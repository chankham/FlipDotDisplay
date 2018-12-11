import serial
serialport = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)
serialport.write(str.encode(str("hi")))
while True:
    s = serialport.readline()
    print(s)
    serialport.write(str.encode(str(s)))
