void updateRTCFromNTP() {
  if (NTP.updateNow()) {
    Datime dt(NTP);
    ds.setTime(dt);
    ds.updateNow();
  }
}

void updateRTCFromGP() {
  GPdate date = ui.getSystemDate();
  GPtime time = ui.getSystemTime();
  Datime dt(date.year, date.month, date.day, time.hour, time.minute, time.second);
  ds.setTime(dt);
  ds.updateNow();
}