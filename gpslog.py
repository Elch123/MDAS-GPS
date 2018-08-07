import gpsd
import time
# Connect to the local gpsd
gpsd.connect()

# Get gps position
cont=True
while(cont):
	time.sleep(.1)
	try:
		packet = gpsd.get_current()

# See the inline docs for GpsResponse for the available data
		print(packet.position())
		print(packet.position_precision())
		print(packet.speed())
	except(KeyboardInterrupt, SystemExit):
		cont=False
	except:
		pass
