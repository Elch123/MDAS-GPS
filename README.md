# MDAS-GPS
code of setting up GPS on the MDAS system for the robotic painter

Commands are 
ssh mdas@192.168.1.113
password is MDASmdas!
gpsd tcp://192.168.1.104:9001
cd MDAS-GPS
screen
roscore
exit screen with ctrl-a ctrl-d

screen
python3 gpstoros.py
exit screen with ctrl-a ctrl-d

rostopic echo location 
