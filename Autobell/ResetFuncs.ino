void checkResetButton() {
    drawSomething("Процесс сброса, ждите...");
    while (digitalRead(RESET_BUTTON_PIN) == LOW) { // Кнопка нажата (если кнопка замыкает на GND)
        drawSomething(String(millis()));
        if (millis() - buttonPressStartTime >= kResetHoldDuration) {
            while (digitalRead(RESET_BUTTON_PIN) == LOW) 
            {
              drawSomething("Отпустите кнопку для сброса...");
              delay(1000);
            }
            removeAllFiles(); // Выполняем сброс файлов
            ESP.restart(); // Перезагружаем устройство
        }
      delay(100);
    }
    buttonPressStartTime = 0; // Сбрасываем таймер, если кнопка отпущена
}