#ifndef GPS_H
#define GPS_H

#include "stdint.h"
#include <string.h>
#include <Arduino.h>


enum GPRMC {
    Msg_id_p = 0,
    UTC_Time_p = 1,
    Status_p = 2,
    Latitude_p = 3,
    ES_indicator_p = 4,
    Longitude_p = 5,
    EW_indicator_p = 6,
    Speed_OG_p = 7,
    Date_p = 9,
};

class Sim {
private:
    /* data */
    String NMEA_data = "$GPRRC,105532.000,V,4334.25232,N,127.99024,E,0.31,193.96,121121,,,A*89";
    char* UTC_Time;
    char* Msg_id;
    char* Status;
    float Latitude ;
    char* ES_indicator;
    float Longitude;
    char* EW_indicator;
    float Speed_OG;
    char* Date;
    bool fixed = false;
public:
    Sim(/* args */);
    ~Sim();
    void set_NMEA_data(String NMEA_data);
    bool is_GPRMC();
    float get_Latitude();
    float get_Longitude();
    String get_UTC_Time();
    String get_Date();
    bool is_Status_A();
    float get_speed_bike();
    void collect_data();
    bool is_gps_fixed();
    void set_gps_fixed();
};

#endif