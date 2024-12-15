void setup() {
  Serial.begin(115200);   
  delay(500);

  LittleFS.begin();

  configFile.begin();
  settingsFile.begin();
  daysofweekFile.begin();
  belltimeFile.begin();

  configGet();
  dayOfWeekGet();
  bellmode = getBellMode();

  pinMode(cfg.relaypin, OUTPUT);
  Wire.begin(cfg.i2csda, cfg.i2cscl);

  // Подключаемся к WiFi
  w_ssid = cfg.wifi_ssid;
  w_pass = cfg.wifi_pass;

  Serial.println(w_ssid);
  Serial.println(w_pass);

  WiFi.mode(WIFI_STA);
  WiFi.begin(w_ssid.c_str(), w_pass.c_str()); // Ошибка решается, если задать переменные через скетч, а не через Upload ESP32 Data -> LittleFS
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  Serial.println(cfg.ui_login);
  Serial.println(cfg.ui_pass);

  // Подключаем конструктор и запускаем
  ui.attachBuild(build);
  ui.attach(action);
  ui.start("autobell");

  // Включаем авторизацию
  ui.enableAuth(cfg.ui_login, cfg.ui_pass);

  // Запускаем NTP-либу
  NTP.begin(cfg.ntptimeoffset);
  NTP.setHost(cfg.ntphost);
}
