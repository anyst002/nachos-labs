#include "copyright.h"
#include "elevator.h"
#include "system.h"
#include "synch.h"

ELEVATOR* e;  // Global elevator instance
int nextPersonID = 1;
Lock* personIDLock = new Lock("PersonIDLock");

ELEVATOR::ELEVATOR(int numFloors) {
    this->numFloors = numFloors;
    this->currentFloor = 1;
    this->occupancy = 0;

    personsWaiting = new int[numFloors]();  // Initialize waiting counts to 0

    // Initialize condition variables
    entering = new Condition*[numFloors];
    leaving = new Condition*[numFloors];
    for (int i = 0; i < numFloors; i++) {
        entering[i] = new Condition("Entering " + i);
        leaving[i] = new Condition("Leaving " + i);
    }

    elevatorLock = new Lock("ElevatorLock");
}

void ELEVATOR::start() {
    while (true) {
        elevatorLock->Acquire();

        // Check if there are passengers waiting on any floor
        bool hasPassengers = false;
        for (int i = 0; i < numFloors; i++) {
            if (personsWaiting[i] > 0) {
                hasPassengers = true;
                break;
            }
        }

        // If no passengers, release lock and yield
        if (!hasPassengers && occupancy == 0) {
            elevatorLock->Release();
            currentThread->Yield();
            continue;
        }

        // Move the elevator floor by floor
        for (int i = 0; i < numFloors; i++) {
            printf("Elevator is moving to floor %d.\n", i + 1);
            currentFloor = i + 1;
            elevatorLock->Release();

            // Simulate travel time (yield to other threads)
            for (int j = 0; j < 500000; j++) {
                currentThread->Yield();
            }

            elevatorLock->Acquire();

            // Signal all passengers to leave
            leaving[currentFloor - 1]->Broadcast(elevatorLock);
            while (occupancy > 0) {
                leaving[currentFloor - 1]->Wait(elevatorLock);
            }

            // Allow passengers to enter one at a time
            while (personsWaiting[currentFloor - 1] > 0 && occupancy < 5) {
                entering[currentFloor - 1]->Signal(elevatorLock);
                personsWaiting[currentFloor - 1]--;
                occupancy++;
            }
        }

        elevatorLock->Release();
    }
}

void ELEVATOR::hailElevator(Person* p) {
    elevatorLock->Acquire();

    // Increment waiting persons at the person's current floor
    personsWaiting[p->atFloor - 1]++;
    printf("Person %d hails the elevator on floor %d.\n", p->id, p->atFloor);

    // Wait for the elevator to arrive at the person's floor
    entering[p->atFloor - 1]->Wait(elevatorLock);

    // Person enters the elevator
    printf("Person %d got into the elevator.\n", p->id);

    // Wait for the elevator to reach the destination floor
    leaving[p->toFloor - 1]->Wait(elevatorLock);

    // Person exits the elevator
    printf("Person %d got out of the elevator on floor %d.\n", p->id, p->toFloor);
    occupancy--;

    // Signal that the person has exited
    leaving[p->toFloor - 1]->Signal(elevatorLock);

    elevatorLock->Release();
}

void ElevatorThread(int numFloors) {
    printf("Elevator with %d floors created!\n", numFloors);
    e = new ELEVATOR(numFloors);
    e->start();
}

int getNextPersonID() {
    personIDLock->Acquire();
    int id = nextPersonID++;
    personIDLock->Release();
    return id;
}

void PersonThread(int personPtr) {
    Person* p = (Person*)personPtr;
    printf("Person %d wants to go from floor %d to floor %d.\n", p->id, p->atFloor, p->toFloor);
    e->hailElevator(p);
}

void ArrivingGoingFromTo(int atFloor, int toFloor) {
    Person* p = new Person;
    p->id = getNextPersonID();
    p->atFloor = atFloor;
    p->toFloor = toFloor;

    Thread* t = new Thread("Person " + std::to_string(p->id));
    t->Fork((VoidFunctionPtr)PersonThread, (int)p);
}
