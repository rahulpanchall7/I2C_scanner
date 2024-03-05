#include <Wire.h>
#include <stdio.h>
#include "sdkconfig.h"
#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  delay(2000);

  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int devices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      devices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("Done\n");
  }

  delay(5000);  // Wait 5 seconds before scanning again
}
