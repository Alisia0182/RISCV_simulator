//
// Created by wjy on 2020/7/18.
//

#include <memory.h>
#include <iostream>
#include <iomanip>

#include "Common.h"
#ifndef RISCV_SIMULATOR_REGISTERFILE_H
#define RISCV_SIMULATOR_REGISTERFILE_H

class RegFile{
    uint regs[32];
    uint PC;

public:
    bool lockRg[32];
    bool lockPC;

    RegFile(uint _PC = 0):
    PC(_PC), lockPC(0)
    {
        memset(regs  ,0,sizeof(uint) * 32);
        memset(lockRg,0,sizeof(bool) * 32);
    }

    inline void WriteReg(uint value, uint pos)
    {
        if(pos == 0) return;
        regs[pos & 255u] = value;
    }

    inline uint ReadReg(uint pos)
    {
        return regs[pos & 255u];
    }

    inline void AddPC(const int & offset)
    {
        PC += offset;
    }

    inline void WritePC(const uint & _PC)
    {
        PC = _PC;
    }

    inline uint ReadPC()
    {
        return PC;
    }

    inline void Clean()
    {
        PC = lockPC = 0;
        memset(regs,0,32 * sizeof(uint));
        memset(lockRg,0,32 * sizeof(bool));
    }

    void DebugFunct()
    {
        std::cout << '\n';

        for(int i = 0;i < 32; ++ i)
        {
            if(!(i%4)) std::cout << '\n';

               std::cout << std::setw(2) << std::setfill('0') << i      << ":\t"
            << std::hex  << std::setw(8) << std::setfill('0') << regs[i]<< '\t';
        }

        std::cout << '\n';
    }

    void DebugFunct2()
    {        std::cout << '\n';

        for(int i = 0;i < 32; ++ i)
        {
            if(!(i%4)) std::cout << '\n';

            std::cout << std::setw(2) << std::setfill('0') << i      << ":\t"<< lockRg[i]<< '\t';
        }

        std::cout << '\n';

    }

};





#endif //RISCV_SIMULATOR_REGISTERFILE_H
