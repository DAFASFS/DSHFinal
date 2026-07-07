#include <WiFi.h>

const char* ssid = "DSH";
const char* password = "9876543210";

// IP fija ESP32 #3
IPAddress local_IP(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Servidor TCP
WiFiServer server(12346);
WiFiClient clientePython;

// Pines LEDs
const int LED_ROJO = 25;
const int LED_AMARILLO = 26;
const int LED_VERDE = 27;

void apagarLeds() {
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void actualizarLeds(float temperatura) {
  apagarLeds();

  if (temperatura < 25.0) {
    digitalWrite(LED_VERDE, HIGH);
    Serial.println("Estado: NORMAL - LED VERDE");
  } 
  else if (temperatura >= 25.0 && temperatura < 30.0) {
    digitalWrite(LED_AMARILLO, HIGH);
    Serial.println("Estado: MEDIO - LED AMARILLO");
  } 
  else {
    digitalWrite(LED_ROJO, HIGH);
    Serial.println("Estado: ALTO - LED ROJO");
  }
}

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
  Serial.println("ESP32 #3 conectado correctamente");
  Serial.print("IP ESP32 #3: ");
  Serial.println(WiFi.localIP());
}

void procesarDato(String data) {
  data.trim();

  Serial.print("Dato recibido: ");
  Serial.println(data);

  if (data.startsWith("TEMP:")) {
    String valor = data.substring(5);
    float temperatura = valor.toFloat();

    Serial.print("Temperatura recibida: ");
    Serial.println(temperatura);

    actualizarLeds(temperatura);

    if (clientePython && clientePython.connected()) {
      clientePython.println("OK");
    }
  } else {
    Serial.println("Formato incorrecto");

    if (clientePython && clientePython.connected()) {
      clientePython.println("ERROR");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  apagarLeds();

  conectarWiFi();

  server.begin();

  Serial.println("Servidor TCP ESP32 #3 iniciado en puerto 12346");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Reconectando...");
    conectarWiFi();
  }

  if (!clientePython || !clientePython.connected()) {
    clientePython = server.available();

    if (clientePython) {
      Serial.println("Python conectado al ESP32 #3");
    }
  }

  if (clientePython && clientePython.connected() && clientePython.available()) {
    String data = clientePython.readStringUntil('\n');
    procesarDato(data);
  }
}