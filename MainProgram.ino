// M5Core2 - Version: Latest
#include <M5Core2.h>

/*
  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made

  int effectivereps;
  bool effectiveornot;
  int mvwifi;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include<M5Core2.h>
#include <Wire.h>
#include <EEPROM.h>
#if defined(ESP32)
#endif

#define TFTW            320     // screen width
#define TFTH            240     // screen height
#define TFTW2           160     // half screen width
#define TFTH2           120     // half screen height
#define bicepvolt       2000    // Voltage to be considered effective
#define squatvolt       1800    // Voltage to be considered effective

int address = 0;                          // Initialize the counter address to 0
int counter = EEPROM.readInt(address);    // Counter for the effective repetitions and store the value
double mv;                                //Milivolts

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  M5.begin();
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000);
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  for (int i = 0; i < 5; i++) {
    ArduinoCloud.update();            //connection to WIFI repeated
    delay(100);                       //to give a chance to connect
  }                                    //at the begining
  mainmenu();
}

void loop() {
  ArduinoCloud.update();
  Serial.println(analogRead (G35));   //Read the Analog values into the port G35
  //delay(10);
  mv = analogRead(G35);               //Store the value into mv
  mvwifi = mv;                        //Store and, thus, send the values of mv to mvwifi
  readata(bicepvolt);
}

void mainmenu() {
  M5.Lcd.fillScreen(TFT_BLACK);     //Set the screen with the black color
  M5.Lcd.fillRect(10, TFTH2 - 20, TFTW - 20, 1, TFT_WHITE); //Create a white rectangle from the point (10, TFTH2 - 20) to the point (TFTW-20, 1)
  M5.Lcd.fillRect(10, TFTH2 + 32, TFTW - 20, 1, TFT_WHITE); //Create a white rectangle from the point (10, TFTH2 + 32) to the point (TFTW-20, 1)
  M5.Lcd.setTextColor(TFT_WHITE); //Set the Text Color to white
  M5.Lcd.setTextSize(3); //Text size to 3
  // half width - num char * char width in pixels
  M5.Lcd.setCursor( TFTW2 - (3 * 9), TFTH2 - 16);
  M5.Lcd.println("FIT");
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor( TFTW2 - (3 * 9), TFTH2 + 8);
  M5.Lcd.println("PAL");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 10, TFTH2 - 36);
  M5.Lcd.println("M5Stack");
  M5.Lcd.setCursor( TFTW2 - (17 * 9), TFTH2 + 36);
  M5.Lcd.println("Smart Fitness Device");
  while (1) {
    // wait for push B button
    if (M5.BtnB.wasPressed()) {
      break;
    }
    M5.update();
  }
}

void readata(int voltage) {
  if (analogRead (G35) > voltage) {    //Voltage where the exercice is effective
    M5.Lcd.fillScreen(GREEN);       //Set screen to green
    displaydata(mv);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setFreeFont(FMB18);
    M5.Lcd.drawString("EFFECTIVE", 100, 50);
    counter++;                    // Add 1 to the counter value
    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.setCursor( TFTW2, TFTH2);
    M5.Lcd.print(counter);
    effectivereps = counter;    // Store the counter data into effectivereps
    effectiveornot = true;      // Initialize the state of effectiveornot to true
    vibrate();
    delay(600);                 // little delay to allow the person to finish the movement

  }
  else {
    M5.Lcd.fillScreen(RED);
    displaydata(mv);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setFreeFont(FMB18);
    M5.Lcd.drawString("NOT EFFECTIVE", 30, 50);
    effectiveornot = false;   //// Initialize the state of effectiveornot to false
  }
}
void vibrate() {
  M5.Axp.SetLDOEnable(3, true);  //Open the vibration.
  delay(200);
  M5.Axp.SetLDOEnable(3, false);  //Open the vibration.
  delay(1);
}

void displaydata(int mv1)
{
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.drawString("Voltage", 30, 160);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB18);
  M5.Lcd.drawNumber(mv1, 30, 190);
  M5.Lcd.setFreeFont(FMB12);
  M5.Lcd.drawString("mV", 120, 190);
  M5.Lcd.setTextSize(1);
}

void onEffectiverepsChange() {

}
void onEffectiveornotChange() {

}
void onMvwifiChange() {

}
