import serial
serialport = serial.Serial("/dev/ttyACM0",19200)
serialport.write("abcd1234")
serialport.write("\x1B")
while True:
        logfile = open("logoutput.txt","a")
        command = serialport.read()
        logfile.write(command)
        logfile.close()
