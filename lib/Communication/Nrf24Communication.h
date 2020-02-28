#ifndef _NRF24Communication_
#define _NRF24Communication_

#include <SPI.h>
#include <RF24.h>
#include "FlightDataStruct.h"

class Nrf24Communication
{
  /*
    CE -> GPIO17 GPIO
    CSN -> GPIO05 VSPI SS
    MISO -> GPIO19 VSPI MISO
    MOSI -> GPIO23 VSPI MOSI
    CLK -> GPIO18 VSPI CLK
    IRQ-> unconnected
  */
private:
  /* data */
  RF24 *radio;

  void RecieveData();

public:
  enum Role
  {
    FLIGHT,
    CONTROLLER
  };
  Role role;

  FlightDataStruct lastData;
  bool lastDataRead = false;

  Nrf24Communication(Role role);
  ~Nrf24Communication();

  void SendData(FlightDataStruct data);
  void Refresh();
};

#endif