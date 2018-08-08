import gpsd
import time
import rospy
from sensor_msgs.msg import NavSatFix
# Connect to the local gpsd
gpsd.connect()

# Get gps position
cont=True
pub = rospy.Publisher('location', NavSatFix, queue_size=10)
rospy.init_node('gps_converter', anonymous=True)

while(cont):
	time.sleep(.1)
	try:
		packet = gpsd.get_current()
# See the inline docs for GpsResponse for the available data
		print(packet.position())
		print(packet.position_precision())
		print(packet.speed())
		place=packet.position()
		location=NavSatFix(latitude=place[0],longitude=place[1],altitude=packet.altitude(),position_covariance=[0,0,0,0,0,0,0,0,0],position_covariance_type=1)
		pub.publish(location)
	except ZeroDivisionError:
		pass


