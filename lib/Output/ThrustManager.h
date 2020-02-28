#include "Thruster.h"

class ThrustManager
{
private:
  Thruster *centerThrusters[10];
  Thruster *leftThrusters[10];
  Thruster *rightThrusters[10];
  int centerCounter = 0;
  int leftCounter = 0;
  int rightCounter = 0;

  int power = 0;
  float differentialRatio = 0;

public:
  enum Position
  {
    CENTER,
    LEFT,
    RIGHT
  };

  bool DifferentialEnabled = false;

  ThrustManager(/* args */);
  ~ThrustManager();

  void AddThruster(int pin, Position position);
  void SetArmed(bool value);
  /*
    power: can be between 0 to 100
  */
  void SetPower(int power);
  void SetDifferentialRatio(float ratio); // TODO: clarify direction
  void Dispatch();
};

ThrustManager::ThrustManager(/* args */)
{
}

ThrustManager::~ThrustManager()
{
}

void ThrustManager::AddThruster(int pin, Position position)
{
  Thruster *thruster = new Thruster(pin);

  if (position == Position::CENTER)
  {
    centerThrusters[centerCounter++] = thruster;
  }
  else if (position == Position::LEFT)
  {
    leftThrusters[leftCounter++] = thruster;
  }
  else if (position == Position::RIGHT)
  {
    rightThrusters[rightCounter++] = thruster;
  }
}

void ThrustManager::SetArmed(bool value)
{
  for (int i = 0; i < centerCounter; i++)
  {
    centerThrusters[i]->SetArmedValue(value);
  }

  for (int i = 0; i < leftCounter; i++)
  {
    leftThrusters[i]->SetArmedValue(value);
  }

  for (int i = 0; i < rightCounter; i++)
  {
    rightThrusters[i]->SetArmedValue(value);
  }
}

void ThrustManager::SetPower(int power)
{
  ThrustManager::power = power;
}

void ThrustManager::SetDifferentialRatio(float ratio)
{
  differentialRatio = ratio;
}

void ThrustManager::Dispatch()
{
  int rawPower = map(power, 0, 100, Thruster::MINPOWER, Thruster::MAXPOWER);
  int difference = DifferentialEnabled ? rawPower * differentialRatio : 0;

  // Serial.println("Differential difference: " + String(difference));

  int leftPower = rawPower - difference;
  int rightPower = rawPower + difference;

  //Serial.println("ThrustManager power:" + String(rawPower));

  for (int i = 0; i < centerCounter; i++)
  {
    centerThrusters[i]->SetPower(rawPower);
  }

  for (int i = 0; i < leftCounter; i++)
  {
    leftThrusters[i]->SetPower(leftPower);
  }

  for (int i = 0; i < rightCounter; i++)
  {
    rightThrusters[i]->SetPower(rightPower);
  }
}