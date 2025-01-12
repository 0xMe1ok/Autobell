void checkResetButton() {
    if (digitalRead(RESET_BUTTON_PIN) == LOW) { // Кнопка нажата (если кнопка замыкает на GND)
        if (buttonPressStartTime == 0) {
            buttonPressStartTime = millis(); // Фиксируем момент начала нажатия
        } else if (millis() - buttonPressStartTime >= resetHoldDuration) {
            removeAllFiles(); // Выполняем сброс файлов
            ESP.restart(); // Перезагружаем устройство
        }
    } else {
        buttonPressStartTime = 0; // Сбрасываем таймер, если кнопка отпущена
    }
}