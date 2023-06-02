
#include "Person.h"

Person::Person(std::string arg_identity, std::string arg_name, GPS_DD arg_destination)
{
  this->identity = arg_identity;
  this->name = arg_name;
  this->destination = arg_destination;
}

Person::Person()
{
  this->identity = "";
  this->name = "";
  this->destination = GPS_DD {};
}

void
Person::setHome
(GPS_DD arg_destination)
{
  this->destination = arg_destination;
}

void
Person::setLocation
(GPS_DD arg_location, JvTime arg_time)
{
  this->location = arg_location;
  this->since_when = arg_time;
}

GPS_DD
Person::getHome
(void)
{
  return this->destination;
}

std::string
Person::getIdentity()
{
  return this->identity;
}

std::string
Person::getName()
{
  return this->name;
}

// function prototype
bool
Person::operator==
(Person& aPerson)
{
  return (this->identity == aPerson.getIdentity());

  return (this->name == aPerson.getName());

  return ((this->name == aPerson.getName()) &&
	  (this->identity == aPerson.getIdentity()));
}

void Person::dump
(void)
{
  std::cout << "[Person] dump-begin" << std::endl;
  std::cout << "name           = " << this->name << std::endl;
  std::cout << "identity       = " << this->identity << std::endl;
  std::cout << "[Person] dump-end" << std::endl;

  return;
}

Json::Value
Person::dump2JSON()
{
  Json::Value result;
  if (this->name != "")
    {
      result["name"] = this->name;
    }

  if (this->identity != "")
    {
      result["identity"] = this->identity;
    }

#ifdef _ECS36B_DEBUG_
  std::cout << result.toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result;
}

bool Person::JSON2Object(Json::Value arg_jv)
{
  ecs36b_Exception my_exception;
  my_exception.data["typeid"] = string { removeNumberPrefix(typeid(*this).name()) };
  my_exception.data["method"] = "JSON2Object";
  std::string sbuf;

  if ((arg_jv.isNull() == true))
  {
      sbuf = "input is a NULL json";
      my_exception.data["message"] = sbuf;
      my_exception.data["error_code"] = EXC_ERR_INPUT_NULL;
      throw my_exception;
  }
  if((arg_jv.isObject() != true)){
      sbuf = "input is not a json object";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_INPUT_NOT_OBJECT;
      throw my_exception;
  }

  if (arg_jv["identity"].isNull() == true)
  {
    sbuf = "missing required attribute \"identity\"";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_MISSING_ATTRIBUTE;
      throw my_exception;
  }
  if(arg_jv["identity"].isString() != true){
    sbuf = "attribute \"identity\" not string";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_DATA_TYPE;
      throw my_exception;
  }

  if (arg_jv["name"].isNull() == true)
  {
    sbuf = "missing required attribute \"name\"";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_MISSING_ATTRIBUTE;
      throw my_exception;
  }
  if(arg_jv["name"].isString() != true){
    sbuf = "attribute \"name\" not string";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_DATA_TYPE;
      throw my_exception;
  }

  // Assign identity and name
  this->identity = arg_jv["identity"].asString();
  this->name = arg_jv["name"].asString();

  return true;
}
