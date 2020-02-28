#ifndef _STRUCT_OPERATION_
#define _STRUCT_OPERATION_
#include "FlightDataStruct.h"

void AddToFlightData(FlightDataStruct *buffer, int id, float value)
{
  switch (id)
  {
  case 0:
    buffer->armThruster = value;
    break;
  case 1:
    buffer->diffrential = value;
    break;
  case 2:
    buffer->thrusterPower = value;
    break;
  case 3:
    buffer->diffrentialRatio = value;
    break;
  case 4:
    buffer->armElevons = value;
    break;
  case 5:
    buffer->horizontal = value;
    break;
  case 6:
    buffer->vertical = value;
    break;

  default:
    break;
  }
}

void PrintData(FlightDataStruct *buffer)
{
  String data = "\n\nData\n\nArmThrust: " + String(buffer->armThruster) +
                "\nDifferential: " + String(buffer->diffrential) +
                "\nThrust Power: " + String(buffer->thrusterPower) +
                "\nDiffrential Ratio: " + String(buffer->diffrentialRatio) +
                "\nArm Elevons: " + String(buffer->armElevons) +
                "\nHorizontal: " + String(buffer->horizontal) +
                "\nVertical: " + String(buffer->vertical);

  Serial.println(data);
}
#endif