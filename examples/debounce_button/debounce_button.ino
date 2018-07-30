#include <Arduino.h>

#include "ESP8266DebounceButtons.h"

ESP8266DebounceButtons debounce;
uint8_t button7PressCount = 3;
void setup(){
  Serial.begin(115200);
  pinMode(D4,OUTPUT);

  debounce.addButtonPressPin(D3, [](uint16_t ms){
    digitalWrite(D4,!digitalRead(D4));
    Serial.printf("Button D3 Pressed for %d\n", ms);
    
  } );

  debounce.addButtonReleasePin(D7, [](uint16_t ms){
    Serial.printf("Button D7 Released for %d\n", ms);
    button7PressCount--;
    if(button7PressCount == 0){
      debounce.removeButtonReleasePin(D7);
      Serial.println("Button D7 removed from debouncer");
    }
  } );

  debounce.enable();

}

void loop(){
  debounce.update();
}