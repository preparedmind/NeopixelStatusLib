#include "NeoPixelStatus.h"

NeoPixelStatus::NeoPixelStatus(int numPixels, int ledPin, neoPixelType type, int brightness)
{
  this->numPixels = numPixels;
  this->ledPin = ledPin;
  this->type = type;
  this->brightness = brightness;

  this->currentBehavior = NULL;
  this->processingInterval = 200;
  this->lastMillis = millis();

  this->pixels = new Adafruit_NeoPixel(this->numPixels, this->ledPin, this->type);
  this->pixels->setBrightness(this->brightness);
}

void NeoPixelStatus::setup()
{
  this->pixels->begin();
  this->pixels->show();
}

void NeoPixelStatus::process()
{
  if (this->currentBehavior == NULL)
  {
    // no  current behavior - nothing to process.
    return;
  }

  // if time the step has been executing is long enough - go to the next step
  if (this->lastMillis + this->processingInterval < millis())
  {
    int nextStepIndex = (this->currentStepIndex + 1) % (this->currentBehavior->numSteps);
    behavior_step_t nextStep = this->currentBehavior->steps[nextStepIndex];
    
    pixels->clear();

    for (int i = 0; i < this->numPixels; i++)
    {
      int mask = 1 << i;
      int isIncluded = mask & nextStep.pins;

      if (isIncluded > 0)
      {
        pixels->setPixelColor(i, pixels->Color(nextStep.r, nextStep.g, nextStep.b));
      }
    }
    pixels->setBrightness(nextStep.brightness);
    pixels->show();
    
    this->processingInterval = nextStep.duration;
    this->currentStepIndex = nextStepIndex;
    this->lastMillis = millis();
  }
}

void NeoPixelStatus::setBehaviors(behavior_t behaviors[], int numBehaviors)
{
  for (int i = 0; i < numBehaviors; i++)
  {
    this->behaviors[i] = behaviors[i];
  }
  
  for (int i = numBehaviors; i < MAX_BEHAVIORS; i++)
  {
    this->behaviors[i] = {};
  }
  
  this->numBehaviors = numBehaviors;
}

void NeoPixelStatus::startBehavior(int index)
{
  this->currentBehavior = &(this->behaviors[index]);
  this->currentStepIndex = 0;
  this->lastMillis = millis();
  pixels->clear();
}

void NeoPixelStatus::startBehavior(String name)
{
  this->stopBehavior();
  for (int i = 0; i < this->numBehaviors; i++)
  {
    if (this->behaviors[i].name.equals(name))
    {
      this->startBehavior(i);
      break;
    }
  }
}

void NeoPixelStatus::stopBehavior()
{
  pixels->clear();
  this->currentBehavior = NULL;
  this->currentStepIndex = 0;
  this->lastMillis = millis();
}
