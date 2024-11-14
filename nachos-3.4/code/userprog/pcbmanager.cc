#include "pcbmanager.h"
#include "synch.h"

PCBManager::PCBManager(int maxProcesses) {

    bitmap = new BitMap(maxProcesses);
    pcbs = new PCB*[maxProcesses];
    pcbManagerLock = new Lock("PCBManagerLock");

    for(int i = 0; i < maxProcesses; i++) {
        pcbs[i] = NULL;
    }

}


PCBManager::~PCBManager() {

    delete bitmap;

    delete pcbs;

    delete pcbManagerLock;
}


PCB* PCBManager::AllocatePCB() {

    pcbManagerLock->Acquire();

    int pid = bitmap->Find();

    pcbManagerLock->Release();

    ASSERT(pid != -1);

    pcbs[pid] = new PCB(pid);

    return pcbs[pid];

}


int PCBManager::DeallocatePCB(PCB* pcb) {

    // Check is pcb is valid -- check pcbs for pcb->pid
    // if(pcbs[pcb->pid] == NULL || pcbs[pcb->pid] != pcb) {
    //     throw exception and break
    // }

    pcbManagerLock->Acquire();

    bitmap->Clear(pcb->pid);

    pcbManagerLock->Release();

    int pid = pcb->pid;

    delete pcbs[pid];

    pcbs[pid] = NULL;

    return 0;

}

PCB* PCBManager::GetPCB(int pid) {
    return pcbs[pid];
}