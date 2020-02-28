#include "Nrf24Communication.h"
#include "FlightDataStruct.h"
#include "StructOperation.h"

class ControllerManager
{
private:
  /* data */
  Nrf24Communication *communication;

  void ReadData(FlightDataStruct *buffer);

public:
  ControllerManager(/* args */);
  ~ControllerManager();
  void Refresh();
};

ControllerManager::ControllerManager(/* args */)
{
  communication = new Nrf24Communication(Nrf24Communication::CONTROLLER);
}

ControllerManager::~ControllerManager()
{
}

void ControllerManager::Refresh()
{
  if (Serial.available())
  {
    FlightDataStruct data;

    ReadData(&data);

    communication->SendData(data);
  }
}

void ControllerManager::ReadData(FlightDataStruct *buffer)
{
#define INPUT_SIZE 100
  char input[INPUT_SIZE + 1];
  auto size = Serial.readBytesUntil(';', input, INPUT_SIZE);
  input[size] = 0;

  // Read each command pair
  char *command = strtok(input, "&");
  while (command != 0)
  {
    // Split the command in two values
    char *separator = strchr(command, ':');
    if (separator != 0)
    {
      // Actually split the string in 2: replace ':' with 0
      *separator = 0;
      int id = atoi(command);
      ++separator;
      float value = atof(separator);

      AddToFlightData(buffer, id, value);
    }
    // Find the next command in input string
    command = strtok(0, "&");
  }
}
