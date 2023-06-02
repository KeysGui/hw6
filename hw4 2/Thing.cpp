
#include "Thing.h"

Thing::Thing
(void)
{
  this->model = "";
  this->description = "";
}

Thing::Thing
(Person arg_owner)
{
  this->model = "";
  this->description = "";
  this->owner = arg_owner;
}

std::string Thing::getName() const {
  return model;
}

Json::Value
Thing::dump2JSON()
{
  Json::Value result;
  if (this->model != "")
    {
      result["model"] = this->model;
    }

  if (this->description != "")
    {
      result["description"] = this->description;
    }
  return result;
}

bool Thing::JSON2Object(Json::Value arg_jv)
{
  ecs36b_Exception my_exception;
  my_exception.data["typeid"] = string { removeNumberPrefix(typeid(*this).name()) };
  my_exception.data["method"] = "JSON2Object";
  std::string sbuf;
  if (arg_jv.isNull() == true)
    {
      sbuf = "input is a NULL json";
      my_exception.data["message"] = sbuf;
      my_exception.data["error_code"] = EXC_ERR_INPUT_NULL;
      throw my_exception;
    }

  if (arg_jv.isObject() != true)
    {
      sbuf = "input is not a json object";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_INPUT_NOT_OBJECT;
      throw my_exception;
    }
  
  if ((arg_jv["model"]).isNull() == true)
    {
      sbuf = "missing required attribute \"latitude\"";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_MISSING_ATTRIBUTE;
      throw my_exception;
    }

  if ((arg_jv["description"]).isNull() == true)
    {
      sbuf = "missing required attribute \"longitude\"";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_MISSING_ATTRIBUTE;
      throw my_exception;
    }
  if ((arg_jv["model"]).isString() != true)
    {
      sbuf = "attribute \"latitude\" not double";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_DATA_TYPE;
      throw my_exception;
    }

  if ((arg_jv["description"]).isString() != true)
    {
      sbuf = "attribute \"longitude\" not double";
      my_exception.data["message"] = sbuf;
      my_exception.data["input"] = arg_jv;
      my_exception.data["error_code"] = EXC_ERR_DATA_TYPE;
      throw my_exception;
    }


  if (!arg_jv.isObject())
  {
    if (!arg_jv.isNull())
    {
      std::cout << arg_jv.toStyledString() << std::endl;
    }
    
  }

  if (!arg_jv["model"].isNull() && arg_jv["model"].isString())
  {
    model = arg_jv["model"].asString();
  }
  

  if (!arg_jv["description"].isNull() && arg_jv["description"].isString())
  {
    description = arg_jv["description"].asString();
  }
  

  return true;
}
