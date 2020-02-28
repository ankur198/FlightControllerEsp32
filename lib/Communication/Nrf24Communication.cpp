#include "Nrf24Communication.h"

const byte addresses[][8] = {"Flight", "Cntrol"};

Nrf24Communication::Nrf24Communication(Role role)
{

  lastData.armElevons = false;
  lastData.armThruster = false;
  lastData.diffrential = false;
  lastData.diffrentialRatio = 0;
  lastData.horizontal = 0;
  lastData.thrusterPower = 0;
  lastData.vertical = 0;

  Nrf24Communication::role = role;

  radio = new RF24(17, 5); // CE, CSN

  radio->begin();

  if (role == Role ::FLIGHT)
  {
    radio->openReadingPipe(1, addresses[0]);
    radio->openWritingPipe(addresses[1]);
  }
  else
  {
    radio->openReadingPipe(1, addresses[1]);
    radio->openWritingPipe(addresses[0]);
  }

  radio->startListening();
}

Nrf24Communication::~Nrf24Communication()
{
}

void Nrf24Communication::SendData(FlightDataStruct data)
{
  radio->stopListening();

  auto res = radio->write(&data, sizeof(data));
  Serial.println(res);

  radio->startListening();
}

void Nrf24Communication::RecieveData()
{
  if (radio->available())
  {
    Serial.println("New data");
    while (radio->available())
    {
      radio->read(&lastData, sizeof(lastData));
    }
    lastDataRead = false;
  }
}

void Nrf24Communication::Refresh()
{
  RecieveData();
}