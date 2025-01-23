void checkResetButton() {
    while (digitalRead(RESET_BUTTON_PIN) == LOW) { // Кнопка нажата (если кнопка замыкает на GND)
        if (millis() - buttonPressStartTime >= kResetHoldDuration) {
            while (digitalRead(RESET_BUTTON_PIN) == LOW) 
            {
              delay(1000);
            }
            removeAllFiles(); // Выполняем сброс файлов
            ESP.restart(); // Перезагружаем устройство
        }
      delay(100);
    }
    buttonPressStartTime = 0; // Сбрасываем таймер, если кнопка отпущена
}