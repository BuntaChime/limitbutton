#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "BluetoothSerial.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// GPIO where LED is connected to
// const int ledPin = 13;

// Handle received and sent messages
String message = "";
char incomingChar;

#define LED 13
BluetoothSerial BT;

void setup()
{
    Serial.begin(11520);   // Initializing serial connection for debugging
    BT.begin("BlewTewth"); // Name of your Bluetooth Device and in slave mode
    Serial.println("Bluetooth Device is Ready to Pair");
    pinMode(LED, OUTPUT); // Change the LED pin to OUTPUT

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    // Display static text
    Serial.println("Device started, now you can pair it with bluetooth!");
    display.println("Device started, now you can pair it with bluetooth!");
    display.display();
}
void loop()
{
    if (BT.available()) // Check if we receive anything from Bluetooth
    {
        int incoming = BT.read(); // Read what we receive
        Serial.print("Received: ");
        Serial.println(incoming);
        if (incoming == 49)
        {                                // 1 in ASCII
            digitalWrite(LED, HIGH);     // LED On
            BT.println("LED turned ON"); // Send the text via BT Serial
        }
        if (incoming == 48)
        {                                 // 0 in ASCII
            digitalWrite(LED, LOW);       // LED Off
            BT.println("LED turned OFF"); // Send the text via BT Serial
        }
    }
    delay(20);
}