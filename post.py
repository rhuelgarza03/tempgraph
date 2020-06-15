import requests
import json
import serial
from time import sleep
import datetime

ser = serial.Serial('COM5', baudrate=9600, timeout=1)
if ser.isOpen():
     print(ser.name + ' is open...')

while 1:
    sleep(1)
    tdata = ser.readline()
    final = tdata.decode('utf-8')
    time = datetime.datetime.now().strftime("%I:%M:%S %p")
    print(final)
    url = "http://10.0.0.69/test"
    data = {"temp": final, "time": time}
    r = requests.post(url=url, json=data)
    #print(r.status_code, r.reason, r.text)
