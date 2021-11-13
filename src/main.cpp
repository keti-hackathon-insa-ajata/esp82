#include <Arduino.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Request.h>
#include <Speed.h>
#include <Sim.h>

#define WARNING_SPEED 35
#define DISTANCE_BETWEEN_ULTRASONIC 40

#define D5 14
#define D6 12
#define D7 13
#define D8 15

Request req;
Speed speed(DISTANCE_BETWEEN_ULTRASONIC);
Sim gps;
Ultrasonic ultrasonic_0(D5);
Ultrasonic ultrasonic_1(D6);
SoftwareSerial softwareSerial(D7, D8);

void set_GPS();

void setup()
{
  Serial.begin(9600);
  softwareSerial.begin(9600);

  req.Wifi_cnx();

  softwareSerial.print("$PMTK101*32\r\n");
}

void loop()
{

  while (!gps.is_gps_fixed())
  {
    if (softwareSerial.available())
    {
      String buffer = softwareSerial.readStringUntil('\n'); // Exemple"$GPRMC,105532.000,A,4334.25232,N,127.99024,E,0.31,193.96,121121,,,A*89"
      gps.set_NMEA_data(buffer);                                        //|              |
    }                                                                   //|              | 
    if (gps.is_GPRMC())                                              //$GPRMC            |
      {                                                                                //|
        if (gps.is_Status_A())                                                         //A = DATA VALID V = DATA NOT VALID
        {
          gps.set_gps_fixed();
        }
      }
  }
  long range_0 = ultrasonic_0.MeasureInCentimeters();
  delay(10);
  long range_1 = ultrasonic_1.MeasureInCentimeters();
  delay(10);
  speed.set_range_cm(range_0, range_1);
  speed.compute_vehicles_speed();
  if (speed.get_vehicule_speed() > WARNING_SPEED)
  {
    while (softwareSerial.available())
    {
      String buffer = softwareSerial.readStringUntil('\n');
      gps.set_NMEA_data(buffer);
      if (gps.is_GPRMC())
      {
        break;
      }
    }
    gps.collect_data();
    req.get_data(speed, gps);
    speed.reset();
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("CONNECTED");
    while (req.code_http != 200)
    {
      Serial.println(req.code_http);
      req.post_DATA();
    }
    Serial.println("DEEP SLEEP ON");
    ESP.deepSleep(0);
  }
}
