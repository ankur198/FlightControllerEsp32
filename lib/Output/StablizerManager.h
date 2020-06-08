#include "StablizerMotor.h"

class StabilizerManager
{
private:
  StabilizerMotor *ElevonsLeft[2];
  StabilizerMotor *ElevonsRight[2];
  StabilizerMotor *Elevator;
  StabilizerMotor *Rudder;

  int elevonsLeftCounter = 0;
  int elevonsRightCounter = 0;

public:
  static const int MINPOWER = -50;
  static const int MAXPOWER = 50;

  int vertical = 0;   //range from -50 to 50
  int horizontal = 0; //range from -50 to 50

  StabilizerManager(/* args */);
  ~StabilizerManager();

  void AddElevons(int left, int right);

  void SetElevator(int value);

  void SetRudder(int value);

  void ArmElevons(bool value);

  void Dispatch();
};

StabilizerManager::StabilizerManager(/* args */)
{
}

StabilizerManager::~StabilizerManager()
{
}

void StabilizerManager::ArmElevons(bool value)
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

void StabilizerManager::Dispatch()
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
    Elevator->SetPower(map(vertical, MINPOWER, MAXPOWER, Elevator->MINPOWER, Elevator->MAXPOWER));
  }

  if (Rudder != nullptr)
  {
    Rudder->SetPower(map(horizontal, MINPOWER, MAXPOWER, Elevator->MINPOWER, Elevator->MAXPOWER));
  }
}

void StabilizerManager::AddElevons(int left, int right)
{
  ElevonsLeft[elevonsLeftCounter++] = new StabilizerMotor(left);
  ElevonsRight[elevonsRightCounter++] = new StabilizerMotor(right);
}

void StabilizerManager::SetElevator(int value)
{
  Elevator = new StabilizerMotor(value);
}

void StabilizerManager::SetRudder(int value)
{
  Rudder = new StabilizerMotor(value);
}