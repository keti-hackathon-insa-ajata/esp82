#ifndef REQUEST_H
#define REQUEST_H

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Speed.h>
#include <Sim.h>
#include <vector>

using namespace std;

class Request
{
private:
    /* data */
    //const char* SSID = "Livebox-FA60";
    //const char* PASS = "9F3C2C923F8F18396F4C818A79";
    const char* SSID = "AndroidAPBD99";
    const char* PASS = "chks9274";
    //String url_data = "http://192.168.43.233:8080/~/mn-cse/mn-name/SmartMeter/DATA";
    //String url_data = "http://192.168.1.16:8080";
    String url_data = "http://192.168.43.202:3000/api/markers";
    String url_descreptor = "http://192.168.43.233:8080/~/mn-cse/mn-name/[CT]/DESCRIPTOR";   
    vector<String> data;

public:
    int code_http;
    Request(/* args */);
    ~Request();
    void wifi_init();
    void wifi_scan();
    void Wifi_cnx();
    void get_data(Speed spd, Sim gps);
    void post_CT_DATA();
    void post_CT_DESCREPTOR();
};




#endif