//
// Created by wjy on 2020/7/18.
//


#include "Memory.h"
#include "ID.h"


#ifndef RISCV_SIMULATOR_IF_H
#define RISCV_SIMULATOR_IF_H

class IF{
private:
    RegFile * RegPtr;
    Memory  * MemPtr;

public:
    Inst instObj;

    IF(RegFile * _RegPtr,Memory* _MemPtr):
    RegPtr(_RegPtr),
    MemPtr(_MemPtr){}

    bool perform(){
#ifdef basic
        std::cout << "\nIF perform begin...\t" << basiccommand;
#endif
        if(RegPtr->lockPC){
            instObj.InstType = NOP;
        }
        else{
            instObj.InstType = fetched;
            instObj.pc   = RegPtr->ReadPC();
            instObj.inst = MemPtr->GetInst(instObj.pc);
            if(instObj.inst == 0x0ff00513) {
#ifdef basic
                std::cout << "IF performed:\t" << basiccommand;
#endif
                return true;
            }
        }
#ifdef basic
        std::cout << "IF performed:\t" << basiccommand;
#endif

        return false;
    }

    void pass(ID& IDObj)
    {
        IDObj.instObj = instObj;
    }

    void Clean()
    {
        instObj.InstType = NOP;
    }
};
#endif //RISCV_SIMULATOR_IF_H
