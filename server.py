#!/usr/bin/env python

import socket
import time
import serial

ser = serial.Serial("/dev/ttyACM0", 9600)
ser.stopbits = 2
print ser

time.sleep(2)

count = 0

bot = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 6000
bot.bind(('', int(port)))
bot.listen(5)
client, address = bot.accept()
while True:
  data = client.recv(17)
  print data
  ser.write(data)
 
