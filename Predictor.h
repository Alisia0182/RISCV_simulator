//
// Created by wjy on 2020/7/18.
//
#include <iostream>
#include <iomanip>
#include <memory.h>
#include "Common.h"

using std::cout;
#ifndef RISCV_SIMULATOR_PREDICTOR_H
#define RISCV_SIMULATOR_PREDICTOR_H

const uint tableSize = 0x2000;

class Predictor {
private:
    uint sucNum, totalNum;//10 0000 0000 0000
    uchar BHTable[tableSize];//Branch History Table

    void addJump(uchar &counter) {
        if (counter ^ 1)//末位0
            counter |= 1;
        else//末位1
        {
            if (counter & 2)//高位1
                return;
            else
                counter |= 2;
        }
    }

    void subJump(uchar &counter) {
        if (counter & 1) //低位1  11 01
            counter &= (~1);//~1: 111111…… 0，低位设为0
        else            //低位0
        {
            if (counter & 1)//高位1 10
                counter = 1;
            //00
        }
    }

public:
    Predictor() {
        sucNum = totalNum = 0;
        memset(BHTable, 0, tableSize);
    }

    void Clean()
    {
        sucNum = totalNum = 0;
        memset(BHTable,0,tableSize);
    }

    bool pred(uint index)
    {
        if(BHTable[index] >> 1)) return true;//高位是1
        return false;
    }

    void record(uint index,bool predJmp, bool predSuc){
        ++totalNum;
        if(predSuc)
        {
            ++sucNum;
            if(predJmp)
                addJump(BHTable[index]);
            else
                subJump(BHTable[index]);
        }
        else
        {
            if(predJmp)
                subJump(BHTable[index]);
            else
                addJump(BHTable[index]);
        }
    }


    void DebugFunct(){
        std::cout <<    "Prediction Num: " << totalNum
        << "\t Succeeded Prediction Num: " << sucNum    << '\n';
        std::cout <<      "Success Rate: " << std::setprecision(8)
                  << ((double)(sucNum)/totalNum ) * 100 << "%\n";
    }
};
#endif //RISCV_SIMULATOR_PREDICTOR_H
