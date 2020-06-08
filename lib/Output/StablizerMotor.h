#ifndef _STABILIZE_MOTOR_
#define _STABILIZE_MOTOR_

#include "Motor.h"

class StabilizerMotor
{
private:
  Motor *motor;
  bool isArmed = false;

public:
  static const int MINPOWER = 45;
  static const int MAXPOWER = 135;

  StabilizerMotor(int pin);
  ~StabilizerMotor();

  void SetPower(int power);
  void SetArmedValue(bool value);
  bool GetArmed();
};

StabilizerMotor::StabilizerMotor(int pin)
{
  motor = new Motor(pin);
  motor->SetPower(90);
}

StabilizerMotor::~StabilizerMotor()
{
}

void StabilizerMotor::SetPower(int power)
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

void StabilizerMotor::SetArmedValue(bool value)
{
  isArmed = value;
  motor->SetPower(90);
}

bool StabilizerMotor::GetArmed()
{
  return isArmed;
}

#endif