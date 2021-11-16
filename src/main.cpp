
#include <M5Core2.h>
#include <Wire.h>
#include "BME280.h"

BME280 bme280;

void setup(){
    M5.begin(true, true, true, false, kMBusModeOutput);
    Wire.begin(32, 33);

    pinMode(21, INPUT_PULLUP); //デファルトのSDAピン21　のプルアップの指定
    pinMode(22, INPUT_PULLUP); //デファルトのSCLピン22　のプルアップの指定

    bme280.begin(0x76); // BME280の初期化
    bme280.begin(0x77);

    Serial.printf("BME280 test\r\n"); // LCD display
}

void loop() {
    float temp, humid, pressure;

    // BME280で温度、湿度、気圧を測定する
    temp = (float)bme280.readTemperature(0x77);
    humid = (float)bme280.readHumidity(0x77);
    pressure = (float)bme280.readPressure(0x77);

    Serial.printf("0x77:");
    Serial.printf(" temp: %2.2f", temp);
    Serial.printf(" humid: %0.2f", humid);
    Serial.printf(" pressure: %f\r\n", pressure);

    temp = (float)bme280.readTemperature(0x76);
    humid = (float)bme280.readHumidity(0x76);
    pressure = (float)bme280.readPressure(0x76);

    Serial.printf("0x76:");
    Serial.printf(" temp: %2.2f", temp);
    Serial.printf(" humid: %0.2f", humid);
    Serial.printf(" pressure: %f\r\n", pressure);
    
    Serial.printf("-----------------------------------\n");
    delay(2000);
}