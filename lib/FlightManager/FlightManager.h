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
  thrustManager->AddThruster(12, ThrustManager::Position::CENTER);

  stablizerManager = new StablizerManager();
  stablizerManager->SetElevator(25);
  stablizerManager->SetRudder(26);
}

FlightManager::~FlightManager()
{
}

void FlightManager::Refesh()
{
  if (!communication->lastDataRead)
  {
    auto newData = communication->lastData;
    // PrintData(&newData);

    //thrusters
    thrustManager->SetArmed(newData.armThruster);
    thrustManager->DifferentialEnabled = newData.differential;
    thrustManager->SetDifferentialRatio(newData.differentialRatio);
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
