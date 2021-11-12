#include "Sim.h"

Sim::Sim(/* args */)
{
}

Sim::~Sim()
{
}

void Sim::set_NMEA_data(String data)
{
    this->NMEA_data = data;
}

bool Sim::is_GPRMC()
{
    String buffer = this->NMEA_data;
    Serial.println("");
    Serial.println(buffer);
    uint8_t buffer_size = this->NMEA_data.length();
    buffer.remove(6, buffer_size);
    if (buffer.compareTo("$GPRMC"))
        return false;
    else
        return true;
}

float Sim::get_Latitude()
{
    char *val = NULL;
    uint8_t buffer_size = this->NMEA_data.length();
    char buff_char[buffer_size];
    this->NMEA_data.toCharArray(buff_char, buffer_size);
    val = strtok(buff_char, ",");
    for (size_t i = 0; i < Latitude_p; i++)
    {
        val = strtok(NULL, ",");
    }
    float Latitude_conv = atof(val) / 100;
    uint8_t int_part = (int)Latitude_conv;
    Latitude_conv -= int_part;
    Latitude_conv *= 100;
    Latitude_conv /= 60;
    Latitude_conv += int_part;

    //Serial.printf("Latitude : %f\n", Latitude_conv);

    this->Latitude = Latitude_conv;
    return Latitude_conv;
}

float Sim::get_Longitude()
{
    char *val = NULL;
    uint8_t buffer_size = this->NMEA_data.length();
    char buff_char[buffer_size];
    this->NMEA_data.toCharArray(buff_char, buffer_size);
    val = strtok(buff_char, ",");
    for (size_t i = 0; i < Longitude_p; i++)
    {
        val = strtok(NULL, ",");
    }
    float Longitude_conv = atof(val) / 100;
    uint8_t int_part = (int)Longitude_conv;
    Longitude_conv -= int_part;
    Longitude_conv *= 100;
    Longitude_conv /= 60;
    Longitude_conv += int_part;

    //Serial.printf("Longitude : %f\n", Longitude_conv);

    this->Longitude = Longitude_conv;
    return Longitude_conv;
}

String Sim::get_UTC_Time()
{
    char *val = NULL;
    uint8_t buffer_size = this->NMEA_data.length();
    char buff_char[buffer_size];
    this->NMEA_data.toCharArray(buff_char, buffer_size);
    val = strtok(buff_char, ",");
    for (size_t i = 0; i < UTC_Time_p; i++)
    {
        val = strtok(NULL, ",");
    }
    String s_val = (String) val[0]+val[1] + ":" + val[2]+val[3] + ":" + val[4]+val[5]+val[6]+val[7]+val[8]+val[9];
    buffer_size = s_val.length();
    s_val.toCharArray(buff_char, buffer_size+1);
    this->UTC_Time = buff_char;
    //Serial.println(this->UTC_Time);
    //Serial.printf(" UTC_Time %d \n", this->UTC_Time);
    return this->UTC_Time;
}

String Sim::get_Date()
{
    char *val = NULL;
    uint8_t buffer_size = this->NMEA_data.length();
    char buff_char[buffer_size];
    this->NMEA_data.toCharArray(buff_char, buffer_size);
    val = strtok(buff_char, ",");
    for (size_t i = 0; i < Date_p; i++)
    {
        val = strtok(NULL, ",");
    }
    
    String s_val =(String) "20" + val[1] + val[0] + "-" + val[3]+val[2] + "-" + val[5] +val[4];
    buffer_size = s_val.length();
    s_val.toCharArray(buff_char, buffer_size+1);
    this->Date = buff_char;
    //Serial.printf("DATE: %s \n", this->Date);
    return this->Date;
}

bool Sim::is_Status_A()
{
    char *val = NULL;
    uint8_t buffer_size = this->NMEA_data.length();
    char buff_char[buffer_size];
    this->NMEA_data.toCharArray(buff_char, buffer_size);
    val = strtok(buff_char, ",");
    for (size_t i = 0; i < Status_p; i++)
    {
        val = strtok(NULL, ",");
    }

    this->Status = val;

    //Serial.print("STATUS: "); Serial.println(this->Status);

    if (val[0] == 'A')
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

float Sim::get_speed_bike()
{
    char *val = NULL;
    uint8_t buffer_size = this->NMEA_data.length();
    char buff_char[buffer_size];
    this->NMEA_data.toCharArray(buff_char, buffer_size);
    val = strtok(buff_char, ",");
    for (size_t i = 0; i < Speed_OG_p; i++)
    {
        val = strtok(NULL, ",");
    }
    float Speed_OG = atof(val) * 1.852;
    this->Speed_OG = Speed_OG;
    //Serial.printf("Speed_OG: %f \n", this->Speed_OG);
    return this->Speed_OG;
}

void Sim::collect_data()
{
    this->get_Date();
    this->get_Latitude();
    this->get_Longitude();
    this->get_speed_bike();
    this->get_UTC_Time();
}

bool Sim::is_gps_fixed() {
    return this->fixed;
}
void Sim::set_gps_fixed() {
    this->fixed = true;
}