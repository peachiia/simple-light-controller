#include <Arduino.h>


long int ref_time = 0;
long int period = 1000;
int i = 0;

long int ref_time_2 = 0;
long int period_2 = 200;
int x = 0;

void setup() 
{
    Serial.begin(115200);
    ref_time = millis();
    ref_time_2 = millis();
}

void loop() 
{
    if (millis() - ref_time >= period) {
        Serial.print("i = ");
        Serial.println(i);
        i++;
        ref_time += period;
    }

    if (millis() - ref_time_2 >= period_2) {
        Serial.print("x = ");
        Serial.println(x);
        x++;
        ref_time_2 += period_2;
    }

}