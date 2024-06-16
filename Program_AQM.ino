//------------------------------------------------------------------------------------------------------------------
// Untuk Blynk
#define BLYNK_TEMPLATE_ID "TMPL6Na7NKuwz"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitoring"
#define BLYNK_AUTH_TOKEN "vjcwEZKOruI6e-FupiGQ2wm_6nuhlqoO"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "XxX";
char pass[] = "12345678";

//------------------------------------------------------------------------------------------------------------------
// Untuk sensor DHT 22
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

//------------------------------------------------------------------------------------------------------------------
// Untuk sensor MQ-135
#define MQPIN A0

//------------------------------------------------------------------------------------------------------------------
// Untuk sensor PM 2.5

//------------------------------------------------------------------------------------------------------------------
// Untuk variabel
float suhu, kelembapan;
int gas;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Untuk memulai serial monitor
  dht.begin(); // Untuk memulai sensor DHT 22
  pinMode(MQPIN, INPUT); // Untuk mendeklarasikan sensor MQ-135 sebagai input
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Untuk memulai Blynk
}

void sensor_dht(){
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  Serial.println("Hasil Pengukuran Sensor DHT 22 : ");
  Serial.print("Suhu = ");
  Serial.print(suhu);
  Serial.println(" °C");
  Serial.print("Kelembapan : ");
  Serial.print(kelembapan);
  Serial.println(" %");
}

void sensor_mq(){
  gas = analogRead(MQPIN);
  Serial.println("Hasil Pengukuran Sensor MQ-135 : ");
  Serial.print("Konsentrasi gas = ");
  Serial.println(gas);
}

void blynk(){
  Blynk.run();
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, gas);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_dht();
  sensor_mq();
  blynk();
  delay(1000);
}
