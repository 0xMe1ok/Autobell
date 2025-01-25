/*
    Скетч проекта "Autobell"
    Устройство для автоматической подачи звонка для школ, колледжей и университетов.
    Управляется и настраивается через веб-интерфейс, сам девайс может
    подключаться к уже существующей Wi-Fi сети, или же раздавать свою точку доступа.

    https://github.com/0xMe1ok/Autobell
*/

// Библиотеки
#include <ESP8266WiFi.h>
#include <GyverPortal.h>
#include <GyverDS3231.h>
#include <GyverOS.h>
#include <GyverNTP.h>
#include <LittleFS.h>
#include <GyverDBFile.h>
#define OLED_SPI_SPEED 8000000ul
#include <GyverOLED.h>

// Пины подключения
#define CLOCK_SDA D5
#define CLOCK_SCL D6
#define RELAY_PIN D2
#define RESET_BUTTON_PIN D1

// Служебный флаг - больше нет звонков на сегодня
#define NOT_MORE_BELLING -1

// Переменные для работы системы
GyverOS<2> OS;
GyverPortal ui;
GyverDS3231 ds;
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;

// Переменные файлов БД
GyverDBFile configFile   (&LittleFS, "/autob/config.bin");   
GyverDBFile settingsFile (&LittleFS, "/autob/settings.bin"); 
GyverDBFile bellModesFile(&LittleFS, "/autob/bellmodes.bin");
GyverDBFile bellTimeFile (&LittleFS, "/autob/belltime.bin"); 
GyverDBFile bellDatesFile(&LittleFS, "/autob/belldates.bin");

String uiLogin = "";
String uiPass = "";

// Режим звонка
enum BellModes {
  Weekend = 0,
  Workday = 1,
  Shortened = 2,
  Holiday = 3
};

// Структура для данных типа Дата:Режим для БД
struct DateMode {
  String date;              // Дата формата dd.mm
  int mode;                 // Режим звонка (см. enum BellModes)
};

bool isRinging = false;     // Звонит/не звонит...

int bellmode = 0;           // Режим звонка текущего дня
int timeUntilBell = 0;      // Время до следующего звонка, сек
int nextBellTime = 0;       // Время следующего звонка, секундный формат с начала суток

int currentDay = -1;        // Текущий день

const long kResetHoldDuration = 10000; // Время удержания кнопки в миллисекундах
unsigned long buttonPressStartTime = 0; // Время начала удержания кнопки

const int kWifiConnectionAwait = 15000; // Ожидание WiFi, мс
bool wifiConnected = true;
