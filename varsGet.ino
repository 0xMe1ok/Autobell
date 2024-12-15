void configGet() {
  cfg.wifi_ssid = configFile.get("wifi_ssid");
  cfg.wifi_pass = configFile.get("wifi_pass");

  cfg.relaypin = configFile.get("relaypin");
  cfg.i2cscl = configFile.get("i2cscl");
  cfg.i2csda = configFile.get("i2csda");

  cfg.ntptimeoffset = configFile.get("ntptimeoffset");
  configFile["ntphost"].toStr(cfg.ntphost);

  configFile["ui_login"].toStr(cfg.ui_login);
  configFile["ui_pass"].toStr(cfg.ui_pass);
}


void dayOfWeekGet() {
  daysofw.monday = daysofweekFile.get("1");
  daysofw.tuesday = daysofweekFile.get("2");
  daysofw.wednesday = daysofweekFile.get("3");
  daysofw.thursday = daysofweekFile.get("4");
  daysofw.friday = daysofweekFile.get("5");
  daysofw.saturday = daysofweekFile.get("6");
  daysofw.sunday = daysofweekFile.get("7");
}
