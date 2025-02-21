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

void drawResetProcess() {
  oled.clear();
  oled.home();
  oled.print("Продолжайте держать");
  oled.setCursor(0, 1);
  oled.print("кнопку, чтоб сбросить");
  oled.setCursor(0, 2);
  oled.print("устройство...");

  oled.setCursor(0, 4);
  oled.print("Прогресс:");
  oled.fastLineV(0, 63, 53, 1);
  oled.fastLineV(127, 63, 53, 1);
  oled.rect(5, 63, map((millis() / 100), 0, 100, 5, 122), 53, 1);
  oled.update();
}
