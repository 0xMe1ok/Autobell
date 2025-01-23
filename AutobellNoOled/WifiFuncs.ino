void wifiAP() {
  wifiConnected = false;
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Autobell");
  delay(2000);
}