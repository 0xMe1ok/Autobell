void drawInfo() {
  oled.clear();
  oled.home();
  oled.print(ds.toString());
  oled.setCursor(0, 2);
  oled.print("Звонок в:");
  oled.setCursor(79, 2);
  oled.print(isNotMoreBelling() ? "НЕТ ЗВОН" : daySecondsToHMS(nextBellTime));
  oled.setCursor(0, 4);
  oled.print("До звонка:");
  oled.setCursor(79, 4);
  oled.print(daySecondsToHMS(timeUntilBell));
  oled.setCursor(0, 6);
  oled.print(isRinging ? "Звонок активен!" : "Звонок неактивен!");
  oled.update();
}

void drawSomething(String message) {
  oled.clear();
  oled.home();
  oled.print(message);
  oled.update();
}

void drawInit() {
  oled.clear();
  oled.home();
  oled.print("Включение...");
  oled.update();
}
