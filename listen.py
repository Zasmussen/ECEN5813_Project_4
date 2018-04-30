import serial
serialport = serial.Serial("/dev/ttyACM0",19200)
while True:
        logfile = open("logoutput.txt","a")
        command = serialport.read()
        logfile.write(command)
        print command
        logfile.close()
