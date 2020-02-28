#include "Motor.h"

class Thruster
{
private:
  Motor *motor;
  bool isArmed = false;

public:
  static const int MINPOWER = 50;
  static const int MAXPOWER = 150;

  Thruster(int pin);
  ~Thruster();

  void SetPower(int power);
  void SetArmedValue(bool value);
  bool GetArmed();
};

Thruster::Thruster(int pin)
{
  motor = new Motor(pin);
  motor->SetPower(10);
}

Thruster::~Thruster()
{
}

void Thruster::SetPower(int power)
{
  if (power > MAXPOWER)
  {
    power = MAXPOWER;
  }
  else if (power < MINPOWER)
  {
    power = MINPOWER;
  }
  // Serial.println("Thruster power:" + String(power));
  if (isArmed)
  {
    motor->SetPower(power);
  }
}

void Thruster::SetArmedValue(bool value)
{
  isArmed = value;
  if (value)
  {
    SetPower(MINPOWER);
  }
  else
  {
    motor->SetPower(10);
  }
}

bool Thruster::GetArmed()
{
  return isArmed;
}