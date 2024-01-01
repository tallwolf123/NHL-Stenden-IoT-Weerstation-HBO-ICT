#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

//voor het scherm
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//voor de temperatuur en luchtvochtigheidsensor
#define DHTPIN 2 
#define DHTTYPE    DHT22
DHT dht(DHTPIN, DHTTYPE);

//zorgt voor interval tussen verschillende schermen
int draw_state = 0;


void setup() {
  Serial.begin(115200);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();

}

void loop() {
  //haalt de data op
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  //zorgt ervoor dat de draw_state oploopt
  draw_state++;
  //reset de draw_state
 if ( draw_state > 3  ){
    draw_state = 0;
  }
  // wisselt draw_state na delay
  delay(1500);

  switch(draw_state) {
    case 0:
      display.clearDisplay(); 
      display.setTextSize(1);
      display.setCursor(10,0);
      display.print("Luchtvochtigheid");
      display.setTextSize(1);
      display.setCursor(110,0);
      display.print("2/4");
      display.setTextSize(2);
      display.setCursor(56,32);
      display.print(h, 1);
      display.setTextSize(2);
      display.setCursor(110,32);
      display.print("%");
      break;
    case 2:
      display.clearDisplay(); 
      display.drawCircle(107, 30, 3, WHITE);
      display.setTextSize(1);
      display.setCursor(30,0);
      display.print("Temperatuur");
      display.setTextSize(1);
      display.setCursor(110,0);
      display.print("1/4");
      display.setTextSize(2);
      display.setCursor(112,32);
      display.print("C");
      display.setTextSize(2);
      display.setCursor(56,32);
      display.print(t, 1); 
      break;
  }

   //tekent een lijn en zorgt ervoor dat het scherm aangaat
   display.drawLine(0,10,128,10, WHITE);
   display.display();

}
