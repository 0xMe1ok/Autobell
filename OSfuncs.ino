void enableBellForDuration() {
  enableBell();
  OS.attach(0, disableBellProcess, settingsFile[SH("BELL_RingingTime")]); // Добавление выключения звонка по таймауту времени звонка из настроек
}

void disableBellProcess() {
  disableBell();
  OS.detach(0); // Удаление выключения звонка из очереди
}

void scheduledRTCUpdate() {
  OS.attach(1, RTCUpdateProcess, 100); // Добавление обновления времени в очередь     
}

void RTCUpdateProcess() {
  updateRTCFromNTP();

  nextBellTime = getNextBellTime();
  timeUntilBell = getTimeUntilBell();

  OS.detach(1); // Удаление обновления времени из очереди     
}