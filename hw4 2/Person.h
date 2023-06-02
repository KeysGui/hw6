
#ifndef _PERSON_H_
#define _PERSON_H_

// Person.h

#include "GPS.h"
#include "JvTime.h"
#include "ecs36b_Common.h"

class Person
{
 private:
  std::string identity;
  std::string name;
  GPS_DD destination;
  GPS_DD location;
  JvTime since_when;

public:
  Person(std::string, std::string, GPS_DD);
  Person();
  void setHome(GPS_DD);
  void setLocation(GPS_DD, JvTime);

  bool operator==(Person& aPerson);
  std::string getIdentity();
  std::string getName();
  GPS_DD getHome();
  GPS_DD getLocation();
  JvTime getLocationTime();
  void dump();
   Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value);
};

#endif  /* _PERSON_H_ */
