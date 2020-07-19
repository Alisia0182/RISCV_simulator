//
// Created by wjy on 2020/7/18.
//
#include <iostream>
#include <fstream>
#include <memory.h>
#include <string>
#include "Common.h"

#ifndef RISCV_SIMULATOR_MEMORY_H
#define RISCV_SIMULATOR_MEMORY_H

using std::string;

const uint MaxMem = 0x000fffff;
class Memory{
    uchar Mem[MaxMem];

public:
    Memory()
    {
        memset(Mem,0,MaxMem);
    }

    void ReadFile(const char * _FileName)
    {
        std::ifstream in(_FileName);
        string tmp;
        uint pst,num;
        bool isPst;
        std::cin.rdbuf(in.rdbuf());

        while(std::cin >> tmp){
            num = ToUint(tmp,isPst);
            if(isPst) {
                pst = num;
            }
            else{
                Mem[pst]  = (uchar)num;
                for(uint i = 0;i<3;++i){
                    std::cin >> tmp;
                    Mem[pst + i + 1] = (uchar)ToUint(tmp);
                }
                pst += 4;
            }
        }
        in.close();
    }

    void ReadIn()
    {
        string tmp;
        uint pst,num;
        bool isPst;

        while(std::cin >> tmp){
            num = ToUint(tmp,isPst);
            if(isPst) {
                pst = num;
            }
            else{
                Mem[pst]  = (uchar)num;
                for(uint i = 0;i<3;++i){
                    std::cin >> tmp;
                    Mem[pst + i + 1] = (uchar)ToUint(tmp);
                }
                pst += 4;
            }
        }
    }

    void Clean()
    {
        memset(Mem,0,sizeof(Mem));
    }

    void WriteMem(const uchar& value,uint pst ){
        Mem[pst] = value;
    }

    uchar ReadMem(uint pst){
        ///范围检查？？
        return Mem[pst];
    }

    uint GetInst(uint pst){
        uint rst = 0;

        for(uint i = 0;i<4;++i)
        {
            rst += (Mem[pst+i]&255)<< (i<< 3);//bug: 没有&255
        }

        return rst;
    }

};
#endif //RISCV_SIMULATOR_MEMORY_H
