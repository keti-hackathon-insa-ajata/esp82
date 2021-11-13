# esp82

You have to plug the two ultrasonic sensors signal wire on D5 and D6 pins, the GPS SIM28 TX wire on D7 and RX wire on D8

Define your distance between the two ultrasonic sensor  “#define DISTANCE_BETWEEN_ULTRASONIC” and the warning speed “#define WARNING_SPEED”
from the main.cpp then add your network SSID + PASSWORD and your server IP_ADDRESS on request.h

Don’t forget to add Ultrasonic library 
https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger.git
and ArduinJSON
https://github.com/bblanchon/ArduinoJson.git

Upload your code before connecting the GPS sensor 
