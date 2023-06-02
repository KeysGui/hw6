# Makefile for f2022, ecs36b
#
# g++ -std=c++14 test_GPS.cpp GPS.cpp -o test_GPS
#
# example: $ ./test_GPS 48.88 2.3

CC 	= g++ -std=c++14
#CFLAGS 	= -g
CFLAGS = -g -I/usr/include/jsoncpp -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -lcurl -ljsonrpccpp-client

# rules.
all: 	ecs36b_hw6_driver

#
#

Record.o:	Record.cpp Record.h 
	$(CC) -c $(CFLAGS) Record.cpp



GPS.o:		GPS.cpp GPS.h
	$(CC) -c $(CFLAGS) GPS.cpp

JvTime.o:	JvTime.cpp JvTime.h
	$(CC) -c $(CFLAGS) JvTime.cpp

Person.o:	Person.cpp Person.h
	$(CC) -c $(CFLAGS) Person.cpp

Thing.o:	Thing.cpp Thing.h
	$(CC) -c $(CFLAGS) Thing.cpp

ecs36b_JSON.o: ecs36b_JSON.cpp ecs36b_Common.h
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

ecs36b_hw6_driver.o:	ecs36b_hw6_driver.cpp GPS.h Thing.h Person.h JvTime.h Record.h ecs36b_Common.h 
	$(CC) -c $(CFLAGS) ecs36b_hw6_driver.cpp

ecs36b_hw6_driver:	GPS.o ecs36b_hw6_driver.o Thing.o Person.o JvTime.o Record.o ecs36b_JSON.o 
	g++ -std=c++14 ecs36b_hw6_driver.o GPS.o Thing.o Person.o JvTime.o Record.o ecs36b_JSON.o  -o ecs36b_hw6_driver $(LDFLAGS)

clean:
	rm -f *.o *~ core ecs36b_hw6_driver
