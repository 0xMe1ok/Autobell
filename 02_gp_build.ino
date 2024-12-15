#define UI_COLOR GP_BLUE

// BUILD - конструктор страницы
void build() {
  GP.BUILD_BEGIN(GP_DARK, 1920);
  GP.TITLE("Autobell 🔔");
  GP.NAV_TABS_LINKS("/,/settings,/config", "Главная,Настройки,Конфиг", UI_COLOR);

  if (ui.uri() == "/config") { // Конфиг

  GP.PAGE_TITLE("Autobell - Конфиг");

  GP.BOX_BEGIN();    

    GP.BLOCK_BEGIN(GP_TAB, "25%", "Настройка NTP-сервера 🕒", UI_COLOR);

      GP.LABEL("Часовой пояс: ");
      GP.TEXT("ntptimeoffset", "7", String(cfg.ntptimeoffset));

      GP.BREAK(); 

      GP.LABEL("NTP-хост: ");
      GP.TEXT("ntphost", "pool.ntp.org", cfg.ntphost);

    GP.BLOCK_END();

    GP.BLOCK_BEGIN(GP_TAB, "25%", "Настройка WiFi 🛜", UI_COLOR);

      GP.LABEL("Имя сети: ");
      GP.TEXT("wifi_ssid", "Имя сети", cfg.wifi_ssid);

      GP.BREAK(); 

      GP.LABEL("Пароль: ");
      GP.PASS("wifi_pass", "Пароль", cfg.wifi_pass);

    GP.BLOCK_END();

    GP.BLOCK_BEGIN(GP_TAB, "25%", "Настройка входа ⚙️", UI_COLOR);

      GP.LABEL("Логин: ");
      GP.TEXT("ui_login", "Логин", cfg.ui_login);
      GP.BREAK(); 

      GP.LABEL("Пароль: ");
      GP.PASS("ui_pass", "Пароль", cfg.ui_pass);

    GP.BLOCK_END();

    GP.BLOCK_BEGIN(GP_TAB, "25%", "Настройка пинов ⚡", UI_COLOR);

      GP.LABEL("Пин реле: ");
      GP.TEXT("relaypin", "Пин реле", String(cfg.relaypin));

      GP.BREAK(); 

      GP.LABEL("I2C SDA (Data): ");
      GP.TEXT("i2csda", "Пин данных RTC", String(cfg.i2csda));

      GP.BREAK(); 

      GP.LABEL("I2C SCL (Clock): ");
      GP.TEXT("i2cscl", "Пин такта RTC", String(cfg.i2cscl));

    GP.BLOCK_END();

    GP.BOX_END();

    GP.FORM_BEGIN("/cfgsave");
      GP.SUBMIT("Сохранить изменения", UI_COLOR);         
    GP.FORM_END();
    
  } else if (ui.uri() == "/settings" || ui.uri() == "/stgsave") { // Настройка

  GP.PAGE_TITLE("Autobell - Настройка");

  GP.BOX_BEGIN();

    GP.BLOCK_BEGIN(GP_TAB, "30%", "Выбор режима для дня недели", UI_COLOR);
      GP.LABEL("Понедельник: ");
      GP.SELECT("slct_bellmode_monday", "Выходной,Будний,Сокращенный,Праздник", daysofw.monday);
      GP.BREAK();

      GP.LABEL("Вторник: ");
      GP.SELECT("slct_bellmode_tuesday", "Выходной,Будний,Сокращенный,Праздник", daysofw.tuesday);
      GP.BREAK();

      GP.LABEL("Среда: ");
      GP.SELECT("slct_bellmode_wednesday", "Выходной,Будний,Сокращенный,Праздник", daysofw.wednesday);
      GP.BREAK();

      GP.LABEL("Четверг: ");
      GP.SELECT("slct_bellmode_thursday", "Выходной,Будний,Сокращенный,Праздник", daysofw.thursday);
      GP.BREAK();

      GP.LABEL("Пятница: ");
      GP.SELECT("slct_bellmode_friday", "Выходной,Будний,Сокращенный,Праздник", daysofw.friday);
      GP.BREAK();

      GP.LABEL("Суббота: ");
      GP.SELECT("slct_bellmode_saturday", "Выходной,Будний,Сокращенный,Праздник", daysofw.saturday);
      GP.BREAK();

      GP.LABEL("Воскресенье: ");
      GP.SELECT("slc_bellmode_sunday", "Выходной,Будний,Сокращенный,Праздник", daysofw.sunday);
    GP.BLOCK_END();

    GP.BLOCK_BEGIN(GP_TAB, "30%", "Звонки буднего дня", UI_COLOR); 
      for (int i = 1; i < kBellPairs + 1; i++) {
          String temp = (String)belltimeFile.get("weekday" + String(i));
          temp = correctTime(temp);
          GP.TIME("time_weekdays" + String(i), GPtime(temp));
          GP.LABEL(" - ");
          temp = (String)belltimeFile.get("weekday" + String(i));
          temp = correctTime(temp);
          GP.TIME("time_weekdays" + String(i + 1), GPtime(temp));
          GP.BREAK();
      }
    GP.BLOCK_END();  

    GP.BLOCK_BEGIN(GP_TAB, "30%", "Звонки сокращенного дня", UI_COLOR); 
      for (int i = 1; i < kBellPairs + 1; i++) {
          String temp = (String)belltimeFile.get("shortened" + String(i));
          temp = correctTime(temp);
          GP.TIME("time_shortened" + String(i), GPtime(temp));
          GP.LABEL(" - ");
          temp = (String)belltimeFile.get("shortened" + String(i + 1));
          temp = correctTime(temp);
          GP.TIME("time_shortened" + String(i + 1), GPtime(temp));
          GP.BREAK();
      }
    GP.BLOCK_END();  

    GP.BLOCK_BEGIN(GP_TAB, "30%", "Звонки праздничного дня", UI_COLOR); 
      for (int i = 1; i < kBellPairs + 1; i++) {
          String temp = (String)belltimeFile.get("holiday" + String(i));
          temp = correctTime(temp);
          GP.TIME("time_holiday" + String(i), GPtime(temp));
          GP.LABEL(" - ");
          temp = (String)belltimeFile.get("holiday" + String(i + 1));
          temp = correctTime(temp);
          GP.TIME("time_holiday" + String(i + 1), GPtime(temp));
          GP.BREAK();
      }
    GP.BLOCK_END();

    GP.BOX_END();

    GP.FORM_BEGIN("/stgsave");
      GP.SUBMIT("Сохранить изменения", UI_COLOR);         
    GP.FORM_END();

  } else { // Главная

    GP.PAGE_TITLE("Autobell - Главная");

    GP.UPDATE("rtcdate,rtctime,lbl_bellstatus");
    
    GP.LABEL("Статус: ");
    GP.LABEL("Звонок неактивен 🔕", "lbl_bellstatus");

    GP.FORM_BEGIN("/enablebell");     
        GP.SUBMIT("Включить звонок", UI_COLOR);         
    GP.FORM_END();

    GP.LABEL("Режим звонка: ");
    GP.SELECT("slt_bellmode", "Выходной,Будний,Сокращенный,Праздник", bellmode);

    GP.BLOCK_BEGIN(GP_TAB, "25%", "Данные времени", UI_COLOR);

      GP.LABEL("RTC: ");
      GP.LABEL(rtc.getDateString(), "rtcdate");
      GP.LABEL(rtc.getTimeString(), "rtctime");
      GP.LABEL(dayOfWeek(), "rtcday");
      
      GP.FORM_BEGIN("/rtcupdate");     
        GP.SUBMIT("Обновить время", UI_COLOR);         
      GP.FORM_END();

    GP.BLOCK_END();
  }

  GP.BUILD_END();
}