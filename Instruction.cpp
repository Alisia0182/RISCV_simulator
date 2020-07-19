//
// Created by wjy on 2020/7/18.
//

#include "Instruction.h"

void Inst::GetType()
{
    uint opcode = (inst&((1<<7) - 1));

    switch(opcode){
        case 0b0110111: {
            BaseType = U;
            InstType = LUI;
            break;
        }
        case 0b0010111: {
            BaseType = U;
            InstType = AUIPC;
            break;
        }
        case 0b1101111: {
            BaseType = J;
            InstType = JAL;
            break;
        }
        case 0b1100111: {
            BaseType = I;
            InstType = JALR;
            break;
        }
        case 0b1100011: {
            BaseType = B;
            uint funct3 = GetFunct3;
            switch (funct3) {
                case 0b000:
                    InstType = BEQ;
                    break;
                case 0b001:
                    InstType = BNE;
                    break;
                case 0b100:
                    InstType = BLT;
                    break;
                case 0b101:
                    InstType = BGE;
                    break;
                case 0b110:
                    InstType = BLTU;
                    break;
                case 0b111:
                    InstType = BGEU;
            }
            break;
        }
        case 0b0000011: {
            BaseType = I;
            uint funct3 = GetFunct3;
            switch (funct3) {
                case 0b000:
                    InstType = LB;
                    break;
                case 0b001:
                    InstType = LH;
                    break;
                case 0b010:
                    InstType = LW;
                    break;
                case 0b100:
                    InstType = LBU;
                    break;
                case 0b101:
                    InstType = LHU;
            }
            break;
        }
        case 0b0100011: {
            BaseType = S;
            uint funct3 = GetFunct3;
            switch (funct3) {
                case 0b000:
                    InstType = SB;
                    break;
                case 0b001:
                    InstType = SH;
                    break;
                case 0b010:
                    InstType = SW;
            }
            break;
        }
        case 0b0010011: {
            uint funct3 = GetFunct3;
            switch (funct3) {
                case 0b000: {
                    BaseType = I;
                    InstType = ADDI;
                    break;
                }
                case 0b001: {
                    BaseType = R;
                    InstType = SLLI;
                    break;
                }
                case 0b010: {
                    BaseType = I;
                    InstType = SLTI;
                    break;
                }
                case 0b011: {
                    BaseType = I;
                    InstType = SLTIU;
                    break;
                }
                case 0b100: {
                    BaseType = I;
                    InstType = XORI;
                    break;
                }
                case 0b101: {
                    BaseType = R;
                    uint funct7 = GetFunct7;
                    switch (funct7) {
                        case 0b0000000:
                            InstType = SRLI;
                            break;
                        case 0b0100000:
                            InstType = SRAI;
                    }
                    break;
                }
                case 0b110: {
                    BaseType = I;
                    InstType = ORI;
                    break;
                }
                case 0b111: {
                    BaseType = I;
                    InstType = ANDI;
                }
            }
            break;
        }
        case 0b0110011: {
            BaseType = R;
            uint funct3 = GetFunct3;
            switch (funct3) {
                case 0b000: {
                    uint funct7 = GetFunct7;
                    switch (funct7) {
                        case 0b0000000:
                            InstType = ADD;
                            break;
                        case 0b0100000:
                            InstType = SUB;
                    }
                    break;
                }
                case 0b001: {
                    InstType = SLL;
                    break;
                }
                case 0b010: {
                    InstType = SLT;
                    break;
                }
                case 0b011: {
                    InstType = SLTU;
                    break;
                }
                case 0b100:{
                    InstType = XOR;
                    break;
                }
                case 0b101: {
                    uint funct7 = GetFunct7;
                    switch (funct7) {
                        case 0b0000000:{
                            InstType = SRL;
                            break;
                        }
                        case 0b0100000:{
                            InstType = SRA;
                            break;
                        }
                    }
                    break;
                }
                case 0b110:{
                    InstType = OR;
                    break;
                }
                case 0b111:{
                    InstType = AND;
                    break;
                }
            }
        }
    }
}

void Inst::Decode()
{
    rd = rs1 = rs2 = 0;
    imm = 0;
    switch (BaseType)
    {
        case R:{
            rd   = GetRd;
            rs1  = GetRs1;
            rs2  = GetRs2;
            break;
        }

        case I: {
            rd   = GetRd;
            rs1  = GetRs1;
            imm |= BitsMove32(inst, 20, 30, 0);
            if (inst >> 31) imm |= (0xffffffff >> 11 << 11);
            break;
        }

        case S: {
            rs1  = GetRs1;
            rs2  = GetRs2;
            imm |= BitsMove32(inst, 7, 11, 0);
            imm |= BitsMove32(inst, 25, 30, 5);
            if (inst >> 31) imm |= (0xffffffff >> 11 << 11);
            break;
        }

        case B: {
            rs1   = GetRs1;
            rs2   = GetRs2;
            index = GetIndex;
            imm |= BitsMove32(inst, 8, 11, 1);
            imm |= BitsMove32(inst, 25, 30, 5);
            imm |= BitsMove32(inst, 7, 7, 11);
            if (inst >> 31) imm |= 0xfffff000;
            break;
        }

        case U: {
            rd   = GetRd;
            imm |= BitsMove32(inst, 12, 31, 12);
            break;
        }

        case J: {
            rd   = GetRd;
            imm |= BitsMove32(inst, 21, 30, 1);
            imm |= BitsMove32(inst, 20, 20, 11);
            imm |= BitsMove32(inst, 12, 19, 12);
            if (inst >> 31) imm |= 0xfff00000;
        }
    }
}
