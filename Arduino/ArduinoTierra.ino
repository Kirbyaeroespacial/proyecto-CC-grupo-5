#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX (azul, blanco)
int errpin = 2;
unsigned long lastReceived = 0;  // Último tiempo en que se recibieron datos
const unsigned long timeout = 5000; // 5 segundos de timeout

void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   Serial.println("Estacion Tierra lista reenviando USB <-> mySerial");
   pinMode (errpin, OUTPUT);
}
void loop() {
  if (Serial.available()){
    String command = Serial.readStringUntil('\n');
    command.trim();//Quitar elementos invisibles.
    if (command.length() > 0){
      mySerial.println(command);
      Serial.println("Comando enviado");
    }
    
    }
  if (mySerial.available()) {
      String data = mySerial.readStringUntil("\n!");
      data.trim();//Quitar elementos invisibles.
      Serial.println(data);
      
      if (data.length() > 0){
          if(data.equals("e")){
            digitalWrite(errpin, HIGH);
            delay (500);
            digitalWrite(errpin, LOW);
            delay(1);
          }
        else{
          Serial.println(data);
        }
        lastReceived = millis();
      }
  }
  if (millis() - lastReceived > timeout){
      digitalWrite(errpin, HIGH);
      delay(100);
      digitalWrite(errpin, LOW);
      delay(50);
    }
}
