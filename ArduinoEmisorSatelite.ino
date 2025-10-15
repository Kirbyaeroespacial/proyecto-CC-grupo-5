#include <DHT.h>
#include <SoftwareSerial.h>

// Pines del DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pines SoftwareSerial (TX del emisor → RX del receptor)
SoftwareSerial mySerial(10, 11); // RX no usado, TX conectado al otro Arduino

// Pin del LED
#define LEDPIN 12  // Cambiado a pin 12

void setup() {
  Serial.begin(9600);       // Monitor serie para depuración
  mySerial.begin(9600);     // Comunicación con otro Arduino
  dht.begin();              // Inicializa DHT11
  pinMode(LEDPIN, OUTPUT);  // Configura el LED como salida
  Serial.println("Iniciando prueba DHT11 con LED...");
 
}

void loop() {
  delay(2000); // Espera 2 segundos entre lecturas

  int h = dht.readHumidity()*100;
  int t = dht.readTemperature()*100; //para que pesen menos los datos ponemos int y tenemos los dats enteros con todas los numeros sin perder datos

  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    // Crear línea de datos
    String data = String(h) + ":" + String(t);

    // Enviar datos
    Serial.println(data);    // Monitor serie
    mySerial.println(data);  // Arduino receptor

    // LED parpadea al enviar datos
    digitalWrite(LEDPIN, HIGH); // LED encendido
    delay(200);                  // 200 ms
    digitalWrite(LEDPIN, LOW);   // LED apagado
  }
}
