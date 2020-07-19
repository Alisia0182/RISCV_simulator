//
// Created by wjy on 2020/7/18.
//
#include "Common.h"

#ifndef RISCV_SIMULATOR_INSTRUCTION_H
#define RISCV_SIMULATOR_INSTRUCTION_H

#define GetFunct3 inst << 17 >> 29
#define GetFunct7 inst       >> 25
#define GetRd     inst << 20 >> 27
#define GetRs1    inst << 12 >> 27
#define GetRs2    inst <<  7 >> 27
#define GetIndex  inst << 12 >> 19;

enum BaseTypes {
                R, I, S,
                B, U, J,
                };

enum InstTypes {
                fetched,NOP,
                LUI, AUIPC,
                JAL, JALR,
                BEQ, BNE, BLT, BLTU, BGE, BGEU,
                LB, LH, LW, LBU, LHU,
                SB, SH, SW,
                ADDI, SLTI, SLTIU,
                XORI, ORI,ANDI,
                SLLI, SRLI, SRAI,
                ADD, SUB,SLL,
                SLT,SLTU,
                XOR,SRL,SRA,
                AND, OR,
                };

struct Inst{
    InstTypes InstType;
    BaseTypes BaseType;
    uint inst, pc;
    uint rd, rs1, rs2;
    int imm;//sometimes rs2 is used as shamt
    uint regRs1,regRs2;
    uint valMem;
    uint rstALU;
    uint index;
    bool predRst;
    bool predSuc;
    bool jumpRst;

    Inst(uint _inst = 0, uint _pc = 0):
                InstType(NOP),
                inst(_inst),
                pc(_pc),rd(0),
                rs1(0), rs2(0),
                imm(0),
                regRs1(0),
                regRs2(0),
                valMem(0),
                rstALU(0),
                predRst(0),
                predSuc(0),//??
                jumpRst(0)
    {}

    void Clean()
    {
        InstType = NOP;
        inst     = pc        = 0;
        rd = rs1 = rs2 = imm = 0;
        regRs1   = regRs2    = 0;
        valMem   = rstALU    = 0;
        predRst  = predSuc
                 = jumpRst   = 0;
    }

    void GetType();

    void Decode();

};

#endif //RISCV_SIMULATOR_INSTRUCTION_H
