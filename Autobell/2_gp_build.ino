#define UI_COLOR GP_BLUE

// BUILD - конструктор страницы
void build() {
  GP.BUILD_BEGIN(GP_DARK, 1920);
  GP.RELOAD_CLICK("BTN_SaveConfig,BTN_SaveSettings,BTN_SaveBellTime,BTN_Add_WeekdayBell,BTN_Del_WeekdayBell,BTN_Add_ShortBell,BTN_Del_ShortBell,BTN_Add_HolidayBell,BTN_Del_HolidayBell,BTN_Add_Date,BTN_Del_Date");
  GP.TITLE("Autobell 🔔");
  GP.NAV_TABS_LINKS("/,/settings,/belltimeWeekdays,/config", "Главная,Настройки звонков,Время звонков,Конфигурация", UI_COLOR);

  if (ui.uri() == "/config") { // Конфиг

  GP.NAV_TABS_LINKS("/config,/configNTP,/configUIAuth,/configOTA", "WiFi,NTP-сервер,Авторизация,OTA обновление");

  GP.PAGE_TITLE("Autobell - Конфиг WIFI");
 
  GP.BLOCK_BEGIN(GP_TAB, "100%", "Настройка WiFi 🛜", UI_COLOR);
    GP.LABEL("Имя сети: ");
    GP.TEXT("CFG/STR/WiFi_SSID", "Имя сети", configFile["WiFi_SSID"]);
    GP.BREAK(); 
    GP.LABEL("Пароль: ");
    GP.PASS("CFG/STR/WiFi_PASS", "Пароль", configFile["WiFi_PASS"]);
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveConfig", "Сохранить изменения");
    
  } else if (ui.uri() == "/configNTP") { // Конфиг

  GP.NAV_TABS_LINKS("/config,/configNTP,/configUIAuth,/configOTA", "WiFi,NTP-сервер,Авторизация,OTA обновление");

  GP.PAGE_TITLE("Autobell - Конфиг NTP");

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Настройка NTP-сервера 🕒", UI_COLOR);
    GP.LABEL("Часовой пояс: ");
    GP.NUMBER("CFG/INT/NTP_TimeOffset", "например: 1, или же -1", configFile["NTP_TimeOffset"]);
    GP.BREAK(); 
    GP.LABEL("NTP-хост: ");
    GP.TEXT("CFG/STR/NTP_Host", "pool.ntp.org", configFile["NTP_Host"]);
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveConfig", "Сохранить изменения");

  } else if (ui.uri() == "/configUIAuth") { // Конфиг

  GP.NAV_TABS_LINKS("/config,/configNTP,/configUIAuth,/configOTA", "WiFi,NTP-сервер,Авторизация,OTA обновление");

  GP.PAGE_TITLE("Autobell - Конфиг авторизации");

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Настройка входа ⚙️", UI_COLOR);
    GP.LABEL("Логин: ");
    GP.TEXT("CFG/STR/UI_Login", "Логин", configFile["UI_Login"]);
    GP.BREAK(); 
    GP.LABEL("Пароль: ");
    GP.PASS("CFG/STR/UI_Pass", "Пароль", configFile["UI_Pass"]);
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveConfig", "Сохранить изменения");

  } else if (ui.uri() == "/configOTA") { // Конфиг

  GP.NAV_TABS_LINKS("/config,/configNTP,/configUIAuth,/configOTA", "WiFi,NTP-сервер,Авторизация,OTA обновление");

  GP.PAGE_TITLE("Autobell - OTA обновление");

  GP.BLOCK_BEGIN(GP_TAB, "100%", "OTA обновление", UI_COLOR);
    GP.OTA_FIRMWARE();
    GP.OTA_FILESYSTEM();
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveConfig", "Сохранить изменения");

  } else if (ui.uri() == "/settings") { // Настройка

  GP.PAGE_TITLE("Autobell - Настройка режима на неделю");
  GP.NAV_TABS_LINKS("/settings,/settingsDates,/settingsDuration", "Дни недели,Даты,Длительность");

  int tempBM; // temp bell mode
  GP.BLOCK_BEGIN(GP_TAB, "100%", "Выбор режима для дня недели", UI_COLOR);
    GP.LABEL("Понедельник: ");
    tempBM = bellModesFile[SH("D1")];
    GP.SELECT("MOD/INT/D1", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
    GP.BREAK();

    GP.LABEL("Вторник: ");
    tempBM = bellModesFile[SH("D2")];
    GP.SELECT("MOD/INT/D2", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
    GP.BREAK();

    GP.LABEL("Среда: ");
    tempBM = bellModesFile[SH("D3")];
    GP.SELECT("MOD/INT/D3", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
    GP.BREAK();

    GP.LABEL("Четверг: ");
    tempBM = bellModesFile[SH("D4")];
    GP.SELECT("MOD/INT/D4", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
    GP.BREAK();

    GP.LABEL("Пятница: ");
    tempBM = bellModesFile[SH("D5")];
    GP.SELECT("MOD/INT/D5", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
    GP.BREAK();

    GP.LABEL("Суббота: ");
    tempBM = bellModesFile[SH("D6")];
    GP.SELECT("MOD/INT/D6", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
    GP.BREAK();

    GP.LABEL("Воскресенье: ");
    tempBM = bellModesFile[SH("D7")];
    GP.SELECT("MOD/INT/D7", "Выходной,Рабочий,Сокращенный,Праздник", tempBM);
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveSettings", "Сохранить изменения");

  } else if (ui.uri() == "/settingsDates") { // Настройка

  GP.PAGE_TITLE("Autobell - Настройка дат");
  GP.NAV_TABS_LINKS("/settings,/settingsDates,/settingsDuration", "Дни недели,Даты,Длительность");

  int datesCount = bellDatesFile["DatesCount"];
  int currYear = ds.year();

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Даты с опред. режимом звонка", UI_COLOR); 
    for (int i = 1; i <= datesCount; i++) {
        DateMode datemode;
        bellDatesFile["Date_" + String(i)].writeTo(datemode);

        const int currDay = datemode.date.substring(0, 2).toInt();
        const int currMonth = datemode.date.substring(3, 5).toInt();
        GPdate gpdat;
        gpdat.day = currDay;
        gpdat.month = currMonth;
        gpdat.year = currYear;

        GP.DATE("DAT/DAT/Date_" + String(i), gpdat);
        GP.LABEL(" - ");
        GP.SELECT("DAT/INT/Date_" + String(i), "Выходной,Рабочий,Сокращенный,Праздник", datemode.mode);
        GP.BREAK();
    }
    GP.BUTTON("BTN_Add_Date", "+");
    if (datesCount >= 1) GP.BUTTON("BTN_Del_Date", "-");
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveSettings", "Сохранить изменения");

  } else if (ui.uri() == "/settingsDuration") { // Настройка

  GP.PAGE_TITLE("Autobell - Настройка длительности звонка");
  GP.NAV_TABS_LINKS("/settings,/settingsDates,/settingsDuration", "Дни недели,Даты,Длительность");

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Длительность звонка", UI_COLOR); 
    GP.NUMBER("SET/INT/BELL_RingingTime", "5000, мс", settingsFile["BELL_RingingTime"]);
    GP.LABEL(" мс");
  GP.BLOCK_END();    

  GP.BUTTON("BTN_SaveSettings", "Сохранить изменения");

  } else if (ui.uri() == "/belltimeWeekdays") {

  GP.PAGE_TITLE("Autobell - Настройка времени звонков");
  GP.NAV_TABS_LINKS("/belltimeWeekdays,/belltimeShort,/belltimeHolidays", "Рабочие,Сокращенные,Праздники");

  const int weekdayBellCount = bellTimeFile["Weekday_BellCount"];

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Звонки рабочего дня", UI_COLOR); 
    for (int i = 1; i <= weekdayBellCount; i++) {
      GPtime time;
      bellTimeFile["Weekday_" + String(i)].writeTo(time);
      GP.TIME("TIM/TIM/Weekday_" + String(i), time);

      if (i % 2 == 1 && i != weekdayBellCount) {
        GP.LABEL(" - ");
      } else {
        GP.BREAK();
      }
    }
    GP.BUTTON("BTN_Add_WeekdayBell", "+");
    if (weekdayBellCount > 1) GP.BUTTON("BTN_Del_WeekdayBell", "-");
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveBellTime", "Сохранить изменения");

  } else if (ui.uri() == "/belltimeShort") {

  GP.PAGE_TITLE("Autobell - Настройка времени звонков");
  GP.NAV_TABS_LINKS("/belltimeWeekdays,/belltimeShort,/belltimeHolidays", "Будни,Сокращенные,Праздники");

  const int shortBellCount = bellTimeFile["Short_BellCount"];

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Звонки сокращенного дня", UI_COLOR); 
    for (int i = 1; i <= shortBellCount; i++) {
      GPtime time;
      bellTimeFile["Short_" + String(i)].writeTo(time);
      GP.TIME("TIM/TIM/Short_" + String(i), time);

      if (i % 2 == 1 && i != shortBellCount) {
        GP.LABEL(" - ");
      } else {
        GP.BREAK();
      }
    }
    GP.BUTTON("BTN_Add_ShortBell", "+");
    if (shortBellCount > 1) GP.BUTTON("BTN_Del_ShortBell", "-");
  GP.BLOCK_END();  

  GP.BUTTON("BTN_SaveBellTime", "Сохранить изменения");

  } else if (ui.uri() == "/belltimeHolidays") {

  GP.PAGE_TITLE("Autobell - Настройка времени звонков");
  GP.NAV_TABS_LINKS("/belltimeWeekdays,/belltimeShort,/belltimeHolidays", "Будни,Сокращенные,Праздники");

  const int holidayBellCount = bellTimeFile["Holiday_BellCount"];

  GP.BLOCK_BEGIN(GP_TAB, "100%", "Звонки праздничного дня", UI_COLOR); 
    for (int i = 1; i <= holidayBellCount; i++) {
      GPtime time;
      bellTimeFile["Holiday_" + String(i)].writeTo(time);
      GP.TIME("TIM/TIM/Holiday_" + String(i), time);

      if (i % 2 == 1 && i != holidayBellCount) {
        GP.LABEL(" - ");
      } else {
        GP.BREAK();
      }
    }
    GP.BUTTON("BTN_Add_HolidayBell", "+");
    if (holidayBellCount > 1) GP.BUTTON("BTN_Del_HolidayBell", "-");
  GP.BLOCK_END();

  GP.BUTTON("BTN_SaveBellTime", "Сохранить изменения");

  } else { // Главная

    GP.PAGE_TITLE("Autobell - Главная");
    GP.UPDATE("LBL_RTC_DateTime,LBL_RTC_DayOfWeek,LBL_BellStatus,LBL_NextBellTime,LBL_TimeUntilBell");
    
    GP.BLOCK_BEGIN(GP_TAB, "100%", "Данные о звонке", UI_COLOR);
      GP.LABEL("Статус: ");
      String bellStatus = isRinging ? "Звонок активен 🔔" : "Звонок неактивен 🔕";
      GP.LABEL(bellStatus, "LBL_BellStatus");
      GP.BREAK();

      GP.LABEL("Режим звонка: ");
      GP.SELECT("SEL_BellMode", "Выходной,Рабочий,Сокращенный,Праздник", bellmode);
      GP.BREAK();

      GP.LABEL("Следующий звонок в:");
      String nextBell = isNotMoreBelling() ? "Больше звонков сегодня не будет!" : daySecondsToHMS(nextBellTime);
      GP.LABEL(nextBell, "LBL_NextBellTime");
      GP.BREAK();

      GP.LABEL("Время до следующего звонка:");
      String untilBell = daySecondsToHMS(timeUntilBell);
      GP.LABEL(untilBell, "LBL_TimeUntilBell");
      GP.BREAK();
        
      GP.BUTTON("BTN_EnableBell", "Включить звонок");
    GP.BLOCK_END();

    GP.BLOCK_BEGIN(GP_TAB, "100%", "Данные времени", UI_COLOR);
      GP.LABEL("RTC: ");
      GP.LABEL(ds.toString(), "LBL_RTC_DateTime");
      GP.LABEL(getDayOfWeek(), "LBL_RTC_DayOfWeek");
      GP.BREAK();
      
      GP.BUTTON("BTN_RTC_Update", "Обновить по NTP-серверу");
      GP.BUTTON("BTN_RTC_Update_UI", "Обновить времени с устройства");
    GP.BLOCK_END();
  }

  GP.BUILD_END();
}