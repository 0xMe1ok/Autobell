#include <WiFi.h>
#include <GyverPortal.h>
#include <microDS3231.h>
#include <GyverOS.h>
#include <GyverNTP.h>

#include <LittleFS.h>
#include <PairsFile.h>

GyverOS<5> OS;
GyverPortal ui;
MicroDS3231 rtc;

PairsFile configFile(&LittleFS,   "/config.dat",   5000);
PairsFile settingsFile(&LittleFS, "/settings.dat", 5000);
PairsFile daysofweekFile(&LittleFS, "/daysofweek.dat", 5000);
PairsFile belltimeFile(&LittleFS, "/belltime.dat", 5000);

struct config {
  String wifi_ssid;
  String wifi_pass;
  uint8_t relaypin;
  uint8_t i2cscl;
  uint8_t i2csda;
  uint8_t ntptimeoffset;
  char ntphost[32];
  char ui_login[32];
  char ui_pass[32];
};

config cfg;

struct daysofweek {
  uint8_t monday;
  uint8_t tuesday;
  uint8_t wednesday;
  uint8_t thursday;
  uint8_t friday;
  uint8_t saturday;
  uint8_t sunday;
};

enum BellMode {
  Weekend = 0,
  Weekday = 1,
  Shortened = 2,
  Holiday = 3
};

daysofweek daysofw;

const byte kBellPairs = 10;

int bellmode = 0;
String str_nextbelltime;
long nextbelltime;

String w_ssid = "";
String w_pass = "";
