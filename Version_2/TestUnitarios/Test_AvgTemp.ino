// --- Media móvil temperatura ---
#define TEMP_HISTORY 10
float tempHistory[TEMP_HISTORY];
int tempIndex = 0;
bool tempFilled = false;
float tempMedia = 0.0;
float medias[3] = {0, 0, 0}; // para comprobar 3 medias consecutivas
int mediaIndex = 0;

void sendPacket(uint8_t type, const String &payload) {
  String msg = String(type) + ":" + payload;
  satSerial.println(msg);
  Serial.println("-> " + msg);
}

void updateTempMedia(float nuevaTemp) {
  tempHistory[tempIndex] = nuevaTemp;
  tempIndex = (tempIndex + 1) % TEMP_HISTORY;
  if (tempIndex == 0) tempFilled = true;

  int n = tempFilled ? TEMP_HISTORY : tempIndex;
  float suma = 0;
  for (int i = 0; i < n; i++) suma += tempHistory[i];
  tempMedia = suma / n;

  medias[mediaIndex] = tempMedia;
  mediaIndex = (mediaIndex + 1) % 3;

  // Si las tres últimas medias >100
  bool alerta = true;
  for (int i = 0; i < 3; i++) {
    if (medias[i] <= 100.0) alerta = false;
  }
  if (alerta) sendPacket(8, "e");  // ID 8 -> alerta alta temperatura
}

    //  if (now - lastSend >= sendPeriod) {
        // if (sending) {
           //  float h = dht.readHumidity();
          //  float t = dht.readTemperature();
          //  if (isnan(h) || isnan(t)) {
            //    sendPacket(4, "e:1");
            // } else {
              //  sendPacket(1, String((int)(h * 100)) + ":" + String((int)(t * 100))); //

                // --- calcular y enviar temperatura media ---
                updateTempMedia(t);
                sendPacket(7, String((int)(tempMedia * 100)));  // <== envío real de la media
                // ---------------------------------------------------

            }
