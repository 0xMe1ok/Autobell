void enableBell() {
  isRinging = true;
  digitalWrite(RELAY_PIN, HIGH);
}

void disableBell() {
  isRinging = false;
  digitalWrite(RELAY_PIN, LOW);
}

int getCurrentBellMode() {
  const int datesCount = bellDatesFile[SH("DatesCount")];
  String currDate = ds.dateToString().substring(0,5);
  for (int i = 1; i <= datesCount; i++) {
    DateMode dm;
    bellDatesFile["Date_" + String(i)].writeTo(dm);
    if (currDate == dm.date) {
      return dm.mode;
    }
  }
  return bellModesFile["D" + String(ds.weekDay())].toInt(); // Иначе - вернуть режим по текущему дню
}

bool isNotMoreBelling() {
  return nextBellTime == NOT_MORE_BELLING;
}

int getNextBellTime() {
  const int currTime = ds.daySeconds();
  if (bellmode == Weekend) {
    return NOT_MORE_BELLING;
  }
  else if (bellmode == Workday) {
    const int bellCount = bellTimeFile[SH("Weekday_BellCount")];
    for (int i = 1; i <= bellCount; i++) {
      GPtime gptime;
      bellTimeFile["Weekday_" + String(i)].writeTo(gptime);
      const int bellTime = gptime.second + (gptime.minute * 60) + (gptime.hour * 3600); // to DaySeconds
      if (bellTime > currTime) {
        return bellTime;
      }
    }
  }
  else if (bellmode == Shortened) {
    const int bellCount = bellTimeFile[SH("Short_BellCount")];
    for (int i = 1; i <= bellCount; i++) {
      GPtime gptime;
      bellTimeFile["Short_" + String(i)].writeTo(gptime);
      const int bellTime = gptime.second + (gptime.minute * 60) + (gptime.hour * 3600); // to DaySeconds
      if (bellTime > currTime) {
        return bellTime;
      }
    }
  }
  else if (bellmode == Holiday) {
    const int bellCount = bellTimeFile[SH("Holiday_BellCount")];
    for (int i = 1; i <= bellCount; i++) {
      GPtime gptime;
      bellTimeFile["Holiday_" + String(i)].writeTo(gptime);
      const int bellTime = gptime.second + (gptime.minute * 60) + (gptime.hour * 3600); // to DaySeconds
      if (bellTime > currTime) {
        return bellTime;
      }
    }
  }
  return NOT_MORE_BELLING;
}

int getTimeUntilBell() {
  if (isNotMoreBelling()) return 0;
  const int currTime = ds.daySeconds();
  return nextBellTime - currTime;
}

bool isTimeToBell() {
  if (isNotMoreBelling()) return false;
  const int currTime = ds.daySeconds();
  return currTime >= nextBellTime;
}