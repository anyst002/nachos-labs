#include "copyright.h"
#include "elevator.h"
#include "system.h"
#include "synch.h"

ELEVATOR* e;  // Global elevator instance
int nextPersonID = 1;
Lock* personIDLock = new Lock("PersonIDLock");  // Lock for generating person IDs

ELEVATOR::ELEVATOR(int numFloors) { //TODO change name for clarity
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
    while (true) {
        elevatorLock->Acquire();

        // If no passengers, release lock and yield
        if (!hasActivePersons()) {
            elevatorLock->Release();

            // Wait for other passengers to show up
            for (int j = 0; j < 1000000; j++) {
                currentThread->Yield();
            }
            
            // If still no passengers, end elevator thread
            if (!hasActivePersons()) {
                break;
            }

            // Else there are passengers, so keep going
            elevatorLock->Acquire();
        }

        // Move the elevator floor by floor
        for (int i = 0; i < numFloors; i++) {
            currentFloor = i + 1;
            printf("Elevator arrives on floor %d\n", currentFloor);

            // Signal all passengers leaving on this floor to leave
            if (personsLeaving[i] != 0) {
                printf("DEBUG - personsLeaving called\n");
                leaving[i]->Broadcast(elevatorLock);
                leaving[i]->Wait(elevatorLock);
                personsLeaving[i] = 0;
            }
            printf("DEBUG - past personsLeaving check\n");
            // Allow passengers to enter one at a time
            while (personsWaiting[i] > 0 && occupancy < 5) {
                printf("DEBUG - personsWaiting called\n");
                entering[i]->Signal(elevatorLock);
                personsWaiting[i]--;
                occupancy++;
            }
            printf("DEBUG - past personsWaiting check\n");
            elevatorLock->Release();
            printf("DEBUG - lock released\n");
            // Simulate travel time (yield to other threads)
            for (int j = 0; j < 500000; j++) {
                currentThread->Yield();
            }
            printf("DEBUG - spinning finished\n");
            elevatorLock->Acquire();
            printf("DEBUG - lock acquired\n");
        }

        elevatorLock->Release();
    }
    printf("DEBUG - elevator thread terminated\n");
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
    personsLeaving[p->toFloor - 1] = 1;

    // Wait for the elevator to reach the destination floor
    leaving[p->toFloor - 1]->Wait(elevatorLock);

    // Person exits the elevator
    printf("Person %d got out of the elevator on floor %d.\n", p->id, p->toFloor);
    occupancy--;

    // Signal that the person has exited
    leaving[p->toFloor - 1]->Signal(elevatorLock); //TODO signals threads to leave until fully empty

    elevatorLock->Release();
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
    printf("Person %d wants to go from floor %d to floor %d.\n", p->id, p->atFloor, p->toFloor);
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
