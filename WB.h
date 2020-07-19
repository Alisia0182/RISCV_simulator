
//
// Created by wjy on 2020/7/18.
//
#include "RegisterFile.h"

#ifndef RISCV_SIMULATOR_WB_H
#define RISCV_SIMULATOR_WB_H

class WB{
    RegFile * RegPtr;
public:
    Inst instObj;

    WB(RegFile * _RegPtr):
    RegPtr(_RegPtr)
    {}

    void perform() {
#ifdef basic
        std::cout << "\n\nWB perform begin...\t" << basiccommand;
#endif
        if (instObj.InstType == NOP){
#ifdef NOPreturn
            NOPreturncommand;
#endif
        return;
    }
        if(instObj.BaseType != B && instObj.BaseType != S)
        {
            if(instObj.InstType == LB  || instObj.InstType == LH  || instObj.InstType == LW ||
               instObj.InstType == LBU || instObj.InstType == LHU ) {
                RegPtr->WriteReg(instObj.valMem, instObj.rd);
            }
            else {
                RegPtr->WriteReg(instObj.rstALU, instObj.rd);
            }
            RegPtr->lockRg[instObj.rd] = false;
        }
        
#ifdef basic
        std::cout << "WB performed:\t" << basiccommand;
#endif
    }

};





#endif //RISCV_SIMULATOR_WB_H
