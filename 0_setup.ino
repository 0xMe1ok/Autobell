void setup() {
  // Старт Serial
  Serial.begin(115200);
  delay(100);

  Serial.println("1. RELAY OUTPUT");
  // Выставление режима пина для реле
  pinMode(RELAY_PIN, OUTPUT);

  Serial.println("2. I2C BEGIN");
  // Запуск часов реального времени и экрана
  Wire.begin(CLOCK_SDA, CLOCK_SCL); // SDA, SCL
  Wire.setClock(800000L);
  oled.init();
  drawInit();
  if (!ds.begin()) ds.setBuildTime();

  Serial.println("3. INIT LITTLEFS");
  // Запуск LittleFS
  LittleFS.begin();

  Serial.println("4. FILES BEGIN");
  // Инициализация файлов БД различных настроек
  configFile.begin(); 
  settingsFile.begin();
  bellModesFile.begin();
  bellTimeFile.begin();
  bellDatesFile.begin();

  Serial.println("5. INIT FILES");
  // Если файлы не инициализированы...
  if (filesIsNotInitiated()) {
    // то инициализировать файлы!
    initFiles();
  }

  Serial.println("6. BELL VARIABLES GET");
  // Получение текущего режима звонка
  bellmode = getCurrentBellMode();
  nextBellTime = getNextBellTime();
  timeUntilBell = getTimeUntilBell();
  previousDay = ds.day();

  Serial.println("7. WIFI BEGIN");
  // Подключение к WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(configFile[SH("WiFi_SSID")], configFile[SH("WiFi_PASS")]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
    // Если время подключения превышено...
    if (millis() > wifiConnectionAwait) {
      // то создаем точку доступа
      WiFi.mode(WIFI_AP);
      WiFi.softAP("Autobell");

      break;
    }
  }
  Serial.println(WiFi.localIP());
  
  Serial.println("8. UI BEGIN");
  // Подключение конструктора и запуск сервера веб-интерфейса
  ui.attachBuild(build);
  ui.attach(action);
  ui.start("autobell");

  Serial.println("9. UI AUTH CHECK");
  // Аутентификация в веб-интерфейсе
  if (configFile[SH("UI_Login")].toString().length() > 0 && configFile[SH("UI_Pass")].toString().length() > 0) {
    const char* login = configFile[SH("UI_Login")].toString().c_str();
    const char* pass = configFile[SH("UI_Pass")].toString().c_str();
    
    ui.enableAuth(login, pass);
    Serial.println("AUTH ENABLED.");
    Serial.print("LOGIN:"); Serial.println(configFile[SH("UI_Login")].toString());
    Serial.print("PASSWORD:"); Serial.println(configFile[SH("UI_Password")].toString());
  }
  
  Serial.println("10. NTP BEGIN");
  // Инициализация NTP-сервера
  NTP.begin(configFile[SH("NTP_TimeOffset")]);
  NTP.setHost(configFile[SH("NTP_Host")]);

  Serial.println("11. UPDATE RTC");
  // Обновление времени RTC-модуля через NTP-сервер
  updateRTC();

  Serial.println("DONE.");
}