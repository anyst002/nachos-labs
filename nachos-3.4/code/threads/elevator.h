
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "copyright.h"
#include "synch.h"

void Elevator(int numFloors);
void ArrivingGoingFromTo(int atFloor, int toFloor);

typedef struct Person {
    int id;
    int atFloor;
    int toFloor;
} Person;


class ELEVATOR {

public:
    ELEVATOR(int numFloors);
    ~ELEVATOR();
    void hailElevator(Person *p);
    void start();

private:
    bool moveElevator(int i);
    bool hasActivePersons();
    bool finished();

    Condition **entering;
    Condition **leaving;
    Lock* elevatorLock;

    int *personsLeaving;
    int *personsWaiting;

    int occupancy;
    int maxOccupancy;
    int numFloors;
    int currentFloor;
};

#endif