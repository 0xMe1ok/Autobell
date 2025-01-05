void updateRTC() {
  if (NTP.updateNow()) {
    Datime dt(NTP);
    ds.setTime(dt);
  }
}