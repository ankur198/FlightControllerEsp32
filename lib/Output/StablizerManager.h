#include "StablizerMotor.h"

class StablizerManager
{
private:
  StablizerMotor *ElevonsLeft[2];
  StablizerMotor *ElevonsRight[2];
  StablizerMotor *Elevator;
  StablizerMotor *Rudder;

  int elevonsLeftCounter = 0;
  int elevonsRightCounter = 0;

public:
  int vertical = 0;   //range from -50 to 50
  int horizontal = 0; //range from -50 to 50

  StablizerManager(/* args */);
  ~StablizerManager();

  void AddElevons(int left, int right);

  void SetElevator(int value);

  void SetRudder(int value);

  void ArmElevons(bool value);

  void Dispatch();
};

StablizerManager::StablizerManager(/* args */)
{
}

StablizerManager::~StablizerManager()
{
}

void StablizerManager::ArmElevons(bool value)
{
  for (int i = 0; i < elevonsLeftCounter; i++)
  {
    ElevonsLeft[i]->SetArmedValue(value);
  }

  for (int i = 0; i < elevonsRightCounter; i++)
  {
    ElevonsRight[i]->SetArmedValue(value);
  }

  if (Elevator != nullptr)
  {
    Elevator->SetArmedValue(value);
  }

  if (Rudder != nullptr)
  {
    Rudder->SetArmedValue(value);
  }
}

void StablizerManager::Dispatch()
{
  //elevons
  if (elevonsLeftCounter != 0 || elevonsRightCounter != 0)
  {
    int leftElevonsPower = vertical + horizontal;
    leftElevonsPower = map(leftElevonsPower, -100, 100, 0, 180);

    int rightElevonsPower = vertical - horizontal;
    rightElevonsPower = map(rightElevonsPower, -100, 100, 0, 180);

    for (int i = 0; i < elevonsLeftCounter; i++)
    {
      ElevonsLeft[i]->SetPower(leftElevonsPower);
    }

    for (int i = 0; i < elevonsRightCounter; i++)
    {
      ElevonsRight[i]->SetPower(rightElevonsPower);
    }
  }

  if (Elevator != nullptr)
  {
    Elevator->SetArmedValue(vertical);
  }

  if (Rudder != nullptr)
  {
    Rudder->SetArmedValue(horizontal);
  }
}

void StablizerManager::AddElevons(int left, int right)
{
  ElevonsLeft[elevonsLeftCounter++] = new StablizerMotor(left);
  ElevonsRight[elevonsRightCounter++] = new StablizerMotor(right);
}

void StablizerManager::SetElevator(int value)
{
  Elevator = new StablizerMotor(value);
}

void StablizerManager::SetRudder(int value)
{
  Rudder = new StablizerMotor(value);
}