#ifndef _RECORD_H_
#define _RECORD_H_

// Record.h

#include "Person.h"
#include "Thing.h"
#include "GPS.h"
#include "JvTime.h"

#include "ecs36b_Common.h"

class Record
{
 private:
  Person* who;
  Thing* what;
  GPS_DD where;
  JvTime when;
  int numP; // number of persons
  int numT; // number of things
  std::string hidden = "";

public:
  Record();
  Record(Person[], Thing[], int, int, GPS_DD, JvTime);
  Json::Value dump2JSON();
  virtual bool JSON2Object (Json::Value);
};

#endif  /* _RECORD_H_ */
