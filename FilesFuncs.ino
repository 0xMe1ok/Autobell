bool filesIsNotInitiated() {
  return !configFile.has(SH("INIT"));
}

void initFiles() {
  // КОНФИГ
  configFile.init(SH("INIT"), "INIT");
  configFile.init(SH("WiFi_SSID"), "yourwifihere");
  configFile.init(SH("WiFi_PASS"), "yourpasshere");
  configFile.init(SH("NTP_TimeOffset"), 1);
  configFile.init(SH("NTP_Host"), "pool.ntp.org");
  configFile.init(SH("UI_Login"), "");
  configFile.init(SH("UI_Pass"), "");

  // НАСТРОЙКИ
  settingsFile.init(SH("BELL_RingingTime"), 5000);

  // ЗВОНКИ - РЕЖИМ
  bellModesFile.init(SH("D1"), (int) Weekday); // Понедельник
  bellModesFile.init(SH("D2"), (int) Weekday); // Вторник
  bellModesFile.init(SH("D3"), (int) Weekday); // Среда
  bellModesFile.init(SH("D4"), (int) Weekday); // Четверг
  bellModesFile.init(SH("D5"), (int) Weekday); // Пятница
  bellModesFile.init(SH("D6"), (int) Weekend); // Суббота
  bellModesFile.init(SH("D7"), (int) Weekend); // Воскресенье

  // ЗВОНКИ - ВРЕМЯ
  GPtime firstTime(9,0,0);
  GPtime secondTime(9,45,0);

  bellTimeFile.init(SH("Weekday_BellCount"), 2);
  bellTimeFile.init(SH("Weekday_1"), firstTime);
  bellTimeFile.init(SH("Weekday_2"), secondTime);

  bellTimeFile.init(SH("Short_BellCount"), 2);
  bellTimeFile.init(SH("Short_1"), firstTime);
  bellTimeFile.init(SH("Short_2"), secondTime);

  bellTimeFile.init(SH("Holiday_BellCount"), 2);
  bellTimeFile.init(SH("Holiday_1"), firstTime);
  bellTimeFile.init(SH("Holiday_2"), secondTime);

  // ЗВОНКИ - ДАТЫ
  // Даты в формате "dd.mm"
  DateMode dmInit;
  dmInit.date = "31.12";
  dmInit.mode = Weekend;

  bellDatesFile.init(SH("DatesCount"), 1);
  bellDatesFile.init(SH("Date_1"), dmInit); // 31 декабря, выходной

  configFile.update();
  settingsFile.update();
  bellModesFile.update();
  bellTimeFile.update();
  bellDatesFile.update();
}

void removeAllFiles() {
  LittleFS.remove("/autob/config.bin");
  LittleFS.remove("/autob/settings.bin");
  LittleFS.remove("/autob/bellmodes.bin");
  LittleFS.remove("/autob/belltime.bin");
  LittleFS.remove("/autob/belldates.bin");
}