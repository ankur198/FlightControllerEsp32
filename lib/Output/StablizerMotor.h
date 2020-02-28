#include "Motor.h"

class StablizerMotor
{
private:
  Motor *motor;
  bool isArmed = false;

public:
  static const int MINPOWER = 0;
  static const int MAXPOWER = 180;

  StablizerMotor(int pin);
  ~StablizerMotor();

  void SetPower(int power);
  void SetArmedValue(bool value);
  bool GetArmed();
};

StablizerMotor::StablizerMotor(int pin)
{
  motor = new Motor(pin);
  motor->SetPower(90);
}

StablizerMotor::~StablizerMotor()
{
}

void StablizerMotor::SetPower(int power)
{
  if (power > MAXPOWER)
  {
    power = MAXPOWER;
  }
  else if (power < MINPOWER)
  {
    power = MINPOWER;
  }
  if (isArmed)
  {
    motor->SetPower(power);
  }
}

void StablizerMotor::SetArmedValue(bool value)
{
  isArmed = value;
  motor->SetPower(90);
}

bool StablizerMotor::GetArmed()
{
  return isArmed;
}