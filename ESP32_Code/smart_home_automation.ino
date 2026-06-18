#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>

BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Relay Pins
#define RELAY1 26
#define RELAY2 27
#define BUZ 14

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_HOME");  // Bluetooth Name
  Serial.println("Bluetooth Started");

  lcd.init();
  lcd.backlight();

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(BUZ, OUTPUT);

  // Turn OFF all loads initially (1-level relay)
  digitalWrite(RELAY1, 0);
  digitalWrite(RELAY2, 0);
  digitalWrite(BUZ, 0);

  lcd.setCursor(0, 0);
  lcd.print("welcome to the");
  lcd.setCursor(0, 1);
  lcd.print("   project   ");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("voice ctrl home");
  lcd.setCursor(0, 1);
  lcd.print("   appliences   ");
  delay(2000);
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.print("Waiting for CMD");
  delay(1000);
  lcd.clear();
  if (SerialBT.available()) {
    lcd.clear();
    char cmd = SerialBT.read();
    Serial.println(cmd);
    
    lcd.setCursor(0, 0);
    lcd.print("Rcv cmd: ");
    lcd.print(cmd);

    switch (cmd) {

      case '1':  // LOAD 1 ON

        lcd.setCursor(0, 1);
        lcd.print("LIGHT ON      ");
        digitalWrite(RELAY1, 1);
        digitalWrite(BUZ, 1);
        delay(1000);
        digitalWrite(BUZ, 0);
        break;

      case '2':  // LOAD 1 OFF
        lcd.setCursor(0, 1);
        lcd.print("LIGHT OFF     ");
        digitalWrite(RELAY1, 0);
        break;

      case '3':  // LOAD 2 ON
        
        lcd.setCursor(0, 1);
        lcd.print("FAN ON      ");
        digitalWrite(RELAY2, 1);
        digitalWrite(BUZ, 1);
        delay(1000);
        digitalWrite(BUZ, 0);
        break;

      case '4':  // LOAD 2 OFF
        lcd.setCursor(0, 1);
        lcd.print("Load2 off      ");
        digitalWrite(RELAY2, 0);
        break;

      case '5':  // LOAD 3 ON
        
        lcd.setCursor(0, 1);
        lcd.print("All Loads ON      ");
        digitalWrite(RELAY1, 1);
        digitalWrite(RELAY2, 1);
        digitalWrite(BUZ, 1);
        delay(1000);
        digitalWrite(BUZ, 0);
        break;

      case '6':  // LOAD 3 OFF
        lcd.setCursor(0, 1);
        lcd.print("All Loads OFF      ");
        digitalWrite(RELAY1, 0);
        digitalWrite(RELAY2, 0);
        break;


      default:
        lcd.print("Rcv cmd: ");
        lcd.print("      ");
        lcd.setCursor(0, 1);
        lcd.print("Loads             ");
        break;
    }
  }
}
