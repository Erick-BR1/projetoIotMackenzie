import network
import time
from machine import Pin
import dht
import ujson
from umqtt.simple import MQTTClient

#Conexao com MQTT
MQTT_CLIENT_ID = "micropython-weather-demo"
MQTT_BROKER    = "broker.mqttdashboard.com"
MQTT_USER      = ""
MQTT_PASSWORD  = ""
MQTT_TOPIC     = "wokwiSensorTempHumiMackenzie"

#Pino de saido do sensor onde envia para o ESP
sensor = dht.DHT22(Pin(15))

#Conecta ao Wi-Fi
print("Conectando ao WI-Fi", end="")
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect('Wokwi-GUEST', '')
while not sta_if.isconnected():
  print(".", end="")
  time.sleep(0.1)
print(" Conectado!")

#Conecta com o MQTT, a partir dos parâmetros mostrados acima
print("Conectando ao servidor MQTT... ", end="")
client = MQTTClient(MQTT_CLIENT_ID, MQTT_BROKER, user=MQTT_USER, password=MQTT_PASSWORD)
client.connect()

print("Conectado!")

#Esse while serve para apresentar a temperatura e humidade
prev_weather = ""
while True:
  print("Medindo as condições do climáticas do local... ", end="")
  sensor.measure() 
  message = ujson.dumps({
    "temperatura": sensor.temperature(),
    "humidade": sensor.humidity(),
  })
  if message != prev_weather:
    print("Atualizado!")
    print("Reportando para o tópico MQTT {}: {}".format(MQTT_TOPIC, message))
    client.publish(MQTT_TOPIC, message)
    prev_weather = message
#Caso não tenha mudança ele entre neste ELSE e printa somente
  else:
    print("Sem mudanças")
  time.sleep(1)
