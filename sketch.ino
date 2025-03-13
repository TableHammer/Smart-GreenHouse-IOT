#define BLYNK_TEMPLATE_ID "TMPL5sTZChYmM"
#define BLYNK_TEMPLATE_NAME "Smart GreenHouse"
#define BLYNK_AUTH_TOKEN "Zd7w3yCRk8JtKai-L9ph6q7U9okpoWdR"

#include <DHTesp.h> 
#include <WiFi.h> 
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Wokwi-GUEST"; 

char pass[] = ""; 

const int DHT_PIN = 32;

DHTesp dhtSensor;
#define SOIL_MOISTURE_PIN 34
#define LED1 26  
#define LED2 14  
#define LED3 27
#define LED4 12
int SW_St1 = 0;
int SW_St2 = 0;
int SW_St3 = 0;
int SW_St4 = 0;
BlynkTimer timer;

BLYNK_WRITE (V3)
{
  SW_St1 = param.asInt();
  if (SW_St1 == 1)
  {
    digitalWrite(LED1, HIGH);
    Serial.println("RED ON");
    Blynk.virtualWrite(V3, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
    Serial.println("RED OFF");
    Blynk.virtualWrite(V3, LOW);
  }
}

BLYNK_WRITE (V4)
{
  SW_St2 = param.asInt();
  if (SW_St2 == 1)
  {
    digitalWrite(LED2, HIGH);
    Serial.println("Green ON");
    Blynk.virtualWrite(V4, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
    Serial.println("green OFF");
    Blynk.virtualWrite(V4, LOW);
  }
}

BLYNK_WRITE (V5)
{
  SW_St3 = param.asInt();
  if (SW_St3 == 1)
  {
    digitalWrite(LED3, HIGH);
    Serial.println("Yellow ON");
    Blynk.virtualWrite(V5, HIGH);
  }
  else
  {
    digitalWrite(LED3, LOW);
    Serial.println("Yellow OFF");
    Blynk.virtualWrite(V5, LOW);
  }
}

BLYNK_WRITE (V6)
{
  SW_St4 = param.asInt();
  if (SW_St4 == 1)
  {
    digitalWrite(LED4, HIGH);
    Serial.println("Blue ON");
    Blynk.virtualWrite(V6, HIGH);
  }
  else
  {
    digitalWrite(LED4, LOW);
    Serial.println("Blue OFF");
    Blynk.virtualWrite(V6, LOW);
  }
}


void setup() {
  Serial.begin(115200);
  Wire.begin(23, 22);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  lcd.init();
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
  Serial.println("Hello, ESP32!");
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);


  timer.setInterval(2500L, sendSensor);
}

void loop() {
  int16_t i = analogRead(34);
  String msg = i < 15 ? "Dry" : i > 40 ? "Wet" : "Good";
  lcd.clear();
  lcd.print("Soil TxT : ");
  lcd.print(msg);
  delay(500); 
  Blynk.run();
  timer.run();
}
void sendSensor() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  int t = data.temperature;
  float h = data.humidity;
  int sM = analogRead(SOIL_MOISTURE_PIN);


  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, sM);
  
  Serial.println("Temp: " + String(t) + "°C");
  Serial.println("Humidity: " + String(h) + "%");
  Serial.println("Soil Moisture: " + String(sM) + "%");

}

