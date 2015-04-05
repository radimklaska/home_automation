#!/usr/bin/python

import sys
import time
import datetime

import Adafruit_DHT

# Type of sensor, can be Adafruit_DHT.DHT11, Adafruit_DHT.DHT22, or Adafruit_DHT.AM2302.
DHT_TYPE = Adafruit_DHT.DHT22

# Example of sensor connected to Raspberry Pi pin 23
DHT1_PIN = 4
DHT2_PIN = 17

# How long to wait (in seconds) between measurements.
FREQUENCY_SECONDS = 60*10

# Where to log
FILE = 'temps.csv'

print 'Logging sensor measurements to {0} every {1} seconds.'.format(FILE, FREQUENCY_SECONDS)
print 'Press Ctrl-C to quit.'

# Give it some time (3min) co connect to NTP and set proper time
time.sleep(180)

while True:

	# Attempt to get sensor reading.
	humidity1, temp1 = Adafruit_DHT.read(DHT_TYPE, DHT1_PIN)
	humidity2, temp2 = Adafruit_DHT.read(DHT_TYPE, DHT2_PIN)

	# Skip to the next reading if a valid measurement couldn't be taken.
	# This might happen if the CPU is under a lot of load and the sensor
	# can't be reliably read (timing is critical to read the sensor).
	if humidity1 is None or temp1 is None or humidity2 is None or temp2 is None:
		time.sleep(2)
		continue

        datetime = time.strftime("%d.%m.%Y %H:%M:%S")
        humidity1 = '{0:0.1f}'.format(humidity1).replace(".", ",")
        temp1 = '{0:0.1f}'.format(temp1).replace(".", ",")
        humidity2 = '{0:0.1f}'.format(humidity2).replace(".", ",")
        temp2 = '{0:0.1f}'.format(temp2).replace(".", ",")

        f = open(FILE,'a+')
        print 'Date time: {0}, Temp1: {1}C, Humi1: {2}%, Temp2: {3}C, Humi2: {4}%'.format(datetime, temp1, humidity1, temp2, humidity2)
        f.write('{0};{1};{2};{3};{4}\n'.format(datetime, temp1, humidity1, temp2, humidity2))
	f.close()

	time.sleep(FREQUENCY_SECONDS)
