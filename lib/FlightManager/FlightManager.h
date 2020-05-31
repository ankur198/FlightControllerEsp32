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
  StabilizerManager *stabilizerManager;

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

  stabilizerManager = new StabilizerManager();
  stabilizerManager->SetElevator(25);
  stabilizerManager->SetRudder(26);
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
    stabilizerManager->ArmElevons(newData.armElevons);
    stabilizerManager->horizontal = newData.horizontal;
    stabilizerManager->vertical = newData.vertical;

    Serial.println("Arm: " + String(newData.armThruster));

    communication->lastDataRead = true;
  }
  stabilizerManager->Dispatch();
  thrustManager->Dispatch();
  communication->Refresh();
}
