// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h" // <- Syscall codes and functions are defined here.
#include "system.h"  // included twice, may not be an issue, just noting

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------


void doExit(int status) {

    // Get process id
    int pid = currentThread->space->pcb->pid;

    printf("System Call: [%d] invoked Exit\n", pid);
    printf ("Process [%d] exits with [%d]\n", pid, status);

    currentThread->space->pcb->exitStatus = status;

    // Manage PCB memory As a parent process
    PCB* pcb = currentThread->space->pcb;

    // Delete exited children and set parent null for non-exited ones
    pcb->DeleteExitedChildrenSetParentNull();

    // TODO: Supply status to parent process if and when it does a Join()
    // Most likely that will go here 
    // "if current process has a parent, remove itself from the children list 
    //  of its parent process and set child exit value to parent"

    // Manage PCB memory As a child process
    if (pcb->parent != NULL) {
        pcb->parent->RemoveChild(pcb);
    }
    pcbManager->DeallocatePCB(pcb);

    // Delete address space only after use is completed
    delete currentThread->space;

    // Finish current thread only after all the cleanup is done
    // because currentThread marks itself to be destroyed (by a different thread)
    // and then puts itself to sleep -- thus anything after this statement will not be executed!
    currentThread->Finish();

}

void incrementPC() {
    int oldPCReg = machine->ReadRegister(PCReg);

    machine->WriteRegister(PrevPCReg, oldPCReg);
    machine->WriteRegister(PCReg, oldPCReg + 4);
    machine->WriteRegister(NextPCReg, oldPCReg + 8);
}

// Helper function for doFork()
void childFunction(int pid) {

    // 1. Restore the state of registers
    currentThread->RestoreUserState();

    // 2. Restore the page table for child
    currentThread->space->RestoreState();

    machine->Run();

}

int doFork(int functionAddr) {
    // Check input is reasonable?

    // Get process id
    int pid = currentThread->space->pcb->pid;

    printf("System Call: [%d] invoked Fork\n", pid);

    if (currentThread->space->GetNumPages() > mm->GetFreePageCount()) {
        printf("Process [%d] does not have enough memory to Fork!\n", pid); //TODO delete later
        return -1;
    }

    // 2. SaveUserState for the parent thread
    currentThread->SaveUserState();

    // 3. Create a new address space for child by copying parent address space
    // 4. Create a new thread for the child and set its addrSpace
    Thread* childThread = new Thread("childThread");
    childThread->space = new AddrSpace(currentThread->space);

    // 5. Create a PCB for the child and connect it all up
    PCB* childPCB = pcbManager->AllocatePCB();
    childPCB->thread = childThread;
    // set parent for child pcb
    childPCB->parent = currentThread->space->pcb;
    // add child for parent pcb
    currentThread->space->pcb->AddChild(childPCB);
    // initialize pcb in childAddSpace
    childThread->space->pcb = childPCB;

    // 6. Set up machine registers for child and save it to child thread
    machine->WriteRegister(PCReg, functionAddr);
    machine->WriteRegister(PrevPCReg, functionAddr - 4);
    machine->WriteRegister(NextPCReg, functionAddr + 4);
    childThread->SaveUserState();

    // 7. Restore register state of parent user-level process
    currentThread->RestoreUserState();

    // 8. Call thread->fork on Child
    childThread->Fork(childFunction, childPCB->pid);

    int pcreg = machine->ReadRegister(PCReg);
    printf("Process [%d] Fork: start at address [%p] with [%d] pages memory\n", pid, pcreg, currentThread->space->GetNumPages());

    return childPCB->pid;

}

int doExec(char* filename) {

    // Get process id
    int pid = currentThread->space->pcb->pid;

    printf("System Call: [%d] invoked Exec\n", pid);
    printf("Exec Program: [%d] loading [%s]\n", pid, filename);

    // Use progtest.cc:StartProcess() as a guide

    // 1. Open the file and check validity
	
    // OpenFile *executable = fileSystem->Open(filename);
    // AddrSpace *space;

    // if (executable == NULL) {
    //     printf("Unable to open file %s\n", filename);
    //     return -1;
    // }
	OpenFile* executable = fileSystem->Open(filename);
    if (executable == NULL) {
        printf("Unable to open file %s\n", filename);
        return -1; // Return error if the file can't be opened
    }

    // 2. Delete current address space but store current PCB first if using in Step 5.
    // PCB* pcb = currentThread->space->pcb;
    // delete currentThread->space;
    PCB* pcb = currentThread->space->pcb;
	
    // 3. Create new address space
    // space = new AddrSpace(executable);
    delete currentThread->space;

    // 4.     delete executable;			// close file
    AddrSpace* space = new AddrSpace(executable);
    delete executable;

    // 5. Check if Addrspace creation was successful
    // if(space->valid != true) {
    // printf("Could not create AddrSpace\n");
    //     return -1;
    // }
    if (!space->valid) { 
        printf("Could not create AddrSpace for [%s]\n", filename);
        return -1; // Return error if address space creation failed
    }
    // 6. Set the PCB for the new addrspace - reused from deleted address space
    // space->pcb = pcb;
    space->pcb = pcb;

    // 7. Set the addrspace for currentThread
    // currentThread->space = space;
    currentThread->space = space;

    // 8. Initialize registers for new addrspace
    //  space->InitRegisters();		// set the initial register values
    space->InitRegisters(); 

    // 9. Initialize the page table
    // space->RestoreState();		// load page table register
    space->RestoreState();

    // 10. Run the machine now that all is set up
    // machine->Run();			// jump to the user progam
    // ASSERT(FALSE); // Execution nevere reaches here
    machine->Run(); // Begin execution (control will not return to this function)
    ASSERT(FALSE);

    return 0;
}


int doJoin(int pid) {

    // Get process id
    int parentPid = currentThread->space->pcb->pid;

    printf("System Call: [%d] invoked Join\n", parentPid);

    // 1. Check if this is a valid pid and return -1 if not
    PCB* joinPCB = pcbManager->GetPCB(pid);
    if (joinPCB == NULL) return -1;

    // 2. Check if pid is a child of current process
    if (currentThread->space->pcb != joinPCB->parent) return -1;

    // 3. Yield while joinPCB has not exited
    while(!joinPCB->HasExited()) currentThread->Yield();

    // 4. Store status and delete joinPCB
    int status = joinPCB->exitStatus;
    //delete joinPCB;

    return status;

}


int doKill (int pid) {

    // Get process id
    int curPid = currentThread->space->pcb->pid;

    printf("System Call: [%d] invoked Kill\n", curPid);

    // 1. Check if the pid is valid and if not, return -1
    PCB* killPCB = pcbManager->GetPCB(pid);
    if (killPCB == NULL) {
        printf("Process [%d] cannot kill process [%d]: doesn't exist\n", curPid, pid);
        return -1;
    }

    // 2. IF pid is self, then just exit the process
    if (killPCB == currentThread->space->pcb) {
        printf("Process [%d] killed itself\n", curPid);
        doExit(0);
        return 0;
    }

    // 3. Valid kill, pid exists and not self, do cleanup similar to Exit

    // Delete exited children and set parent null for non-exited ones
    killPCB->DeleteExitedChildrenSetParentNull();

    // Remove killed thread from children list of parent if available
    if (killPCB->parent != NULL) {
        killPCB->parent->RemoveChild(killPCB);
    }
    
    // Delete address space, set thread to be destroyed
    delete killPCB->thread->space;
    scheduler->RemoveThread(killPCB->thread);

    pcbManager->DeallocatePCB(killPCB);

    printf("Process [%d] killed process [%d]\n", curPid, pid);

    return 0;
}



void doYield() {

    // Get process id
    int pid = currentThread->space->pcb->pid;

    printf("System Call: [%d] invoked Yield\n", pid);

    currentThread->Yield();
}





// This implementation (discussed in one of the videos) is broken!
// Try and figure out why.
char* readString1(int virtAddr) {

    unsigned int pageNumber = virtAddr / 128;
    unsigned int pageOffset = virtAddr % 128;
    unsigned int frameNumber = machine->pageTable[pageNumber].physicalPage;
    unsigned int physicalAddr = frameNumber*128 + pageOffset;

    char *string = &(machine->mainMemory[physicalAddr]);

    return string;

}










// This implementation is correct!
// perform MMU translation to access physical memory
char* readString(int virtualAddr) {
    int i = 0;
    char* str = new char[256];
    unsigned int physicalAddr = currentThread->space->Translate(virtualAddr);

    // Need to get one byte at a time since the string may straddle multiple pages that are not guaranteed to be contiguous in the physicalAddr space
    bcopy(&(machine->mainMemory[physicalAddr]),&str[i],1);
    while(str[i] != '\0' && i != 256-1)
    {
        virtualAddr++;
        i++;
        physicalAddr = currentThread->space->Translate(virtualAddr);
        bcopy(&(machine->mainMemory[physicalAddr]),&str[i],1);
    }
    if(i == 256-1 && str[i] != '\0')
    {
        str[i] = '\0';
    }

    return str;
}

void doCreate(char* fileName)
{
    printf("Syscall Call: [%d] invoked Create.\n", currentThread->space->pcb->pid);
    fileSystem->Create(fileName, 0);
}

// Checks each syscall code, exits after one is run.
// If no valid excpetion/syscall is run, outputs a debug message.
// Each syscall calls its related do subroutine (Fork calls doFork, etc.)
// The actual syscall code is run in its related subroutine above.
// The subroutine output is then supplied back here and written back to the machine.
// Finally, the incrementPC() is called to update the program counter.
void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    } else  if ((which == SyscallException) && (type == SC_Exit)) {
        doExit(machine->ReadRegister(4));
    } else if ((which == SyscallException) && (type == SC_Fork)) {
        int ret = doFork(machine->ReadRegister(4));
        machine->WriteRegister(2, ret);
        incrementPC();
    } else if ((which == SyscallException) && (type == SC_Exec)) {
        int virtAddr = machine->ReadRegister(4);
        char* fileName = readString(virtAddr);
        int ret = doExec(fileName);
        machine->WriteRegister(2, ret);
        incrementPC();
    } else if ((which == SyscallException) && (type == SC_Join)) {
        int ret = doJoin(machine->ReadRegister(4));
        machine->WriteRegister(2, ret);
        incrementPC();
    } else if ((which == SyscallException) && (type == SC_Kill)) {
        int ret = doKill(machine->ReadRegister(4));
        machine->WriteRegister(2, ret);
        incrementPC();
    } else if ((which == SyscallException) && (type == SC_Yield)) {
        doYield();
        incrementPC();
    } else if((which == SyscallException) && (type == SC_Create)) {
        int virtAddr = machine->ReadRegister(4);
        char* fileName = readString(virtAddr);
        doCreate(fileName);
        incrementPC();
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}

