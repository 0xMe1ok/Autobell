void loop() {
  OS.tick();
  ui.tick();
  
  if (ds.tick()) {
    timeUntilBell = getTimeUntilBell();

    if (isTimeToBell()) {
      enableBellPlanned();
      nextBellTime = getNextBellTime();
    }
    
    if (isNewDay(currentDay, ds.day())) {
      ESP.restart();
    }

    drawInfo();
  }
}