void updateRTCFromNTP() {
  if (NTP.updateNow()) {
    Datime dt(NTP);
    ds.setTime(dt);
  }
}