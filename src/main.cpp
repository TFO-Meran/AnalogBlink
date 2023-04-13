#include <Arduino.h>
#include "IOHelper.h"

#define LED LED_BUILTIN
#define LED_GR 11
#define LED_RD 10
#define TESTOUT 2
#define TESTIN 3
#define BTN_1 8
#define BTN_2 7
#define POTI_1 A1
#define PWM_1 11

void setup()
{
    Serial.begin(57600);
    Serial.println("Analog-Test:");
    pinMode(LED, OUTPUT);
    pinMode(LED_GR, OUTPUT);
    pinMode(LED_RD, OUTPUT);
}

const uint16_t fadeMin = 100;
const uint16_t fadeMax = 2000;
uint8_t brightness = 0;
bool fadeUp = true;
unsigned long timeBefore = 0;
uint16_t timeUpdate = 1000; // Mikrosekunden

void loop()
{
    uint16_t val = analogRead(POTI_1);
    uint16_t diff = fadeMax - fadeMin;
    double faktor = diff / 1023.0;
    uint32_t zeit = (faktor * val + 100) * 1000;
    timeUpdate = (uint16_t)(zeit / 512);

    // Serial.println(zeit);

    if (micros() - timeBefore > timeUpdate)
    {
        if (brightness >= 255)
            fadeUp = false;
        else if (brightness <= 0)
            fadeUp = true;

        if (fadeUp)
            brightness++;
        else
            brightness--;

        timeBefore = micros();
    }

    analogWrite(PWM_1, brightness);
}

/////////////////////////////////////////

