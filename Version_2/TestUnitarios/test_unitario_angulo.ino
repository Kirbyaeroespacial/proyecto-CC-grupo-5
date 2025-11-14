#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial satSerial(10, 11); // RX=10, TX=11
const uint8_t servoPin = 8;
const int potPin = A0;
Servo motor;

const int angles[] = {0, 90, 180};
const int N_ANGLES = sizeof(angles)/sizeof(angles[0]);
const int TOL = 8;        // tolerancia (grados)
const unsigned long WAIT_MS = 350;

void sendPacket(uint8_t type, const String &payload) {
  satSerial.println(String(type) + ":" + payload);
  Serial.println(String(type) + ":" + payload);
}

int readPotAngle() {
  int adc = analogRead(potPin);
  return map(adc, 0, 1023, 0, 180); // si calibras, cambia 0/1023
}

void runTestOnce() {
  for (int i = 0; i < N_ANGLES; ++i) {
    int target = angles[i];
    motor.write(target);
    delay(WAIT_MS);
    int measured = readPotAngle();
    String res = (abs(measured - target) <= TOL) ? "PASS" : "FAIL";
    sendPacket(6, "test:" + String(target) + ":" + String(measured) + ":" + res);
    delay(120);
  }
}

void setup() {
  Serial.begin(9600);
  satSerial.begin(9600);
  motor.attach(servoPin);
  motor.write(90);
  delay(500);
  runTestOnce(); // test inicial
}

void loop() {
  if (satSerial.available()) {
    String c = satSerial.readStringUntil('\n');
    c.trim();
    if (c == "7:t") runTestOnce();
  }
  if (Serial.available()) {
    String c = Serial.readStringUntil('\n');
    c.trim();
    if (c == "7:t") runTestOnce();
  }
  delay(20);
}
