
#include "Record.h"
#include <string>
#include "ecs36b_Exception_hw6.h"
using namespace std;

// Function to create empty Record object
Record ::Record(){
    who = nullptr;
    what = nullptr;
    numP = 0;
    numT = 0;
    where = GPS_DD();
    when = JvTime();
}

Record::Record(Person _p[], Thing _t[], int n, int l, GPS_DD _g, JvTime _jt)
{
  //n = sizeof(_p)/sizeof(_p[0]);
  who = new Person[n];
  for(int i = 0; i < n; i++){
    who[i] = _p[i];
  }
  //l = sizeof(_t)/sizeof(_t[0]);
  what = new Thing[l];
  for(int i = 0; i < l; i++){
    what[i] = _t[i];
  }
  this->numP = n;
  this->numT = l;
  this->where = _g;
  this->when = _jt;
}

// Dump paired keys
Json::Value Record::dump2JSON()
{
  Json::Value result;
  result["where"] = (this->where).dump2JSON();
  result["when"] = (this->when).dump2JSON();
  Json::Value whoArr(Json::arrayValue); // Loop through the specified who array (_p) depending on given size
  for (int i = 0; i < numP; i++) {
    whoArr.append(who[i].dump2JSON());
  }
  result["who"] = whoArr;
  Json::Value whatArr(Json::arrayValue);
  for(int j = 0; j < numT; j++){
    whatArr.append(what[j].dump2JSON());
  }
  result["what"] = whatArr;
  result["hidden"] = hidden;
  return result;
}

#include "Record.h"

bool Record::JSON2Object(Json::Value arg_jv)
{
  ecs36b_Exception my_exception;
  my_exception.data["typeid"] = string { removeNumberPrefix(typeid(*this).name()) };
  my_exception.data["method"] = "JSON2Object";
  std::string sbuf;
  if (arg_jv.isMember("hidden")) {
    if (!arg_jv["hidden"].isString()) {
      sbuf = "hidden' attribute must be a String";
      my_exception.data["message"] = sbuf;
      my_exception.data["error_code"] = EXC_ERR_DATA_TYPE;
      throw my_exception;
    }
    std::string hiddenValue = arg_jv["hidden"].asString();
    if (hiddenValue == "SOS" || hiddenValue == "HELP") {
      sbuf = "A critical hidden detected";
      my_exception.data["message"] = sbuf;
      my_exception.data["error_code"] = EXC_ERR_HIDDEN_DETECTED;
      throw my_exception;
    }
    hidden = hiddenValue; // Store the value in the hidden member variable
  }

  // Extract the "where" JSON object
  Json::Value whereObj = arg_jv["where"];
  if (!whereObj.isNull())
  {
    this->where.JSON2Object(whereObj);
  }

  // Extract the "when" JSON object
  Json::Value whenObj = arg_jv["when"];
  if (!whenObj.isNull())
  {
    this->when.JSON2Object(whenObj);
  }

  // Extract the "who" array
  Json::Value whoArr = arg_jv["who"];
  if (whoArr.isArray())
  {
    numP = whoArr.size();
    this -> who = new Person[numP];
    for (int i = 0; i < numP; i++)
    {
      Json::Value temp = whoArr[i];

      who[i].JSON2Object(temp);

    }
  }

  // Extract the "what" array
  Json::Value whatArr = arg_jv["what"];
  if (whatArr.isArray())
  {
    numT = whatArr.size();
    what = new Thing[numT];
    for (int i = 0; i < numT; i++)
    {
      what[i].JSON2Object(whatArr[i]);
    }

  }



  return true;
}
