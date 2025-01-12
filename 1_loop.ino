void loop() {
  OS.tick();
  ui.tick();
  checkResetButton();
  
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