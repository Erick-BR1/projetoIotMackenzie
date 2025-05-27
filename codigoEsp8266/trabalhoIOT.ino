#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configurações do WiFi
const char* ssid = "Jonisfreide";
const char* password = "Ticolitle69.";

// Configurações do broker MQTT
const char* mqtt_server = "possum.lmq.cloudamqp.com";
const int mqtt_port = 1883;
const char* mqtt_user = "qbbqncsk";
const char* mqtt_pass = "pJJrbUVyW3xrgtj2ghor4FEFlsuTfBgl";
const char* mqtt_topic = "possum.lmq.cloudamqp.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    client.connect("ESP01Client", mqtt_user, mqtt_pass);
  }
}

void setup() {
  Serial.begin(9600); // Lê dados do Arduino pela UART
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Serial.available()) {
    String valor = Serial.readStringUntil('\n');
    client.publish("sensor/turbidez", valor.c_str());
  }

int turbidez = analogRead(turbidezPin);
  String estado;

  if (turbidez > 700) {
    estado = "Água limpa";
  } else if (turbidez > 600) {
    estado = "Água um pouco suja";
  } else {
    estado = "Água muito suja";
  }

  Serial.print("Turbidez: ");
  Serial.print(turbidez);
  Serial.print(" | Estado: ");
  Serial.println(estado);

  // Publica no MQTT
  String mensagem = "{\"turbidez\":" + String(turbidez) + ",\"estado\":\"" + estado + "\"}";
  client.publish(mqtt_topic, mensagem.c_str());

  delay(2000);  // Espera 2 segundos antes da próxima leitura
}