***Leitura de qualidade da água com sensor de turbidez***


***Breve Descrição do Funcionamento e Uso***

Este projeto tem como objetivo monitorar a qualidade da água através de um sensor de turbidez, conectando-se à internet via Wi-Fi com o módulo ESP8266 (por exemplo, ESP-01 ou NodeMCU).
Os dados lidos são enviados para um broker MQTT que pode ser acessado remotamente para visualizar os valores e o estado da água.

O projeto pode ser utilizado por escolas, estações de tratamento de água, projetos ambientais, ou mesmo projetos educacionais com foco nos Objetivos de Desenvolvimento Sustentável (ODS), especialmente o ODS 6 - Água potável e saneamento.


 ***Descrição do Hardware Utilizado***

 | Componente                      | Descrição                                                 |
| ------------------------------- | --------------------------------------------------------- |
| **ESP8266** (ESP-01 ou NodeMCU) | Módulo Wi-Fi com microcontrolador para conexão à internet |
| **Sensor de Turbidez**          | Sensor analógico que mede a transparência da água         |
| **Resistores**                  | Usados para limitar corrente do sensor                    |
| **Protoboard e Jumpers**        | Para montagem rápida do circuito                          |
| **Fonte de Alimentação 5V**     | Pode ser via USB ou adaptador externo                     |



***Documentação das Interfaces, Protocolos e Módulos de Comunicação***


• Interface de Comunicação Wi-Fi

    Conexão via SSID e senha do roteador

• Protocolo MQTT

     Utiliza o protocolo MQTT (Message Queuing Telemetry Transport)
     Porta: 1883 (sem TLS)
     Tópico publicado: sensor/turbidez
     Payload: mensagem JSON com a turbidez e o estado

• json

      {
        "turbidez": 720,
        "estado": "Água limpa"
      }

• Broker utilizado

    possum.lmq.cloudamqp.com (pode ser substituído por outro)
    Requer usuário e senha

• Serial

    Comunicação com monitor serial a 9600 bps para depuração local


***Comunicação/Controle via Internet e Uso do Protocolo MQTT***

• O projeto é controlado e monitorado via internet. Os dados são

    Enviados por Wi-Fi do ESP8266 para um broker MQTT externo
    Publicados em tempo real, podendo ser consumidos por dashboards como Node-RED, MQTT Explorer, IoT platforms (ex: Ubidots, ThingsBoard) ou aplicativos móveis

Essa arquitetura permite telemetria remota, integração com alertas, dashboards e até automação de ações (como acionar uma bomba ou enviar alerta caso a água esteja muito suja).
