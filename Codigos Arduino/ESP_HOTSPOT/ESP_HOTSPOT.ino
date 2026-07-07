#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "DSH";		 // CAMBIAR
const char* password = "9876543210";	 // CAMBIAR
WebServer server(80);

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html><head><meta charset="utf-8">
    <title>ESP32 Web Server</title>
    <style>body{font-family:Arial;text-align:center;padding:40px;background:#BFB3A4;}</style>
    </head><body>
      <h1>ESP32 - Access Point</h1>
      <p>Envíar un mensaje usando:</p>
      <p><code>http://192.168.4.1/update?msg=Mensaje aquí</code></p>
      <p>Clientes conectados: )rawliteral" + String(WiFi.softAPgetStationNum()) + R"rawliteral(</p>
    </body></html>
  )rawliteral";
  server.send(200, "text/html", html);
}
void handleUpdate() {
  if (server.hasArg("msg")) {
    String msg = server.arg("msg");
    Serial.println("MSG:" + msg);        // Formato claro para Flask
    server.send(200, "text/plain", "Mensaje recibido: " + msg);
  } else {
    server.send(400, "text/plain", "Falta el parámetro msg");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  
  Serial.println("\n=== ESP32 AP + Web Server ===");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/update", HTTP_GET, handleUpdate);
  
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();
}
