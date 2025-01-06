// ACTION - действия на странице
void action() {
  // Обработка КЛИКОВ (обновлений значений полей ввода)
  int bellCount;
  int datesCount;

  if (ui.click()) {
    if (ui.click("BTN_SaveConfig")) {
      configFile.update();
      ESP.restart();
    }
    else if (ui.click("BTN_SaveSettings")) {
      bellModesFile.update();
      settingsFile.update();
      bellDatesFile.update();
      ESP.restart();
    }
    else if (ui.click("BTN_SaveBellTime")) {
      bellTimeFile.update();
      ESP.restart();
    }
    // Добавление/Удаление записи звонка в будний день
    else if (ui.click("BTN_Add_WeekdayBell")) {
      bellCount = bellTimeFile["Weekday_BellCount"];
      bellTimeFile["Weekday_BellCount"] = bellCount + 1;
      bellTimeFile["Weekday_" + String(bellCount + 1)] = GPtime();
    }
    else if (ui.click("BTN_Del_WeekdayBell")) {
      bellCount = bellTimeFile["Weekday_BellCount"];
      if (bellCount > 1) {
        bellTimeFile.remove("Weekday_" + String(bellCount));
        bellTimeFile["Weekday_BellCount"] = bellCount - 1;
      }
    }

    // Добавление/Удаление записи звонка в сокращенный день
    else if (ui.click("BTN_Add_ShortBell")) {
      bellCount = bellTimeFile["Short_BellCount"];
      bellTimeFile["Short_BellCount"] = bellCount + 1;
      bellTimeFile["Short_" + String(bellCount + 1)] = GPtime();
    }
    else if (ui.click("BTN_Del_ShortBell")) {
      bellCount = bellTimeFile["Short_BellCount"];
      if (bellCount > 1) {
        bellTimeFile.remove("Short_" + String(bellCount));
        bellTimeFile["Short_BellCount"] = bellCount - 1;
      }
    }

    // Добавление/Удаление записи звонка в праздничный день
    else if (ui.click("BTN_Add_HolidayBell")) {
      bellCount = bellTimeFile["Holiday_BellCount"];
      bellTimeFile["Holiday_BellCount"] = bellCount + 1;
      bellTimeFile["Holiday_" + String(bellCount + 1)] = GPtime();
    }
    else if (ui.click("BTN_Del_HolidayBell")) {
      bellCount = bellTimeFile["Holiday_BellCount"];
      if (bellCount > 1) {
        bellTimeFile.remove("Holiday_" + String(bellCount));
        bellTimeFile["Holiday_BellCount"] = bellCount - 1;
      }
    }

    // Добавление/Удаление записи Даты:Режима
    else if (ui.click("BTN_Add_Date")) {
      datesCount = bellDatesFile["DatesCount"];
      bellDatesFile["DatesCount"] = datesCount + 1;

      DateMode dm;
      dm.date = "01.01";
      dm.mode = 1;
      bellDatesFile["Date_" + String(datesCount + 1)] = dm;
    }
    else if (ui.click("BTN_Del_Date")) {
      datesCount = bellDatesFile["DatesCount"];
      if (datesCount > 0) {
        bellDatesFile.remove("Date_" + String(datesCount + 1));
        bellDatesFile["DatesCount"] = datesCount - 1;
      }
    }

    // Включение звонка
    else if (ui.click("BTN_EnableBell")) {
      enableBellForDuration();
    }

    // Обновление времени RTC-модуля
    else if (ui.click("BTN_RTC_Update")) {
      scheduledRTCUpdate();
    }

    // Обновление режима звонка
    else if (ui.clickInt("slt_bellmode", bellmode)) {
      nextBellTime = getNextBellTime();
      timeUntilBell = getTimeUntilBell();
    }
    // Сохранение значения для файла Config
    if (ui.clickSub("CFG")) {
      if (ui.clickNameSub(1) == "STR") {
        configFile[ui.clickNameSub(2)] = ui.getString();
      }
      if (ui.clickNameSub(1) == "INT") {
        configFile[ui.clickNameSub(2)] = ui.getInt();
      }
    }
    // Сохранение значения для файла bellModes
    else if (ui.clickSub("MOD")) {
      if (ui.clickNameSub(1) == "INT") {
        bellModesFile[ui.clickNameSub(2)] = ui.getInt();
      }
    }
    // Сохранение значения для файла bellTime
    else if (ui.clickSub("TIM")) {
      if (ui.clickNameSub(1) == "TIM") {
        bellTimeFile[ui.clickNameSub(2)] = ui.getTime();
      }
    }
    // Сохранение значения для файла bellDates
    else if (ui.clickSub("DAT")) {
      if (ui.clickNameSub(1) == "DAT") {
        GPdate selectedDate = ui.getDate();
        DateMode dm;

        bellDatesFile[ui.clickNameSub(2)].writeTo(dm);
        dm.date = selectedDate.encodeDMY().substring(0,5);

        bellDatesFile[ui.clickNameSub(2)] = dm;
      }
      if (ui.clickNameSub(1) == "INT") {
        int selectedMode = ui.getInt();
        DateMode dm;

        bellDatesFile[ui.clickNameSub(2)].writeTo(dm);
        dm.mode = selectedMode;

        bellDatesFile[ui.clickNameSub(2)] = dm;
      }
    }
    // Сохранение значения для файла Settings
    else if (ui.clickSub("SET")) {
      if (ui.clickNameSub(1) == "INT") {
        bellModesFile[ui.clickNameSub(2)] = ui.getInt();
      }
    }
  }
  if (ui.update()) {
    String dsDateTime = ds.toString();
    String dayOfWeek = getDayOfWeek();
    String nextBell = isNotMoreBelling() ? "Больше звонков сегодня не будет!" : daySecondsToHMS(nextBellTime);
    String untilBell = daySecondsToHMS(timeUntilBell);
    String bellStatus = isRinging ? "Звонок активен 🔔" : "Звонок неактивен 🔕";
    ui.updateString("LBL_RTC_DateTime", dsDateTime);
    ui.updateString("LBL_RTC_DayOfWeek", dayOfWeek);
    ui.updateString("LBL_NextBellTime", nextBell);
    ui.updateString("LBL_TimeUntilBell", untilBell);
    ui.updateString("LBL_BellStatus", bellStatus);
  }
}