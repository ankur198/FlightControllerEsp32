#include <Arduino.h>
#include "FlightManager.h"
#include "ControllerManager.h"

#define CONTROLLER 0

#if CONTROLLER == 0
FlightManager *flightManager = nullptr;
#elif CONTROLLER == 1
ControllerManager *controllerManager = nullptr;
#endif

void setup()
{
  Serial.begin(115200);

#if CONTROLLER == 0
  flightManager = new FlightManager();
#elif CONTROLLER == 1
  controllerManager = new ControllerManager();
#endif
}

void loop()
{
#if CONTROLLER == 0
  flightManager->Refesh();
#elif CONTROLLER == 1
  controllerManager->Refresh();
#endif
}