# NeopixelStatusLib

A library to show status using Neopixel Stick 8 with patterns of LEDs and simple programming interface.

## Overview
Display status in two primary steps:

1. Define light pattern, and
1. Start stop patterns

### Define Light Pattern

```cpp
behavior_t behaviors[1]; //in general an array of behaviors

  behaviors[0].name = "Sweep";
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
```

## Manage behaviors
1. Initialize pixelStatus:
```cpp
#define NEOPIXEL_PIN 4
#define NUMPIXELS 8
NeoPixelStatus pixelStatus(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800,20);
```
Depends on Adafruit_NeoPixel library.

2. Set behaviors:
```cpp
pixelStatus.setBehaviors(behaviors, 1);
```
Second argument is number of behaviors in the array.

3. Start a behavior:
```cpp
pixelStatus.startBehavior("Sweep"); //by name
pixelStatus.startBehavior(0); //by index
```

4. Stop current behavior:
```cpp
pixelStatus.stopBehavior("Sweep"); //by name
``
