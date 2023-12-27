#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// GPIO where LED is connected to
const int ledPin = 13;

// Handle received and sent messages
String message = "";
char incomingChar;

BluetoothSerial SerialBT;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("BlewTewth"); // Bluetooth device name
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  // Display static text
  Serial.println("The device started, now you can pair it with bluetooth!");
  display.println("The device started, now you can pair it with bluetooth!");
  display.display();
}

void loop()
{
  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }
  delay(20);

  // Read received messages (LED control command)
  if (SerialBT.available())
  {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n')
    {
      message += String(incomingChar);
    }
    else
    {
      message = "";
    }
    Serial.write(incomingChar);
  }
  // Check received message and control output accordingly
  if (message == "led_on")
  {
    digitalWrite(ledPin, HIGH);
  }
  else if (message == "led_off")
  {
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}