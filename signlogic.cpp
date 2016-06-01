#include <Adafruit_NeoPixel.h>

#define PIN            8
#define NUMPIXELS      12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int photocellPin = A0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
bool lightStatus = false;
int lightCounter = 0;
int darknessCounter = 0;

void setup(void) {
  pixels.begin(); // This initializes the NeoPixel library.
  for(int i=0;i<NUMPIXELS;i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
}
 
void loop(void) {
  checkStatus();
  lightController();
}

void checkStatus() {
  photocellReading = analogRead(photocellPin);  
  
  if (photocellReading > 640 && photocellReading < 750) {
    lightCounter++;
    if (lightCounter > 10) {
      lightStatus = true;
    }
  } else {
    lightStatus = false;
    lightCounter = 0;
  }
}

void lightController() {
  if (lightStatus) {
    for(int i=0;i<NUMPIXELS;i++) {
      pixels.setPixelColor(i, pixels.Color(255,0,0));
      pixels.show();
    }
  } else {
    for(int i=0;i<NUMPIXELS;i++) {
      pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show();
    }
  }
}
