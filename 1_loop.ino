void loop() {
  OS.tick();
  ui.tick();
  
  if (ds.tick()) {
    drawInfo();
    if (isTimeToBell()) {
      enableBellPlanned();
      nextBellTime = getNextBellTime();
    }
    timeUntilBell = getTimeUntilBell();
    if (isNewDay(previousDay, ds.day())) {
      ESP.restart();
    }
  }
}