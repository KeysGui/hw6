// test_ThingPerson.cpp

#include "Person.h"
#include "Thing.h"
#include "Record.h"
#include "JvTime.h"
#include "ecs36b_Common.h"

int main(int argc, char *argv[])
{
  // Key value pair exception GPS_DD
  double value = 3.14;
  Json::Value jsonValue;
  jsonValue = value;
  GPS_DD gps_JstStop{value, -121.73899634851351};
  GPS_DD gps_EversonHall { 38.53803233283516, -121.74996578596833 };
  GPS_DD gps_Silo   { 38.53933566907282, -121.75367827130925 };
  GPS_DD gps_Moore {38.56441612430943, -121.71917367026707};

  Person instructor { "instructor", "Felix", gps_Moore }; // Instructor has no specified name
  Person Tiffany {"bus driver", "Tiffany", gps_Silo}; // Assume Tiffany must return to the Silo stop
  Person John {"ecs36B student", "John", gps_JstStop};
  Thing Android_Device { instructor };
  Android_Device.model = "Android Device";
  Android_Device.description = "It belongs to the instructor";

  Thing computer {John};
  computer.model = "computer device";
  computer.description = "John's personal computer.";

  Thing Unitrains_L {Tiffany};
  Unitrains_L.model = "Unitrain L line";
  Unitrains_L.description = "Tiffany is the bus driver for this line";
  

  Person at_Six10_P[3];
  at_Six10_P[0] = John;
  at_Six10_P[1] = Tiffany;
  at_Six10_P[2] = instructor;

  Thing at_Six10_T[3];
  at_Six10_T[0] = Android_Device;
  at_Six10_T[1] = computer;
  at_Six10_T[2] = Unitrains_L;


  instructor.setLocation(gps_JstStop, JvTime("2023-04-12T18:20:00+0700"));

  John.setLocation(gps_JstStop, JvTime("2023-04-12T18:20:00+0700"));

  Tiffany.setLocation(gps_JstStop, JvTime("2023-04-12T18:20:00+0700"));

  try
  {
    Json::Value x;
    char filename[] = "Record1.json";
    int rc1 = myFile2JSON(filename, &x);
    Record r1_test;
    bool b1 = r1_test.JSON2Object(x);
  }
  catch (ecs36b_Exception &e)
  {
    std::cout << "Missing essential key value pair\n";
    std::cout << "standard exception: " << e.what() << endl;
    std::cout << typeid(e).name() << std::endl;
  }
  // Mismatched value type for Thing
  try
  {
    Json::Value y;
    char filename[] = "Record2.json";
    int rc2 = myFile2JSON(filename, &y);
    Record r2_test;
    bool b2 = r2_test.JSON2Object(y);
  }
  catch (ecs36b_Exception &e)
  {
    std::cout << "Mismatched value type\n";
    std::cout << "standard exception: " << e.what() << endl;
    std::cout << typeid(e).name() << std::endl;
  }
  try
  {
    Json::Value x;
    Json::Value another_x;
    char buff[128];
    Record r3{at_Six10_P, at_Six10_T, 3, 3, gps_JstStop, JvTime("2023-04-12T18:20:00+0700")};
    x = r3.dump2JSON();
    //std::cout << "Record 3 - 6:20" << std::endl;
    //std::cout << x.toStyledString() << std::endl;

    snprintf(buff, strlen("./Record3.json") + 1, "./Record3.json");
    int rc3 = myJSON2File(buff, &x);

    rc3 = myFile2JSON(buff, &another_x);
    Record r3_test;
    bool b3 = r3_test.JSON2Object(another_x);
  }
  catch (const std::exception &e)
  {
    std::cout << "not object\n";
    std::cout << "standard exception: " << e.what() << endl;
    std::cout << typeid(e).name() << std::endl;
  }

  try
  {
    Json::Value another_a;
    char filename[] = "Record4.json";
    int rc4 = myFile2JSON(filename, &another_a);
    another_a["hidden"] = "SOS"; // Manually changing the hidden attribute to SOS
    Record u_another;
    bool e = u_another.JSON2Object(another_a);
  }
  catch (const std::exception &e)
  {
    std::cout << "Exception occurred: " << e.what() << std::endl;
    std::cout << typeid(e).name() << std::endl;
  }

  return 0;
}
