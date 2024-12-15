// ACTION - действия на странице
void action() {
  if (ui.click()) {
    ui.clickInt("slt_bellmode", bellmode); // + НАДО ЗВОНКИ МЕНЯТЬ, то есть при нажатии на эту шнягу идет обновление след. звонка
  }
  if (ui.update()) {
    String date = rtc.getDateString();
    String time = rtc.getTimeString();
    String status = bellStatus();
    ui.updateString("rtcdate", date);
    ui.updateString("rtctime", time);
    ui.updateString("lbl_bellstatus", status);
  }
  if (ui.form()) {
    if (ui.form("/rtcupdate")) {
      queueNTPupdate();                                                           
    }
    if (ui.form("/enablebell")) {
      enableBell();
    }
    if (ui.form("/cfgsave")) {
      configSet();
      ESP.restart();
    }
    if (ui.form("/stgsave")) {
      settingsSet();
      ESP.restart();
    }
  }
}