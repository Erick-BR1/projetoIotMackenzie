// Bibliotecas
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configurações do WiFi
const char* ssid = "inheritance";
const char* password = "Bliat.";

// Configurações do broker MQTT
const char* mqtt_server = "possum.lmq.cloudamqp.com";
const int mqtt_port = 1883;
const char* mqtt_user = "qbbqncsk";
const char* mqtt_pass = "pJJrbUVyW3xrgtj2ghor4FEFlsuTfBgl";
const char* mqtt_topic = "sensor/turbidez";

// Pino do sensor de turbidez
const int turbidezPin = A0;

// Objetos WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Conexão com o WiFi
void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

// Reconexão com o broker MQTT
void reconnect() {
  while (!client.connected()) {
    client.connect("ESP01Client", mqtt_user, mqtt_pass);
  }
}

void setup() {
  Serial.begin(9600); // Comunicação serial com o Arduino
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Verifica a conexão MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura serial (se estiver recebendo dados de outro dispositivo)
  if (Serial.available()) {
    String valor = Serial.readStringUntil('\n');
    client.publish("sensor/turbidez", valor.c_str());
  }

  // Leitura do sensor de turbidez
  int turbidez = analogRead(turbidezPin);
  String estado;

  if (turbidez > 700) {
    estado = "Água limpa";
  } else if (turbidez > 600) {
    estado = "Água um pouco suja";
  } else {
    estado = "Água muito suja";
  }

  // Exibe no monitor serial
  Serial.print("Turbidez: ");
  Serial.print(turbidez);
  Serial.print(" | Estado: ");
  Serial.println(estado);

  // Publica no tópico MQTT
  String mensagem = "{\"turbidez\":" + String(turbidez) + ",\"estado\":\"" + estado + "\"}";
  client.publish(mqtt_topic, mensagem.c_str());

  delay(2000);  // Espera 2 segundos antes da próxima leitura
}
