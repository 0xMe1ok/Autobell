void enableBellPlanned() {
  enableBell();
  OS.attach(0, disableBell, settingsFile[SH("BELL_RingingTime")]); // Добавление выключения звонка по таймауту времени звонка из настроек
}

void disableBellPlanned() {
  disableBell();
  OS.detach(0); // Удаление выключения звонка из очереди
}

void updateRTCPlanned() {
  OS.attach(1, updateNTPPlanned, 100); // Добавление обновления времени в очередь     
}

void updateNTPPlanned() {
  updateRTC();

  nextBellTime = getNextBellTime();
  timeUntilBell = getTimeUntilBell();

  OS.detach(1); // Удаление обновления времени из очереди     
}