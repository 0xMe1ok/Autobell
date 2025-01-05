const char* getDayOfWeek() {
  const char* daysOfWeek[] = {"ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС"};
  return daysOfWeek[ds.weekDay() - 1];
}

String daySecondsToHMS(int dayS) {
  int seconds = dayS % 60;
  int minutes = (dayS % 3600) / 60;
  int hours = dayS / 3600;

  return addZero(hours) + ":" + addZero(minutes) + ":" + addZero(seconds);
}

String addZero(int number) {
  return number < 10 ? ("0" + String(number)) : (String(number));
}

bool isNewDay(int currentDay, int previousDay) {
    return currentDay != previousDay;
}