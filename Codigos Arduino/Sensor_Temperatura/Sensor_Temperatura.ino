#include <WiFi.h>
#include "DHT.h"

const char* ssid = "DSH";
const char* password = "9876543210";

// IP fija del ESP32 sensor dentro de la red del hotspot principal
IPAddress local_IP(192, 168, 4, 2);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Servidor TCP del ESP32 sensor
WiFiServer server(12345);

// Configuración DHT11
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void conectarWiFi() {
  WiFi.mode(WIFI_STA);

  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  Serial.print("Conectando a red WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado correctamente");
  Serial.print("IP del ESP32 sensor: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  conectarWiFi();

  server.begin();

  Serial.println("Servidor TCP iniciado en puerto 12345");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Reconectando...");
    conectarWiFi();
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Cliente Python conectado");

    float temperatura = dht.readTemperature();

    if (isnan(temperatura)) {
      Serial.println("Error al leer temperatura DHT11");
      client.println("ERROR:DHT11");
    } else {
      String data = "TEMP:" + String(temperatura, 2);

      client.println(data);

      Serial.println("Enviado a Python: " + data);
    }

    delay(100);
    client.stop();

    Serial.println("Cliente Python desconectado");
  }
}