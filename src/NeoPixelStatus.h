#ifndef NEOPIXEL_STATUS_H
#define NEOPIXEL_STATUS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

struct behavior_step_t {
  unsigned short int pins; //mask - i-th bit corresponds to i-th led
  int r;
  int g;
  int b;
  int brightness;
  int duration;
} ;

#define MAX_BEHAVIOR_STEPS 16
#define MAX_BEHAVIORS 10

struct behavior_t {
  String name;
  behavior_step_t steps[MAX_BEHAVIOR_STEPS];
  int numSteps; // Number of steps in the behavior
};

class NeoPixelStatus {
  private:
    int ledPin;  //datapin
    int numPixels; //number of pixes in pixel stick
    neoPixelType type;  
    int brightness;  

    behavior_t behaviors[MAX_BEHAVIORS];  
    int numBehaviors;  //number of behaviors defined 
    behavior_t *currentBehavior;  //behavior being executed
    int currentStepIndex; //step of the behavior being executed
  
    int processingInterval;  //time the step will be executing
    uint lastMillis;  //time the step started
    
  public:
    NeoPixelStatus(int numPixels, int ledPin, neoPixelType type, int brightness=40);
    
    void setup();
    void process();
    Adafruit_NeoPixel* pixels;

    
    void setBehaviors(behavior_t behaviors[], int numBehaviors);
    void startBehavior(String name);
    void startBehavior(int behaviorIndex);
    void stopBehavior();
};

#endif
