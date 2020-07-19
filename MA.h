
//
// Created by wjy on 2020/7/18.
//

#include "Memory.h"
#include "WB.h"

#ifndef RISCV_SIMULATOR_MA_H
#define RISCV_SIMULATOR_MA_H

class MA{
Memory * MemPtr;

public:
    Inst instObj;

    MA(Memory * _MemPtr):
    MemPtr(_MemPtr){}


    void perform()
    {
#ifdef basic
        std::cout << "\nMA perform begin...\t" << basiccommand;
#endif
        if(instObj.InstType == NOP) {
#ifdef NOPreturn
            NOPreturncommand;
#endif
            return;
        }

        switch(instObj.InstType) {
            case SW:
                MemPtr->WriteMem(instObj.regRs2 << 0  >> 24,instObj.rstALU + 3);
                MemPtr->WriteMem(instObj.regRs2 << 8  >> 24,instObj.rstALU + 2);
#ifdef extradebug
                std::cout << "MA line 42\n";
#endif
            case SH:
                MemPtr->WriteMem(instObj.regRs2 << 16 >> 24, instObj.rstALU + 1);
#ifdef extradebug
                std::cout << "MA line 47\n";
#endif
            case SB:
                 MemPtr->WriteMem(instObj.regRs2 << 24 >> 24,instObj.rstALU);
#ifdef extradebug
                std::cout << "MA line 52\n";
#endif
                break;
            case LB:{
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU);
                if(instObj.valMem & (1<<7)) {
                    instObj.valMem |= (0xffffffff >> 8 << 8);
                }
#ifdef extradebug
                std::cout << "MA line 60\n";
#endif
                break;
            }
            case LH:
                {
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU + 1);
                instObj.valMem <<= 8;
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU);
                if(instObj.valMem & (1<<15))
                    instObj.valMem |= (0xffffffff>>15<<15);
#ifdef extradebug
                std::cout << "MA line 72\n";
#endif
                break;
                }
            case LW:
                {
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU + 3);
                instObj.valMem <<= 8;
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU + 2);
                instObj.valMem <<= 8;
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU + 1);
                instObj.valMem <<= 8;
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU);
#ifdef extradebug
                std::cout << "MA line 86\n";
#endif
                break;
                }
            case LBU:
                {
                    instObj.valMem |= MemPtr->ReadMem(instObj.rstALU);
#ifdef extradebug
                std::cout << "MA line 94\n";
#endif
                    break;
                }
            case LHU:
            {
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU + 1);
                instObj.valMem <<= 8;
                instObj.valMem |= MemPtr->ReadMem(instObj.rstALU);
#ifdef extradebug
                std::cout << "MA line 104\n";
#endif
                break;
            }

        }

#ifdef LS
switch(instObj.InstType)
{
    case LB:{
        std::cout <<"LB:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  << "\t rd:"
                  << std::hex << std::setw(2) << std::setfill('0') << instObj.rd
                  << '\n';
        break;
    }
    case LBU:
    {
        std::cout <<"LBU:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  << "\t rd:"
                  << std::hex << std::setw(2) << std::setfill('0') << instObj.rd
                  << '\n';
        break;
    }
    case LH:
    {
        std::cout <<"LH:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  <<"\tMem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 1 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 1)
                  << "\t rd:"
                  << std::hex << std::setw(2) << std::setfill('0') << instObj.rd
                  << '\n';
        break;
    }
    case LW:
    {
        std::cout <<"LW:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 1 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 1)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 2 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 2)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 3 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 3)
                  << "\t rd:"
                  << std::hex << std::setw(2) << std::setfill('0') << instObj.rd
                  << '\n';
        break;
    }
    case LHU:
    {
        std::cout <<"LHU:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  <<"\tMem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 1 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 1)
                  << "\t rd:"
                  << std::hex << std::setw(2) << std::setfill('0') << instObj.rd
                  << '\n';
        break;
    }
    case SB:
    {

        std::cout <<"SB:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  << '\n';
    }
    case SH:
    {
        std::cout <<"SH:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 1 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 1)
                  << '\n';
    }
    case SW:
    {
        std::cout <<"SW:\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 1 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 1)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 2 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 2)
                  <<"\t Mem["
                  << std::hex << std::setw(8) << std::setfill('0') << instObj.rstALU + 3 <<"]\t"
                  << std::hex << std::setw(2) << std::setfill('0') << (uint)MemPtr->ReadMem(instObj.rstALU + 3)
                  << '\n';
    }

}
#endif



#ifdef basic
        std::cout << "MA performed:\t" << basiccommand;
#endif
    }

    void pass(WB & WBobj)
    {
        WBobj.instObj = instObj;
    }
};



#endif //RISCV_SIMULATOR_MA_H
