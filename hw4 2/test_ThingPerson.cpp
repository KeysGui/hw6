// test_ThingPerson.cpp

#include "Person.h"
#include "Thing.h"
#include "Record.h"
#include "JvTime.h"
#include "ecs36b_Common.h"

int
main(int argc, char *argv[])
{
	// Set location by latitude and longtitude
  double value = 3.14;
  Json::Value jsonValue;
  jsonValue = value;
  GPS_DD gps_EversonHall { 38.53803233283516, -121.74996578596833 };
  GPS_DD gps_Silo   { 38.53933566907282, -121.75367827130925 };
  GPS_DD gps_JstStop {38.551917054430156, -121.73899634851351};
  GPS_DD gps_Moore {38.56441612430943, -121.71917367026707};

	// Define Persons by identity, name, and final destination
  Person instructor { "instructor", "Felix", gps_Moore }; // Instructor has no specified name
  Person Tiffany {"bus driver", "Tiffany", gps_Silo}; // Assume Tiffany must return to the Silo stop
  Person John {"ecs36B student", "John", gps_JstStop};

	// Define Things by ownership, then assign a model and description
  Thing Android_Device { instructor };
  Android_Device.model = "Android Device";
  Android_Device.description = "It belongs to the instructor";

  Thing computer {John};
  computer.model = "computer device";
  computer.description = "John's personal computer.";

  Thing Unitrains_L {Tiffany};
  Unitrains_L.model = "Unitrain L line";
  Unitrains_L.description = "Tiffany is the bus driver for this line";

	// Set the location for each Person at certain times
  instructor.setLocation(gps_EversonHall, JvTime("2023-04-12T18:00:00+0700"));
  instructor.setLocation(gps_Silo, JvTime("2023-04-12T18:10:00+0700"));
  instructor.setLocation(gps_JstStop, JvTime("2023-04-12T18:20:00+0700"));
  instructor.setLocation(gps_Moore, JvTime("2023-04-12T18:32:00+0700"));

  John.setLocation(gps_EversonHall, JvTime("2023-04-12T18:00:00+0700"));
  John.setLocation(gps_Silo, JvTime("2023-04-12T18:10:00+0700"));
  John.setLocation(gps_JstStop, JvTime("2023-04-12T18:20:00+0700"));

  Tiffany.setLocation(gps_Silo, JvTime("2023-04-12T18:10:00+0700"));
  Tiffany.setLocation(gps_JstStop, JvTime("2023-04-12T18:20:00+0700"));
  Tiffany.setLocation(gps_Moore, JvTime("2023-04-12T18:32:00+0700"));

	// Arrays to make it possible for Record.cpp to loop through and process each object for each record
  Person at_Six_P[2];
  at_Six_P[0] = instructor;
  at_Six_P[1] = John;

  Thing at_Six_T[2];
  at_Six_T[0] = Android_Device;
  at_Six_T[1] = computer;

	// Person and Thing are the same at 6:10 and 6:20 so only one set of arrays (at_Six10 _P and _T) is needed
  Person at_Six10_P[3];
  at_Six10_P[0] = John;
  at_Six10_P[1] = Tiffany;
  at_Six10_P[2] = instructor;

  Thing at_Six10_T[3];
  at_Six10_T[0] = Android_Device;
  at_Six10_T[1] = computer;
  at_Six10_T[2] = Unitrains_L;

  Person at_Six32_P[2];
  at_Six32_P[0] = instructor;
  at_Six32_P[1] = Tiffany;

  Thing at_Six32_T[2];
  at_Six32_T[0] = Unitrains_L;
  at_Six32_T[1] = Android_Device;

  Json::Value x;

	// Dump each record to JSON and print as a styled string
  Record r1 {at_Six_P, at_Six_T, 2, 2, gps_EversonHall, JvTime("2023-04-12T18:00:00+0700")};
  x = r1.dump2JSON();
  std::cout << "Record 1 - 6:00" << std::endl;
  std::cout << x.toStyledString() << std::endl;

  Json::Value another_x;

	// Convert each JSON record into a file
  char buff[128];
  snprintf(buff, strlen("./Record1.json") + 1, "./Record1.json");
  int rc1 = myJSON2File(buff, &x);

	// Convert the file into a Record object and print the object
  rc1 = myFile2JSON(buff, &another_x);
  Record r1_test;
  bool b1 = r1_test.JSON2Object(another_x);

  Json::Value y = r1_test.dump2JSON();
  std::cout << "Record 1 - 6:10 (JSON2Object version)" << std::endl;
  std::cout << y.toStyledString() << std::endl;

	// Record 2
  Record r2 {at_Six10_P, at_Six10_T, 3, 3, gps_Silo, JvTime("2023-04-12T18:10:00+0700")};
  x = r2.dump2JSON();
  std::cout << "Record 2 - 6:10" << std::endl;
  std::cout << x.toStyledString() << std::endl;

  snprintf(buff, strlen("./Record2.json") + 1, "./Record2.json");
  int rc2 = myJSON2File(buff, &x);

   rc2 = myFile2JSON(buff, &another_x);
  Record r2_test;
  bool b2 = r2_test.JSON2Object(another_x);

   y = r2_test.dump2JSON();
  std::cout << "Record 2 - 6:10 (JSON2Object version)" << std::endl;
  std::cout << y.toStyledString() << std::endl;

	// Record 3
  Record r3 {at_Six10_P, at_Six10_T, 3, 3, gps_JstStop, JvTime("2023-04-12T18:20:00+0700")};
  x = r3.dump2JSON();
  std::cout << "Record 3 - 6:20" << std::endl;
  std::cout << x.toStyledString() << std::endl;

  snprintf(buff, strlen("./Record3.json") + 1, "./Record3.json");
  int rc3 = myJSON2File(buff, &x);

  rc3 = myFile2JSON(buff, &another_x);
  Record r3_test;
  bool b3 = r3_test.JSON2Object(another_x);

  y = r3_test.dump2JSON();
  std::cout << "Record 3 - 6:18 (JSON2Object version)" << std::endl;
  std::cout << y.toStyledString() << std::endl;

	// Record 4
  Record r4 {at_Six32_P, at_Six32_T, 2, 2, gps_Moore, JvTime("2023-04-12T18:32:00+0700")};
  x = r4.dump2JSON();
  std::cout << "Record 4 - 6:32" << std::endl;
  std::cout << x.toStyledString() << std::endl;

  snprintf(buff, strlen("./Record4.json") + 1, "./Record4.json");
  int rc4 = myJSON2File(buff, &x);

  rc4 = myFile2JSON(buff, &another_x);
  Record r4_test;
  bool b4 = r4_test.JSON2Object(another_x);

  y = r4_test.dump2JSON();
  std::cout << "Record 4 - 6:32 (JSON2Object version)" << std::endl;
  std::cout << y.toStyledString() << std::endl;

  return 0;
}
