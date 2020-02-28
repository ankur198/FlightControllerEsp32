#include "Nrf24Communication.h"
#include "ThrustManager.h"
#include "StablizerManager.h"
#include "StructOperation.h"

class FlightManager
{
private:
  /* data */
  Nrf24Communication *communication;
  ThrustManager *thrustManager;
  StablizerManager *stablizerManager;

public:
  FlightManager(/* args */);
  ~FlightManager();

  void Refesh();
};

FlightManager::FlightManager(/* args */)
{
  communication = new Nrf24Communication(Nrf24Communication::Role::FLIGHT);

  thrustManager = new ThrustManager();
  thrustManager->AddThruster(12, ThrustManager::Position::RIGHT);
  thrustManager->AddThruster(13, ThrustManager::Position::LEFT);

  stablizerManager = new StablizerManager();
  stablizerManager->AddElevons(25, 26);
}

FlightManager::~FlightManager()
{
}

void FlightManager::Refesh()
{
  if (!communication->lastDataRead)
  {
    auto newData = communication->lastData;
    PrintData(&newData);

    //thrusters
    thrustManager->SetArmed(newData.armThruster);
    thrustManager->DifferentialEnabled = newData.diffrential;
    thrustManager->SetDifferentialRatio(newData.diffrentialRatio);
    thrustManager->SetPower(newData.thrusterPower);

    //stablizers
    stablizerManager->ArmElevons(newData.armElevons);
    stablizerManager->horizontal = newData.horizontal;
    stablizerManager->vertical = newData.vertical;

    Serial.println("Arm: " + String(newData.armThruster));

    communication->lastDataRead = true;
  }
  stablizerManager->Dispatch();
  thrustManager->Dispatch();
  communication->Refresh();
}
