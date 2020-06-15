import serial
import datetime
import time

ser = serial.Serial('COM5', baudrate=9600, timeout=1)
if ser.isOpen():
     print(ser.name + ' is open...')
     
while 1:
    a = ser.readline()
    x = datetime.datetime.now()
    print(a)
    print(x.strftime("%I:%M:%S:%p"))
    time.sleep(1) # wait 1 second so you only get 1 datapoint per second





'''
port = 'COM5'
baud = 4800

ser = serial.Serial(port, baud, timeout=1)
if ser.isOpen():
     print(ser.name + ' is open...')
'''

'''
while 1:
    sleep(2)
    tdata = ser.readline()
    final = tdata.decode('utf-8')
    print(final)
'''


#tdata = ser.readline()
#print(tdata)
#final = tdata.decode('utf-8')
#print(final)