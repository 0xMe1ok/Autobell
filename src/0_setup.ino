void setup() {
  // Выставление режима пина для реле и кнопки
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  // Запуск часов реального времени и экрана
  Wire.begin(CLOCK_SDA, CLOCK_SCL); // SDA, SCL
  Wire.setClock(800000L);
  oled.init();
  drawInit();
  if (!ds.begin()) ds.setBuildTime();

  // Запуск LittleFS
  LittleFS.begin();

  // Инициализация файлов БД различных настроек
  configFile.begin(); 
  settingsFile.begin();
  bellModesFile.begin();
  bellTimeFile.begin();
  bellDatesFile.begin();

  // Если файлы не инициализированы...
  if (filesIsNotInitiated()) {
    // то инициализировать файлы!
    initFiles();
  }

  // Получение текущего режима звонка
  bellmode = getCurrentBellMode();
  nextBellTime = getNextBellTime();
  timeUntilBell = getTimeUntilBell();
  currentDay = ds.day();

  const int preparationTime = millis();

  // Подключение к WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(configFile[SH("WiFi_SSID")], configFile[SH("WiFi_PASS")]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    // Если время подключения превышено...
    if (millis() > wifiConnectionAwait + preparationTime) {
      // то создаем точку доступа
      WiFi.mode(WIFI_AP);
      WiFi.softAP("Autobell");

      break;
    }
  }
  //Serial.println(WiFi.localIP());
  
  // Подключение конструктора и запуск сервера веб-интерфейса
  ui.attachBuild(build);
  ui.attach(action);
  ui.start("autobell");

  // Аутентификация в веб-интерфейсе
  if (configFile[SH("UI_Login")].toString().length() > 0 && configFile[SH("UI_Pass")].toString().length() > 0) {
    const char* login = configFile[SH("UI_Login")].toString().c_str();
    const char* pass = configFile[SH("UI_Pass")].toString().c_str();
    
    ui.enableAuth(login, pass);
  }
  
  // Инициализация NTP-сервера
  NTP.begin(configFile[SH("NTP_TimeOffset")]);
  NTP.setHost(configFile[SH("NTP_Host")]);

  // Обновление времени RTC-модуля через NTP-сервер
  updateRTCFromNTP();
}