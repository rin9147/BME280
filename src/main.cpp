
#include <M5Core2.h>
#include <Wire.h>
#include "BME280.h"
#include "Adafruit_MPL3115A2.h"

const float seaPressure = 1021.4;

float distance_referBaro = 0;
float referenceAltitudeMPL = 0;
float referenceAltitudeBME = 0;
float temp, pressure, altitude;

BME280 bme280;
Adafruit_MPL3115A2 baro;


void setup(){
    M5.begin(true, true, true, false, kMBusModeOutput);
    Wire.begin(32, 33);

    pinMode(21, INPUT_PULLUP); //デファルトのSDAピン21　のプルアップの指定
    pinMode(22, INPUT_PULLUP); //デファルトのSCLピン22　のプルアップの指定

    //bme280.begin(0x77); // BME280の初期化
    baro.begin();
    baro.setSeaPressure(seaPressure);
    bme280.begin(0x76);

    referenceAltitudeMPL = baro.getAltitude();
    temp = (float)bme280.readTemperature(0x76);
    pressure = (float)bme280.readPressure(0x76);
    referenceAltitudeBME = (pow(seaPressure/pressure,1/5.257)-1)*(temp+273.15)/0.0065;
}

void loop() {
    m5.Lcd.setCursor(0,0);
    /*
    // BME280で温度、湿度、気圧を測定する
    temp = (float)bme280.readTemperature(0x77);
    humid = (float)bme280.readHumidity(0x77);
    pressure = (float)bme280.readPressure(0x77);

    Serial.printf("0x77:");
    Serial.printf(" temp: %2.2f", temp);
    Serial.printf(" humid: %0.2f", humid);
    Serial.printf(" pressure: %f\r\n", pressure);
    delay(1000);
    */
    pressure = baro.getPressure();
    altitude = baro.getAltitude();
    temp = baro.getTemperature();
    distance_referBaro = (altitude - referenceAltitudeMPL) / sin(35 * 3.141592 / 180);
    
    Serial.printf("MPL:");
    Serial.printf(" temp: %2.2f", temp);
    Serial.printf(" pressure: %f", pressure);
    Serial.printf(" altitude: %0.2f", altitude);
    Serial.printf(" distance: %0.2f\r\n", distance_referBaro);
    M5.Lcd.println("MPL:");
    M5.Lcd.printf(" temp: %2.2f\n", temp);
    M5.Lcd.printf(" pressure: %f\n", pressure);
    M5.Lcd.printf(" altitude: %0.2f\n", altitude);
    M5.Lcd.printf(" distance: %0.2f\n", distance_referBaro);
    
    

    temp = (float)bme280.readTemperature(0x76);
    pressure = (float)bme280.readPressure(0x76);
    altitude = (pow(seaPressure/pressure,1/5.257)-1)*(temp+273.15)/0.0065;
    distance_referBaro = (altitude - referenceAltitudeBME) / sin(35 * 3.141592 / 180);

    Serial.printf("BME:");
    Serial.printf(" temp: %2.2f", temp);
    Serial.printf(" pressure: %f", pressure);
    Serial.printf(" altitude: %0.2f", altitude);
    Serial.printf(" distance: %0.2f\r\n", distance_referBaro);

    M5.Lcd.println("BME:");
    M5.Lcd.printf(" temp: %2.2f\n", temp);
    M5.Lcd.printf(" pressure: %f\n", pressure);
    M5.Lcd.printf(" altitude: %0.2f\n", altitude);
    M5.Lcd.printf(" distance: %0.2f\n", distance_referBaro);
    
    Serial.printf("-----------------------------------\n");
    delay(1000);
    M5.Lcd.clear();
}