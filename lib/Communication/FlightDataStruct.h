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
  int vertical;    //6

  //sensors
  float gyro_x;         //7
  float gyro_y;         //8
  float gyro_z;         //9
  float acceleration_x; //10
  float acceleration_y; //11
  float acceleration_z; //12
  float heading;        //13
};

#endif