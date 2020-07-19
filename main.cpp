//
// Created by wjy on 2020/7/19.
//

#include <iostream>

#include "Common.h"
#include "Instruction.h"

#include "RegisterFile.h"
#include "Memory.h"
#include "Predictor.h"

#include "IF.h"
#include "ID.h"
#include "EX.h"
#include "MA.h"
#include "WB.h"

using std::cout;

Memory    * MemPtr;
RegFile   * RegPtr;
Predictor * PredPtr;

int main()
{
    MemPtr  = new Memory;
    RegPtr  = new RegFile;
    PredPtr = new Predictor;

    IF If(RegPtr,MemPtr);
    ID Id(PredPtr,RegPtr);
    EX Ex(PredPtr,RegPtr);
    MA Ma(MemPtr);
    WB Wb(RegPtr);

    uint     rst;
    bool     End = false;

    MemPtr->ReadIn();

    while (1) {
        Wb.perform();

        Ma.perform();
        Ma.pass(Wb);

        if(!Ex.perform()) Id.Clean();
        Ex.pass(Ma);

        Id.perform();
        Id.pass(Ex);

        End = If.perform();
        If.pass(Id);

        if(End){
            Wb.perform();

            Ma.perform();
            Ma.pass(Wb);

            Ex.perform();
            Ex.pass(Ma);

            Wb.perform();

            Ma.perform();
            Ma.pass(Wb);

            Wb.perform();

            rst = RegPtr->ReadReg(10);
            cout << std::dec << (rst << 24 >> 24) << '\n';

            RegPtr->Clean();
            MemPtr->Clean();
            PredPtr->Clean();

            break;
        }
    }
    return 0;
}