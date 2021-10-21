#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define SUBSCRIBE "EnvCourierMQTT"
#define PUBLISH   "RecCourierMQTT"
#define IDMQTT  "IDCourier"
#define MDIRETO     D0
#define MESQUERDO   D1
#define ECHOPIN     D3
#define TRIGGERPIN  D4

#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1 

long duracao = 0;
int distancia = 0;
 
const char* SSID = "Gabriel";
const char* PASSWORD = "99@E@123";
const char* BROKER_MQTT = "mqtt.eclipseprojects.io";
int PORTA_BROKER = 1883;

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoMDireto = '0';
char EstadoMEsquerdo = '0';

int calcDistancia(){
    digitalWrite(TRIGGERPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGERPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGERPIN, LOW);
    duracao = pulseIn(ECHOPIN, HIGH);
    distancia= duracao*0.034/2;
    return distancia;
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String command;
    int distancia_l = calcDistancia();
    for(int i = 0; i < length; i++) 
    {
       char p = (char)payload[i];
       command += p;
    }
    if (distancia_l <=5){
      digitalWrite(MDIRETO, LOW);
          digitalWrite(MESQUERDO, LOW);
    
          EstadoMDireto = '0';
          EstadoMEsquerdo = '0';
    }
    else
    {

      if (command.equals("F"))
      {
          digitalWrite(MDIRETO, HIGH);
          digitalWrite(MESQUERDO, HIGH);
    
          EstadoMDireto = '1';
          EstadoMEsquerdo = '1';
      }
   
      if (command.equals("D"))
      {
          digitalWrite(MDIRETO, LOW);
          digitalWrite(MESQUERDO, HIGH);
    
          EstadoMDireto = '0';
          EstadoMEsquerdo = '1';
      }
   
      if (command.equals("E"))
      {
          digitalWrite(MDIRETO, HIGH);
          digitalWrite(MESQUERDO, LOW);
    
          EstadoMDireto = '1';
          EstadoMEsquerdo = '0';
      }
   
      if (command.equals("P"))
      {
          digitalWrite(MDIRETO, LOW);
          digitalWrite(MESQUERDO, LOW);
    
          EstadoMDireto = '0';
          EstadoMEsquerdo = '0';
      }
    }
}

void initMQTT() {
    MQTT.setServer(BROKER_MQTT, PORTA_BROKER);
    MQTT.setCallback(mqtt_callback);
}

void reconnectMQTT() {
    while (!MQTT.connected()) {

        Serial.print("* Tentando se conectar com MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(IDMQTT)) 
        {
            Serial.println("Conectado ao MQTT!");
            MQTT.subscribe(SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Erro de reconexão com Broker.");
            Serial.println("Tentando outra vez em 3s...");
            delay(3000);
        }
    }
}
  
void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conexão realizada! SSID: ");
    Serial.print(SSID);
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
}
 
void conexaoWiFI_MQTT(void) {
    if (!MQTT.connected())
        reconnectMQTT();
    reconectWiFi();
}
 
void EnviaMQTT(void) {
    char EstadoMotor[3];
 
    EstadoMotor[0] = EstadoMDireto;
    EstadoMotor[1] = '-';
    EstadoMotor[2] = EstadoMEsquerdo;
 
    MQTT.publish(PUBLISH, EstadoMotor);
    Serial.println("- no Broker!");
    delay(1000);
}

void initWiFi();
void initMQTT();
void reconectWiFi();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void conexaoWiFI_MQTT(void);

void initWiFi() {
    delay(10);
    Serial.println("------ Conexao -----");
    Serial.print("Rede: ");
    Serial.println(SSID);
    Serial.println("Um momento...");
     
    reconectWiFi();
}

void setup() {
    pinMode(MDIRETO, OUTPUT);
    pinMode(MESQUERDO, OUTPUT);
    pinMode(TRIGGERPIN, OUTPUT);
    pinMode(ECHOPIN, INPUT);

    digitalWrite(MDIRETO, LOW);
    digitalWrite(MESQUERDO, LOW);
    Serial.begin(115200);

    initWiFi();
    initMQTT();
}

void loop() {
    conexaoWiFI_MQTT();
 
    EnviaMQTT();

    delay(50);
    distancia = calcDistancia();
    Serial.println("Distância do Obstáculo: ");
    Serial.print(distancia);
    Serial.print(" cm.");
    delay(50);
 
    MQTT.loop();
}
