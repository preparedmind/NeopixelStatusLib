// from https://randomnerdtutorials.com/stepper-motor-esp32-web-server/

#include <Arduino.h>
#include <NeoPixelStatus.h>


#define NEOPIXEL_PIN 4
#define NUMPIXELS 8
//Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
NeoPixelStatus pixelStatus(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800,20);
#define DELAYVAL 500

void setup()
{
  Serial.begin(115200);
  pixelStatus.setup();

  behavior_step_t* behavior = new behavior_step_t[2];

  behavior[0].pins = 2;
  behavior[0].duration = 200;
  behavior[0].r = 0;
  behavior[0].g = 150;
  behavior[0].b = 0;
  behavior[0].brightness = 40;

  behavior[1].pins = 3;
  behavior[1].duration = 200;
  behavior[1].r = 150;
  behavior[1].g = 0;
  behavior[1].b = 0;
  behavior[1].brightness = 40;

  pixelStatus.setBehavior(behavior, 2);


  Serial.println("End setup");
}

void loop()
{
  pixelStatus.process(); 
}