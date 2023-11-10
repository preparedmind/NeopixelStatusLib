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
  Serial.println("Start setup");
  pixelStatus.setup();

  behavior_t behaviors[2];

  behaviors[0].name = "Blink";
  behaviors[0].numSteps = 16;
  int stepIndex = 0;

  for(int i =0; i < 8; i++) {
    // int i =  0;
    behaviors[0].steps[stepIndex].pins = static_cast<int>(pow(2,i));
    behaviors[0].steps[stepIndex].r = 0;
    behaviors[0].steps[stepIndex].g = 150;
    behaviors[0].steps[stepIndex].b = 0;
    behaviors[0].steps[stepIndex].brightness = 40;
    behaviors[0].steps[stepIndex].duration = 100;
    stepIndex++;
  }
  
  for(int i =7; i >= 0; i--) {
    behaviors[0].steps[stepIndex].pins = static_cast<int>(pow(2,i));
    behaviors[0].steps[stepIndex].r = 0;
    behaviors[0].steps[stepIndex].g = 150;
    behaviors[0].steps[stepIndex].b = 0;
    behaviors[0].steps[stepIndex].brightness = 40;
    behaviors[0].steps[stepIndex].duration = 100;
    stepIndex++;
  }
  
  behaviors[1].name = "Blink2";
  behaviors[1].numSteps = 8;
  stepIndex = 0;
  for(int i =0; i < 8; i++) {
    // int i =  0;
    behaviors[1].steps[stepIndex].pins = static_cast<int>(pow(2,i))+static_cast<int>(pow(2,7-i)) ;
    behaviors[1].steps[stepIndex].r = 150;
    behaviors[1].steps[stepIndex].g = 0;
    behaviors[1].steps[stepIndex].b = 0;
    behaviors[1].steps[stepIndex].brightness = 40;
    behaviors[1].steps[stepIndex].duration = 100;
    stepIndex++;
  }
  
  // behaviors[1].steps[0].pins = 3;
  // behaviors[1].steps[0].r = 0;
  // behaviors[1].steps[0].g = 150;
  // behaviors[1].steps[0].b = 0;
  // behaviors[1].steps[0].brightness = 40;
  // behaviors[1].steps[0].duration = 200;

  // behaviors[1].steps[1].pins = 3;
  // behaviors[1].steps[1].duration = 200;
  // behaviors[1].steps[1].r = 150;
  // behaviors[1].steps[1].g = 0;
  // behaviors[1].steps[1].b = 0;
  // behaviors[1].steps[1].brightness = 40;

  pixelStatus.setBehaviors(behaviors, 2);

  Serial.println("End setup2");
}

int switchBehaviorInterval = 5000;
int lastMillis = millis()-switchBehaviorInterval;
String currentBehaviorName = "Blink";

void loop()
{
  if(lastMillis + switchBehaviorInterval < millis()) {
    Serial.println("Switch behavior");
    Serial.println(currentBehaviorName);
    if( currentBehaviorName.compareTo("Blink") == 0  ) {
      pixelStatus.startBehavior("Blink2");
      currentBehaviorName = "Blink2";
    }else {
      pixelStatus.startBehavior("Blink");
      currentBehaviorName = "Blink";
    }
    Serial.println(currentBehaviorName);
    
    lastMillis = millis();
  }

  pixelStatus.process(); 
}