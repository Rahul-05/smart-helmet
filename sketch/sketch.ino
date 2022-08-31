#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"

int16_t val=0,val1=0;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

Adafruit_SSD1306 display(-1);

void setup()   
{                
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
//  display.println("Hello world!");
  display.display();
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(val,0);
//    display.println("Hello World");
    display.println((char)SerialBT.read());
    val=val+7;
    if(val>=12){
      val1=val1+15;
      val=0;
    }
    display.setCursor(val,val1);
    display.display();
  }
//  Serial.write(val1);
//  display.clearDisplay();
//  delay(2000);
}
