#include <WiFi.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);

#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(LED_PIN, HIGH);
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(LED_PIN, LOW);
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    client.println("<h1>ESP32 LED Control</h1>");
    client.println("<a href=\"/LED=ON\"><button>ON</button></a>");
    client.println("<a href=\"/LED=OFF\"><button>OFF</button></a>");

    client.stop();
    Serial.println("Client disconnected");
  }
}