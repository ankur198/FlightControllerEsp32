#ifndef _FlightDataStruct_
#define _FlightDataStruct_

struct FlightDataStruct
{
  // thruster
  bool armThruster;       //0
  bool diffrential;       //1
  int thrusterPower;      //2
  float diffrentialRatio; //3

  // elevons
  bool armElevons; //4
  int horizontal;  //5
  int vertical; //6
};

#endif