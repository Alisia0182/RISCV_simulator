//
// Created by wjy on 2020/7/18.
//

#include "Predictor.h"
#include "RegisterFile.h"
#include "Instruction.h"
#include "EX.h"


#ifndef RISCV_SIMULATOR_ID_H
#define RISCV_SIMULATOR_ID_H

class ID{
    Predictor* PredPtr;
    RegFile  * RegPtr;
public:
    Inst instObj;
    bool readSuc;// whether regRs1 regRs2 is available

    ID(Predictor * _PredPtr,RegFile * _RegPtr):
    PredPtr(_PredPtr),RegPtr(_RegPtr),readSuc(1){}

    void perform() {
#ifdef basic
        std::cout << "\nID perform begin...\t" << basiccommand;
#endif
        if (instObj.InstType == NOP) {
#ifdef NOPreturn
            NOPreturncommand;
#endif
            return;
        }
        if (instObj.InstType == fetched) {
            instObj.GetType();
            instObj.Decode();

            // ReadReg:
            readSuc = true;
            switch (instObj.BaseType) {
                case R:
                case S:
                case B: {
                    if (RegPtr->lockRg[instObj.rs1] || RegPtr->lockRg[instObj.rs2])
                        readSuc = false;
                    else {
                        instObj.regRs1 = RegPtr->ReadReg(instObj.rs1);
                        instObj.regRs2 = RegPtr->ReadReg(instObj.rs2);
                    }
                    break;
                }
                case I: {
                    if (RegPtr->lockRg[instObj.rs1])
                        readSuc = false;
                    else
                        instObj.regRs1 = RegPtr->ReadReg(instObj.rs1);
                    break;
                }
            }

            //ChangePC:
            if (readSuc) {
                //锁Reg
                if (instObj.BaseType != B && instObj.BaseType != S) {
                    RegPtr->lockRg[instObj.rd] = true;
                }

                if (instObj.InstType == JALR) {
                    RegPtr->WritePC((instObj.regRs1 + instObj.imm) & (~1));
                } else if (instObj.InstType == JAL) {
                    RegPtr->AddPC(instObj.imm);
                } else if (instObj.BaseType != B) {
                    RegPtr->AddPC(4);
                } else {
                    instObj.predRst = PredPtr->pred(instObj.index);
                    if (instObj.predRst)
                        RegPtr->AddPC(instObj.imm);
                        //老子猜一个，跳了再说
                    else//猜你不跳，要是EX的时候发现要跳了再去解决问题
                        RegPtr->AddPC(4);
                }
            }
            //else pass的时候塞NOP指令

#ifdef basic
            std::cout << "ID performed:\t" << basiccommand;
#endif
        }
    }
    void pass(EX & EXobj)
    {
        if(!readSuc)
            EXobj.instObj.InstType = NOP;//塞一条空指令
        else
            EXobj.instObj = instObj;//传下去，欸嘿嘿
    }

    void Clean(){
        instObj.InstType = NOP;
    }
};

#endif //RISCV_SIMULATOR_ID_H
