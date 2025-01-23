void setup() {
  // Выставление режима пина для реле и кнопки
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  // Запуск часов реального времени и экрана
  Wire.begin(CLOCK_SDA, CLOCK_SCL); // SDA, SCL
  Wire.setClock(800000L);
  oled.init();
  drawInit();
  ds.begin();

  // Запуск LittleFS
  LittleFS.begin();

  // Проверка на сброс
  buttonPressStartTime = millis();
  checkResetButton();
  drawSomething("Включение...");

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

  uiLogin = configFile[SH("UI_Login")].toString();
  uiPass = configFile[SH("UI_Pass")].toString();

  const int preparationTime = millis();

  // Подключение к WiFi
  if (configFile[SH("WiFi_SSID")].toString().length() > 0 && configFile[SH("WiFi_PASS")].toString().length() > 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(configFile[SH("WiFi_SSID")], configFile[SH("WiFi_PASS")]);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      // Если время подключения превышено...
      if (millis() > kWifiConnectionAwait + preparationTime) {
        // то создаем точку доступа
        wifiAP();
        break;
      }
    }
  }
  else {
    wifiAP();
  }
  
  // Обновление времени RTC-модуля через NTP-сервер
  if (wifiConnected) {
    // Инициализация NTP-сервера
    NTP.begin();
    NTP.setGMT(configFile[SH("NTP_TimeOffset")]);
    NTP.setHost(configFile[SH("NTP_Host")]);
    
    updateRTCFromNTP();
  }
  
  // Подключение конструктора и запуск сервера веб-интерфейса
  ui.attachBuild(build);
  ui.attach(action);
  ui.start("autobell");

  // Аутентификация в веб-интерфейсе
  if (uiLogin.length() > 0 && uiPass.length() > 0) {
    const char* login = uiLogin.c_str();
    const char* pass = uiPass.c_str();
    
    ui.enableAuth(login, pass);
  }
}