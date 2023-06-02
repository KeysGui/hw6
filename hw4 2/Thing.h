
#ifndef _THING_H_
#define _THING_H_

// Thing.h
#include "Person.h"
#include "GPS.h"
#include "JvTime.h"
#include "ecs36b_Common.h"

class Thing
{
 private:
 protected:
 public:


  std::string model;
  std::string description;
  Person      owner;
  JvTime      purchased;
  JvTime      sold;

  GPS_DD      location;

  Thing(void);
  Thing(Person arg_owner);
  //virtual void dump(); // print the content of the object
  std::string getName() const;
  Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value);
};

#endif /* _THING_H_ */
