
//
// Created by wjy on 2020/7/18.
//

#include "Predictor.h"
#include "MA.h"
#include "Common.h"

#ifndef RISCV_SIMULATOR_EX_H
#define RISCV_SIMULATOR_EX_H

class EX{
    Predictor * predPtr;
    RegFile   * regPtr;
public:
    Inst instObj;
    EX(Predictor * _predPtr,RegFile * _regPtr):
    predPtr(_predPtr), regPtr(_regPtr)
    {}

    bool perform()
    {
#ifdef basic
        std::cout << "\nEX perform begin...\t" << basiccommand;
#endif
        bool preSuc = true;//不需要清空IF
        switch(instObj.InstType)
        {
            case NOP: {
#ifdef NOPreturn
                NOPreturncommand;
#endif
                return true;
            }case LUI: {
                instObj.rstALU = instObj.imm;
                break;
            }
                case AUIPC:
                {
                instObj.rstALU = instObj.pc + instObj.imm;
                break;
                }
              //无脑跳👇
            case JAL:
            case JALR:
            {
                instObj.rstALU = instObj.pc + 4;
                break;
            }

            case BEQ:
            {
                instObj.jumpRst = (instObj.regRs1 == instObj.regRs2);
#ifdef BRANCHPREDICTION
                std::cout << "BEQ \t pc:\t" <<std::hex << std::setw(4) << std::setfill('0') << instObj.pc
                        << "\tRs1:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs1
                        << "\tregRs1:\t"<<std::hex << std::setw(8) <<std::setfill('0')  << instObj.regRs1
                        << "\tRs2:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs2
                        << "\tregRs2:\t"<<std::hex << std::setw(8) <<std::setfill('0')  <<  instObj.regRs2
                        << "jumpRst:\t" << (instObj.jumpRst?"true": "false")<< "\n";
#endif
                break;
            }
            case BNE:
            {
                instObj.jumpRst = (instObj.regRs1 != instObj.regRs2);
#ifdef BRANCHPREDICTION
                std::cout << "BNE \t pc:\t" <<std::hex << std::setw(4) << std::setfill('0') << instObj.pc
                        << "\tRs1:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs1
                        << "\tregRs1:\t"<<std::hex << std::setw(8) <<std::setfill('0')  << instObj.regRs1
                        << "\tRs2:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs2
                        << "\tregRs2:\t"<<std::hex << std::setw(8) <<std::setfill('0')  <<  instObj.regRs2
                        << "jumpRst:\t" << (instObj.jumpRst?"true": "false")<< "\n";
#endif
                break;
            }
            case BLT:
            {
                instObj.jumpRst = lessCmpSigned(instObj.regRs1,instObj.regRs2);
#ifdef BRANCHPREDICTION
                std::cout << "BLT \t pc:\t" <<std::hex << std::setw(4) << std::setfill('0') << instObj.pc
                        << "\tRs1:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs1
                        << "\tregRs1:\t"<<std::hex << std::setw(8) <<std::setfill('0')  << instObj.regRs1
                        << "\tRs2:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs2
                        << "\tregRs2:\t"<<std::hex << std::setw(8) <<std::setfill('0')  <<  instObj.regRs2
                        << "jumpRst:\t" << (instObj.jumpRst?"true": "false")<< "\n";
#endif
                break;
            }
            case BGE:
            {
                instObj.jumpRst = !lessCmpSigned(instObj.regRs1,instObj.regRs2);
#ifdef BRANCHPREDICTION
                std::cout << "BGE \t pc:\t" <<std::hex << std::setw(4) << std::setfill('0') << instObj.pc
                        << "\tRs1:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs1
                        << "\tregRs1:\t"<<std::hex << std::setw(8) <<std::setfill('0')  << instObj.regRs1
                        << "\tRs2:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs2
                        << "\tregRs2:\t"<<std::hex << std::setw(8) <<std::setfill('0')  <<  instObj.regRs2
                        << "jumpRst:\t" << (instObj.jumpRst?"true": "false")<< "\n";
#endif
                break;
            }
            case BLTU:
            {
                instObj.jumpRst = (instObj.regRs1  < instObj.regRs2);
#ifdef BRANCHPREDICTION
                std::cout << "BLTU \t pc:\t" <<std::hex << std::setw(4) << std::setfill('0') << instObj.pc
                        << "\tRs1:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs1
                          << "\tregRs1:\t"<<std::hex << std::setw(8) <<std::setfill('0')  << instObj.regRs1
                          << "\tRs2:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs2
                          << "\tregRs2:\t"<<std::hex << std::setw(8) <<std::setfill('0')  <<  instObj.regRs2
                          << "jumpRst:\t" << (instObj.jumpRst?"true": "false")<< "\n";
#endif
                break;
            }
            case BGEU:
            {
                instObj.jumpRst = (instObj.regRs1 >= instObj.regRs2);
#ifdef BRANCHPREDICTION
                std::cout << "BGEU \t pc:\t" <<std::hex << std::setw(4) << std::setfill('0') << instObj.pc
                        << "\tRs1:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs1
                        << "\tregRs1:\t"<<std::hex << std::setw(8) <<std::setfill('0')  << instObj.regRs1
                        << "\tRs2:\t"<<std::hex << std::setw(2) <<std::setfill('0')  << instObj.rs2
                        << "\tregRs2:\t"<<std::hex << std::setw(8) <<std::setfill('0')  <<  instObj.regRs2
                        << "jumpRst:\t" << (instObj.jumpRst?"true": "false")<< "\n";
#endif
                break;
            }
            case LB:
            case LH:
            case LW:
            case LBU:
            case LHU:
            case SB:
            case SH:
            case SW:
            case ADDI:
            {
                instObj.rstALU = instObj.regRs1 + instObj.imm;
                break;
            }
            case SLTI:
            {
                instObj.rstALU = ((int)instObj.regRs1 < instObj.imm);//?
                break;
            }
            case SLTIU:
            {
                instObj.rstALU = (instObj.regRs1 < (uint)instObj.imm);
                break;
            }
            case XORI:
            {
                instObj.rstALU = instObj.regRs1 ^ instObj.imm;
                break;
            }
            case ORI:
            {
                instObj.rstALU = instObj.regRs1 | instObj.imm;
                break;
            }
            case ANDI:
            {
                instObj.rstALU = instObj.regRs1 & instObj.imm;
                break;
            }
            case SLLI:
            {
                instObj.rstALU = instObj.regRs1 << instObj.rs2;
                break;
            }
            case SRLI:
            {
                instObj.rstALU = instObj.regRs1 >> instObj.rs2;
                break;
            }
            case SRAI:
            {
                instObj.rstALU = ((int)instObj.regRs1) >> instObj.rs2;
                break;
            }
            case ADD:
            {
                instObj.rstALU = instObj.regRs1 + instObj.regRs2;
                break;
            }
            case SUB:
            {
                instObj.rstALU = instObj.regRs1 - instObj.regRs2;
                break;
            }
            case SLL:
            {
                instObj.rstALU = instObj.regRs1 << (instObj.regRs2 &0x1f);
                break;
            }
            case SLT:
            {
                instObj.rstALU = lessCmpSigned(instObj.regRs1,instObj.regRs2);
                break;
            }
            case SLTU:
            {
                instObj.rstALU = (instObj.regRs1 < instObj.regRs2);
                break;
            }
            case XOR:
            {
                instObj.rstALU = instObj.regRs1 ^ instObj.regRs2;
                break;
            }
            case SRL:
            {
                instObj.rstALU = instObj.regRs1 >> (instObj.regRs2 & 0x1f);
                break;
            }
            case SRA:
            {
                instObj.rstALU = ((int)instObj.regRs1) >> (instObj.regRs2 & 0x1f);
                break;
            }
            case OR:
            {
                instObj.rstALU = instObj.regRs1 | instObj.regRs2;
                break;
            }
            case AND:
            {
                instObj.rstALU = instObj.regRs1 & instObj.regRs2;
                break;
            }
        }

        if(instObj.BaseType == B)
        {
            if(instObj.jumpRst == instObj.predRst) {//猜对了

#ifdef BRANCHPREDICTION
                std::cout << "Branch Prediction: Good Guess!\n";
#endif

                instObj.predSuc = true;
            }
            else//猜错了
            {
#ifdef BRANCHPREDICTION
                std::cout << "Branch Prediction was wrong...\n";
#endif
                instObj.predSuc = false;
                preSuc = false;
                if(instObj.predRst)///？
                    regPtr->AddPC(-instObj.imm + 4);
                else
                    regPtr->AddPC(instObj.imm - 4);
                //撤销
            }
            predPtr->record(instObj.index,instObj.predRst,instObj.predSuc);
        }
#ifdef basic
        std::cout << "EX performed:\t" << basiccommand;
#endif
        return preSuc;
    }

    void pass(MA & MAobj)
    {
        MAobj.instObj = instObj;
    }
};


#endif //RISCV_SIMULATOR_EX_H
