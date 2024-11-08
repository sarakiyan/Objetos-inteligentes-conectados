// Bibliotecas
#include "DHT.h"
#include <WiFi.h>
#include <ThingSpeak.h>

// Credenciais do WiFi
const char* ssid = ""; // Add your WiFi network name
const char* password = ""; // Add your WiFi password 

// Credenciais do ThingSpeak
unsigned long channelID = ;
const char* writeAPIKey = "";
const char* readAPIKey = "";

// Endpoint do ThingSpeak
const char* server = "api.thingspeak.com";

// Definição do pino de leitura do sensor DHT11
#define DHTPIN 12
#define DHTTYPE DHT11
#define SENSOR_READ_TIME 1000  // Le o valor do sensores a cada 1 segundo

#define THINK_SPEAK_SEND_DATA_TIMEOUT 15000  // Envia o valor lido a cada 15 seconds (ThingSpeak has a 15-second update limit)
unsigned long previousMillis = 0;

// Inicialização do sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

// Inicialização do WiFi como cliente
WiFiClient client;

// Inicialização do LED atuador
#define RED_LED 13

float humidity;
float temperature;

// Initial temperature and humidity alarm values
float humidity_alarm = 90; 
float temperature_alarm = 30;

// Inicialização do WiFi
void setup_wifi() {
  Serial.println("\setup_wifi setup_wifi");

  delay(10);
  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


// Inicialização do sensor de DHT11 e dos leds
void setup() {
  Serial.begin(115200);

  // Define os leds
  pinMode(RED_LED, OUTPUT);

  // Inicializa o sensor DHT11
  dht.begin();
  Serial.println("DHT11 sensor initialized");

  // Setup WiFi
  setup_wifi();

  // Inicializa o ThingSpeak
  ThingSpeak.begin(client);
}

void read_sensor_data() {
  // Le o valor dos sensores de humidade e temperatura
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Printa o valor lido dos sensores na porta serial
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
}

// Envia os valor lido pelo sensor DHT11 para o ThinkSpeak
void publishSensorData() {
  // Define o valor dos campos de temperatura e humidade
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  // Envia o valor dos sensores para o ThinkSpeak
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("Channel update successful");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  }
}

void check_led_alarm () {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (humidity > humidity_alarm || temperature > temperature_alarm){
    Serial.println("Turn on alarm");
    digitalWrite(RED_LED, HIGH);
  } else {
    Serial.println("Turn off alarm");
    digitalWrite(RED_LED, LOW);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  // Verifica a conexão Wifi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    setup_wifi();
  }

  // Le os valores do sensores
  read_sensor_data();

  if (currentMillis - previousMillis >= THINK_SPEAK_SEND_DATA_TIMEOUT) {
    // Save the current time
    previousMillis = currentMillis;
    // Envia o valor lido pelos sensores para o ThinkSpeak a cada 15 segundos
    Serial.println("Try to send data to thinkSpeak");
    publishSensorData();
  }

  check_led_alarm();

  // Espera 15 segundos para enviar o proximo valor ao ThinkSpeak
  delay(SENSOR_READ_TIME);
}