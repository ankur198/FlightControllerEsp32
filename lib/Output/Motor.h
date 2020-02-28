#ifndef _MOTOR_
#define _MOTOR_

#include <ESP32Servo.h>

class Motor
{
private:
  // -------------------constants for ESP32Servo-------------
  static const int freq = 50;
  static const int min = 544, max = 2400;
  // --------------------------------------------------------

  Servo *servo;
  int pin;

public:
  Motor(int pin);
  ~Motor();

  void SetPower(int dutyCycle);
};

Motor::Motor(int pin)
{
  Motor::pin = pin;
  servo = new Servo();
  servo->setPeriodHertz(freq);
  servo->attach(pin, min, max);
  SetPower(10);
}

Motor::~Motor()
{
}

void Motor::SetPower(int dutyCycle)
{
  // Serial.println("Motor power: " + String(dutyCycle));
  servo->write(dutyCycle);
}

#endif