void queueNTPupdate() {
  OS.attach(4, NTPupdate, 100); // Добавление обновления времени в очередь                     
}

void NTPupdate() {
  NTP.updateNow();
  Datime dt(NTP);
  
  rtc.setTime(dt.second, dt.minute, dt.hour, dt.day, dt.month, dt.year);
  OS.detach(4);
}

void enableBell() {
  digitalWrite(cfg.relaypin, HIGH);
  OS.attach(3, disableBell, 5000); 
}

void disableBell() {
  digitalWrite(cfg.relaypin, LOW);
  OS.detach(3);
}

const char* bellStatus() {
  const char* bellEnabled = "Звонок активен 🔔";
  const char* bellDisabled = "Звонок неактивен 🔕";
  return digitalRead(cfg.relaypin) ? bellEnabled : bellDisabled;
}

const char* dayOfWeek() {
  const char* daysOfWeek[] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
  return daysOfWeek[rtc.getDay() - 1];
}

int getBellMode() {
  return daysofweekFile.get(String(rtc.getDay()));
}

String correctTime(String time) {
  return time.length() == 8 ? time : "00:00:00";
}

// GPTime funcs