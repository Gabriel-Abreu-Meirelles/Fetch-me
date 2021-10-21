<h1>Projeto Fetch-Me, robo de controle remoto por mqtt</h1>

<p>Olá! Meu nome é Gabriel de Abreu Meirelles e este é o Fetch-Me, projeto entregue para a disciplina de Objetos Inteligentes Conectados, do curso de Análise e desenvolvimento de sistemas, da Universidade Presbiteriana Mackenzie.
O projeto consiste no controle de um carrinho de duas rodas através da internet, utilizando o protocolo MQTT, para isso utilizaremos um ESP8266, um sensor de distância ultrassônico que adaptamos para ser uma medida de segurança e demais componentes que podem ser encontrados na lista de materiais mais abaixo.</p>
<h3>Para a elaboração do projeto foi utilizado como base:</h3>

<p>- "um carro de controle remoto" do site <a href="https://www.filipeflop.com/blog/robo-iot-com-esp8266-nodemcu/">"filipeflop"</a></p>

<h4>Para a demonstração do uso do protocolo mqtt no projeto foi utilizado o client <a  href="https://mosquitto.org/">mosquitto</a></h4>

<h2>Documentação das principais tecnologias, protocolos e bibliotecas utilizadas:</h2>
<h4>Módulos de hardware:</h4>
- <a href="https://github.com/ekstrand/ESP8266wifi">Plataforma NodeMCU;</a><br>
- <a href="https://www.arduino.cc/reference/en/libraries/hcsr04-ultrasonic-sensor/">sensor ultrassônico HC-sr04;</a><br>
- <a href="https://components101.com/switches/5v-dual-channel-relay-module-pinout-features-applications-working-datasheet">Modulo relé.</a>
<h4>Bibliotecas:</h4>
- <a href="https://github.com/ekstrand/ESP8266wifi">ESP8266WiFi;</a><br>
- <a href="https://github.com/knolleary/pubsubclient">PubSubClient;</a>
<h4>Mosquitto:</h4>
- <a href="https://mosquitto.org/">Mosquitto;</a></h4>
<h4>Protocolo MQTT:</h4>
- <a href="https://github.com/ekstrand/ESP8266wifi">MQTT versão 3.1.1;</a>
<h4>Arduino IDE:</h4>
- <a href="https://www.arduino.cc/en/main/documentation">Arduino IDE.</a>

<h2>Lista de Materiais:</h2>

- Módulo WiFi ESP8266 NodeMCU ESP-12;
- Sensor de Distância Ultrassônico HC-SR04;
- Módulo Relé 5V com 2 canais;
- Protoboard com 400 pontos;
- Kit Chassi 2wd;
- conjunto de jumpers macho-macho;
- conjunto de jumpers macho-fêmea;
- 4 pilhas AA;
- regulador de tensão 7805;
- 2 transistores;
- 2 resistores de 220 ohms;
- 2 resistores de 2200 ohms.

<p>Os componentes devem ser conectados de acordo com o esquema do sistema:</p>
<img src="IOT-esquema com sensor.png">
