#include "copyright.h"
#include "elevator.h"
#include "system.h"
#include "synch.h"

ELEVATOR* e;  // Global elevator instance
int nextPersonID = 1;
Lock* personIDLock = new Lock("PersonIDLock");  // Lock for generating person IDs

ELEVATOR::ELEVATOR(int numFloors) {
    this->numFloors = numFloors;
    this->currentFloor = 1;
    this->occupancy = 0;

    personsWaiting = new int[numFloors]();  // Initialize waiting counts to 0
    personsLeaving = new int[numFloors]();  // Initialize leaving flags to 0

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
    elevatorLock->Acquire();

    // Wait for person to appear
    if (finished()) {
        return;
    }

    bool run = true;

    while (run) {
        // Move the elevator floor by floor upwards
        for (int i = 0; i < numFloors - 1; i++) {
            if (!run) {
                break;
            }
            run = moveElevator(i);
        }

        // Move the elevator floor by floor downwards
        for (int i = numFloors - 1; i > 0; i--) {
            if (!run) {
                break;
            }
            run = moveElevator(i);
        }
    }
}

// elevatorLock MUST be acquired before calling
bool ELEVATOR::moveElevator(int i) {
    currentFloor = i + 1;
    printf("Elevator arrives on floor %d.\n", currentFloor);

    // Signal all passengers leaving on this floor to leave
    if (personsLeaving[i] != 0) {
        leaving[i]->Broadcast(elevatorLock);
        leaving[i]->Wait(elevatorLock);
        personsLeaving[i] = 0;

        // Make sure there are more passengers to serve
        if (occupancy == 0 && finished()) {
            return false;
        }
    }

    // Allow passengers to enter one at a time
    while (personsWaiting[i] > 0 && occupancy < 5) {
        entering[i]->Signal(elevatorLock);
        personsWaiting[i]--;
        occupancy++;
    }

    elevatorLock->Release();

    // Simulate travel time (yield to other threads)
    for (int j = 0; j < 50; j++) {
        currentThread->Yield();
    }

    elevatorLock->Acquire();

    return true;
}

void ELEVATOR::hailElevator(Person* p) {
    elevatorLock->Acquire();

    // Increment waiting persons at the person's current floor
    personsWaiting[p->atFloor - 1]++;

    // Wait for the elevator to arrive at the person's floor
    entering[p->atFloor - 1]->Wait(elevatorLock);

    // Person enters the elevator
    printf("Person %d got into the elevator.\n", p->id);
    personsLeaving[p->toFloor - 1] = 1;

    // Wait for the elevator to reach the destination floor
    leaving[p->toFloor - 1]->Wait(elevatorLock);

    // Person exits the elevator
    printf("Person %d got out of the elevator.\n", p->id);
    occupancy--;

    // Signal that the person has exited
    leaving[p->toFloor - 1]->Signal(elevatorLock);

    elevatorLock->Release();
}

bool ELEVATOR::finished() {
    // If no passengers, release lock and yield
    if (!hasActivePersons()) {
        elevatorLock->Release();

        // Wait for other passengers to show up
        for (int j = 0; j < 1000000; j++) {
            currentThread->Yield();
        }

        // If still no passengers, end elevator thread
        if (!hasActivePersons()) {
            return true;
        }

        // Else there are passengers, so keep going
        elevatorLock->Acquire();
    }
    return false;
}

bool ELEVATOR::hasActivePersons() {
    bool hasPassengers = false;

    // Check each floor for people waiting
    for (int i = 0; i < numFloors; i++) {
        if (personsWaiting[i] > 0) {
            hasPassengers = true;
            break;
        }
    }

    // If no persons waiting and elevator is empty, return false
    if (!hasPassengers && occupancy == 0) {
        return false;
    }

    // Else there are active persons, so return true
    return true;
}

void ElevatorThread(int numFloors) {
    printf("Elevator with %d floors created!\n", numFloors);
    e = new ELEVATOR(numFloors);
    e->start();
}

void Elevator(int numFloors) {
    // Create Elevator Thread
    Thread* t = new Thread("Elevator");
    t->Fork(ElevatorThread, numFloors);
}

int getNextPersonID() {
    personIDLock->Acquire();
    int id = nextPersonID++;
    personIDLock->Release();
    return id;
}

void PersonThread(int personPtr) {
    Person* p = (Person*)personPtr;
    printf("Person %d wants to go to floor %d from floor %d.\n", p->id, p->toFloor, p->atFloor);
    e->hailElevator(p);
}

void ArrivingGoingFromTo(int atFloor, int toFloor) {
    // Create Person struct
    Person* p = new Person;
    p->id = getNextPersonID();
    p->atFloor = atFloor;
    p->toFloor = toFloor;

    // Create Person Thread
    Thread* t = new Thread("Person " + p->id);
    t->Fork((VoidFunctionPtr)PersonThread, (int)p);
}
