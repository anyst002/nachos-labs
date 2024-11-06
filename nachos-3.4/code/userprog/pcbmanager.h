#ifndef PCBMANAGER_H
#define PCBMANAGER_H

#include "synch.h"
#include "bitmap.h"
#include "pcb.h"

class PCB;

class PCBManager {

    public:
        PCBManager(int maxProcesses);
        ~PCBManager();

        PCB* AllocatePCB();
        int DeallocatePCB(PCB* pcb);
        PCB* GetPCB(int pid);

    private:
        BitMap* bitmap;
        PCB** pcbs;
        Lock* pcbManagerLock;

};

#endif // PCBMANAGER_H