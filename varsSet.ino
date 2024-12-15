void configSet() {
  configFile["wifi_ssid"] = ui.getString("wifi_ssid");
  configFile["wifi_pass"] = ui.getString("wifi_pass");
  configFile["relaypin"] = (uint8_t) ui.getInt("relaypin");
  configFile["i2csda"] = (uint8_t) ui.getInt("i2csda");
  configFile["i2cscl"] = (uint8_t) ui.getInt("i2cscl");
  configFile["ntptimeoffset"] = (uint8_t) ui.getInt("ntptimeoffset");
  configFile["ntphost"] = ui.getString("ntphost");
  configFile["ui_login"] = ui.getString("ui_login");
  configFile["ui_pass"] = ui.getString("ui_pass");
  configFile.update();
}

void settingsSet() {
  daysofweekFile["1"] = ui.getInt("slct_bellmode_monday");
  daysofweekFile["2"] = ui.getInt("slct_bellmode_tuesday");
  daysofweekFile["3"] = ui.getInt("slct_bellmode_wednesday");
  daysofweekFile["4"] = ui.getInt("slct_bellmode_thursday");
  daysofweekFile["5"] = ui.getInt("slct_bellmode_friday");
  daysofweekFile["6"] = ui.getInt("slct_bellmode_saturday");
  daysofweekFile["7"] = ui.getInt("slct_bellmode_sunday");

  for (int i = 1; i < (kBellPairs * 2) + 1; i++) {
    belltimeFile["weekday" + String(i)] = ui.getTime("time_weekdays" + String(i)).encode();
    belltimeFile["shortened" + String(i)] = ui.getTime("time_shortened" + String(i)).encode();
    belltimeFile["holiday" + String(i)] = ui.getTime("time_holiday" + String(i)).encode();

    Serial.print(i); Serial.print(": ui[");
    Serial.print(ui.getTime("time_weekdays" + String(i)).encode());
    Serial.print("] var[");
    Serial.print(belltimeFile["weekday" + String(i)]);
    Serial.println("]");
  }

  daysofweekFile.update();
  belltimeFile.update();
}