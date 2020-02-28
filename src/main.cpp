#include <Arduino.h>
#include "FlightManager.h"
#include "ControllerManager.h"

#define CONTROLLER 0

FlightManager *flightManager = nullptr;
ControllerManager *controllerManager = nullptr;

void setup()
{
  Serial.begin(115200);

#if CONTROLLER == 0   //port 5
  flightManager = new FlightManager();
#elif CONTROLLER == 1 //port 3
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