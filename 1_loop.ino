void loop() {
  OS.tick();
  ui.tick();
  
  if (ds.tick()) {
    timeUntilBell = getTimeUntilBell();

    if (isTimeToBell()) {
      enableBellForDuration();
      nextBellTime = getNextBellTime();
    }
    
    if (isNewDay(currentDay, ds.day())) {
      ESP.restart();
    }

    drawInfo();
  }
}