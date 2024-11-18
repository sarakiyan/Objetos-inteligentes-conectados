 # Monitoramento Inteligente de Infraestrutura de Torres de Telecomunicações 
 
Este projeto propõe uma solução de IoT para o monitoramento de infraestrutura de telecomunicações utilizando ESP32, sensor DHT11 e LED. Ele coleta dados de temperatura e umidade em tempo real, envia-os para a plataforma ThingSpeak via protocolo MQTT e aciona um alerta visual quando valores predefinidos são excedidos.

## Código e Documentação

O código principal está disponível na pasta do repositório `projeto_esp32.ino` e foi desenvolvido na Arduino IDE. O arquivo principal inclui:

- Configuração da conexão Wi-Fi.
- Configuração do protocolo MQTT.
- Funções para leitura do sensor DHT11, Controle do LED com base em limites predefinidos.  

### Hardware

- **Placa ESP32**: Gerencia a coleta de dados e a comunicação com a internet.  
- **Sensor DHT11**: Mede temperatura e umidade do ambiente.  
- **LED com resistor de 68 Ohms**: Sinalizador visual para alertas de valores fora dos limites configurados.  

### Interfaces e Protocolos de Comunicação

O sistema utiliza o protocolo MQTT para comunicação com a plataforma ThingSpeak. Os seguintes tópicos MQTT são usados:  

- **Temperatura**: Envia leituras de temperatura.  
- **Umidade**: Envia leituras de umidade.  
- **Controle do LED**: Gerencia o acionamento do LED com base nos dados do sensor.  
 
Os tópicos são atualizados automaticamente em intervalos regulares de 15 segundos.

### Controle e Comunicação via Internet

A comunicação do sistema é feita pela rede Wi-Fi (TCP/IP) e utiliza o protocolo MQTT para transmissão eficiente de dados. A configuração inclui:  

- **Credenciais do Wi-Fi**: Configure `wifi_ssid` e `wifi_password` para conectar à rede local.  
- **Configuração do ThingSpeak**: Insira a chave API e os feeds para autenticação e envio de dados.  
- **Feeds MQTT no ThingSpeak**: Configure canais para temperatura e umidade, permitindo a visualização remota.  
