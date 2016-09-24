/*
   Copyright (c) 2015 RF Digital Corp. All Rights Reserved.

   The source code contained in this file and all intellectual property embodied in
   or covering the source code is the property of RF Digital Corp. or its licensors.
   Your right to use this source code and intellectual property is non-transferable,
   non-sub licensable, revocable, and subject to terms and conditions of the
   SIMBLEE SOFTWARE LICENSE AGREEMENT.
http://www.simblee.com/licenses/SimbleeSoftwareLicenseAgreement.txt

THE SOURCE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND.

This heading must NOT be removed from this file.
 */

#include <SimbleeForMobile.h>

#define MAX_HEIGHT SimbleeForMobile.screenHeight
#define MAX_WIDTH SimbleeForMobile.screenWidth

uint8_t ui_button;
uint8_t ui_text;
uint8_t ui_textField;
uint8_t ui_switch;
uint8_t ui_segment;
uint8_t ui_slider;
uint8_t ui_stepper;
uint8_t ui_rectangle;

/***
* Extra stuff
***/
uint8_t text_temp;
String textFieldString = "";
unsigned long lastUpdated = 0;
unsigned long updateRate = 500; // in milliseconds

// include newlib printf float support (%f used in sprintf below)
asm(".global _printf_float");

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  SimbleeForMobile.deviceName = "Name";
  SimbleeForMobile.advertisementData = "Data";
  SimbleeForMobile.domain = "template.simblee.com";

  SimbleeForMobile.begin();
}

void loop() {
  unsigned long loopTime = millis();

  if (SimbleeForMobile.updatable && updateRate < (loopTime - lastUpdated)) { 
    lastUpdated = loopTime;
    
    float temp = Simblee_temperature(CELSIUS);

    char buf[16];
    sprintf(buf, "%02f", temp);
    SimbleeForMobile.updateText(text_temp, buf);
  }

  SimbleeForMobile.process();
}

void ui() {
  color_t grayBackgroundColor = rgb(128, 128, 128);
  SimbleeForMobile.beginScreen(grayBackgroundColor);

  ui_text = SimbleeForMobile.drawText(40, 30, "This is some text");
  ui_button = SimbleeForMobile.drawButton(120, 60, 100, "I'm a button!");
  ui_stepper = SimbleeForMobile.drawStepper(120, 110, 75, 0, 30);
  ui_textField = SimbleeForMobile.drawTextField(50, 180, 150, "I'm a text field! Write here!");
  ui_slider = SimbleeForMobile.drawSlider(50, 250, 180, 0, 30);
  ui_switch = SimbleeForMobile.drawSwitch(120, 300);
  ui_rectangle = SimbleeForMobile.drawRect(120, MAX_HEIGHT - 100, 80, 80, BLACK);

  const char* alice = "alice";
  const char* dave = "dave";
  const char* peter = "peter";
  const char* const segment_collection[3] = {alice, dave, peter};
  ui_segment = SimbleeForMobile.drawSegment(50, MAX_HEIGHT - 180, 200, segment_collection, 3);

  
  text_temp = SimbleeForMobile.drawText(40, 10, "Simblee Temperature");
  SimbleeForMobile.setEvents(ui_button, EVENT_PRESS);  

  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event) { 

  if (event.id == ui_button && event.type == EVENT_PRESS) {
    SimbleeForMobile.updateText(ui_text, textFieldString.c_str());
  } else if (event.id == ui_stepper) {
    SimbleeForMobile.updateValue(ui_slider, event.value);
  } else if (event.id == ui_switch) {
    if (event.value == 0) {
      SimbleeForMobile.updateText(ui_text, "Switch off");
    } else if (event.value == 1) {
      SimbleeForMobile.updateText(ui_text, "Switch on");
    }
  } else if (event.id == ui_segment) {
    switch (event.value) {
      case 0:
        SimbleeForMobile.updateText(ui_text, "Alice text");
        break;

      case 1:
        SimbleeForMobile.updateText(ui_text, "Dave text");
        break;

      case 2:
        SimbleeForMobile.updateText(ui_text, "Peter text");
        break;
    }
  } else if (event.id == ui_textField) { 
    textFieldString = String(event.text);
  }
}


