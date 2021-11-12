#include <Arduino.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Request.h>
#include <Speed.h>
#include <Sim.h>

#define WARNING_SPEED 35

Request req;
Speed speed(40);
Sim gps;
Ultrasonic ultrasonic_0(12);
Ultrasonic ultrasonic_1(14);
SoftwareSerial softwareSerial(13, 15);
int conteur;

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
      String buffer = softwareSerial.readStringUntil('\n');
      //Serial.println(buffer);
      gps.set_NMEA_data(buffer);
    }
    if (gps.is_GPRMC())
      {
        if (gps.is_Status_A())
          gps.set_gps_fixed();
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
      req.post_CT_DATA();
    }
    Serial.println("DEEP SLEEP ON");
    ESP.deepSleep(0);
  }
}