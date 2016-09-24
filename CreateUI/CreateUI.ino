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

/*
   Traditional Arduino setup routine

   Initialize the SimbleeForMobile environment.
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  // put your setup code here, to run once:
  SimbleeForMobile.deviceName = "Name";
  SimbleeForMobile.advertisementData = "Data";
  SimbleeForMobile.domain = "template.simblee.com";

  // Begin Simblee UI
  SimbleeForMobile.begin();
}

/*
   The traditional Arduino loop method

   Enable SimbleeForMobile functionality by calling the process method
   each time through the loop. This method must be called regularly for
   functionality to work.
 */
void loop() {
  // put your main code here, to run repeatedly:
  // process must be called in the loop for Simblee UI
  SimbleeForMobile.process();
}

/*
   SimbleeForMobile UI callback requesting the user interface
 */
void ui() {
  color_t grayBackgroundColor = rgb(128, 128, 128);
  SimbleeForMobile.beginScreen(grayBackgroundColor);

  ui_text = SimbleeForMobile.drawText(40, 30, "This is some text");
  ui_button = SimbleeForMobile.drawButton(120, 60, 100, "I'm a button!");
  ui_stepper = SimbleeForMobile.drawStepper(120, 110, 75, 0, 10);
  ui_textField = SimbleeForMobile.drawTextField(50, 180, 150, "I'm a text field! Write here!");
  ui_slider = SimbleeForMobile.drawSlider(50, 250, 180, 0, 30);
  ui_switch = SimbleeForMobile.drawSwitch(120, 300);
  ui_rectangle = SimbleeForMobile.drawRect(120, MAX_HEIGHT - 100, 80, 80, BLACK);

  const char* alice = "alice";
  const char* dave = "dave";
  const char* peter = "peter";
  const char* const segment_collection[3] = {alice, dave, peter};
  ui_segment = SimbleeForMobile.drawSegment(50, MAX_HEIGHT - 180, 200, segment_collection, 3);

  SimbleeForMobile.endScreen();
}

/*
   SimbleeForMobile event callback method
 */
void ui_event(event_t &event)
{
}


