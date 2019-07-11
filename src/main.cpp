#include <Arduino.h>

#define LED_PIN_RED   3
#define LED_PIN_GREEN 5
#define LED_PIN_BLUE  6

int red = 255, green = 255, blue = 255;


char command_buffer[30];
int command_len = 0;

void setLed(int r, int g, int b);
void getRGBfromText(char text[]);
void task_blink(long period);
void task_terminal(long period);

void setup() 
{
    Serial.begin(115200);

    pinMode(LED_PIN_RED, OUTPUT);
    pinMode(LED_PIN_GREEN, OUTPUT);
    pinMode(LED_PIN_BLUE, OUTPUT);

    setLed(red, green, blue);
}


void loop() 
{
    task_terminal(20);
    task_blink(500);

}



void setLed(int r, int g, int b)
{
    analogWrite(LED_PIN_RED, r);
    analogWrite(LED_PIN_GREEN, g);
    analogWrite(LED_PIN_BLUE, b);
}



void getRGBfromText(char text[])
{
    int i = 0, len = 0;

    while (text[len] != '\0') {
        len++;
    }

    red = 0;
    for (i = 0; i < command_len; i++) {
        if (text[i] != ' ') {
            red = (red * 10) + (text[i] - '0');
        }
        else {
            break;
        }
    }
    i++;

    green = 0;
    for (   ; i < command_len; i++) {
        if (text[i] != ' ') {
            green = (green * 10) + (text[i] - '0');
        }
        else {
            break;
        }
    }
    i++;

    blue = 0;
    for (   ; i < command_len; i++) {
        if (text[i] != '\0') {
            blue = (blue * 10) + (text[i] - '0');
        }
        else {
            break;
        }
    }

    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);
}



void task_blink(long period)
{
    static long ref_time = millis();
    static int x = 0;

    if (millis() - ref_time >= period) {

       if (x == 0) {
            setLed(red, green, blue);
            x = 1;
        }
        else {
            setLed(0, 0, 0);
            x = 0;
        }

       ref_time += period;
    }
}


void task_terminal(long period)
{
    static long ref_time = millis();

    if (millis() - ref_time >= period) {

      if (Serial.available() > 0) {
            char c = Serial.read();

            if (c == '\r' || c == '\n') {
                if (command_len > 0){ 
                    Serial.println("ENTER");

                    command_buffer[command_len] = '\0';
                    Serial.print("command = ");
                    Serial.println(command_buffer);

                    getRGBfromText(command_buffer);
                    
                    command_len = 0;
                } 
            }
            else {
                command_buffer[command_len] = c;
                command_len++;
                
                Serial.print("len = ");
                Serial.println(command_len);
            }
        }

       ref_time += period;
    }
}
