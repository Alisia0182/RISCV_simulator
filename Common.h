//
// Created by wjy on 2020/7/18.
//
#include <string>

#ifndef RISCV_SIMULATOR_COMMON_H
#define RISCV_SIMULATOR_COMMON_H

using std::string;

typedef unsigned int  uint;
typedef unsigned char uchar;

inline uint BitsMove32(const uint &x,uint low,uint high, uint DstLow){
    uint rst;
    rst = x     << (31-high)  >> (31-high);
    rst = rst   >> low        << DstLow;
    return rst;
}

inline bool lessCmpSigned(const uint & num1, const uint & num2)
{
    if((num1 >> 31) && (num2 >> 31))//同负数
        return (num2 < num1);
    if(num1 >> 31)//num1负数，num2非负
        return true;
    if(num2 >> 31)//num1非负，num2负
        return false;
    return (num1 < num2);
}


inline uint ToUint(char ch){
    if(ch >= '0'&& ch <='9')
        return (ch-'0');
    else if(ch>='A'&&ch<='F')
        return (ch-'A'+10);
    return (ch-'a'+10);//没得用(
};

inline uint ToUint(const string& str,bool & isPst) {
    uint rst = 0,i = 0;
    isPst = false;
    if (str[0] == '@') {
        isPst = true;++i;
    }
    for (; str[i]; ++i)
        rst = (rst << 4) + ToUint(str[i]);
    return rst;
}

inline uint ToUint(const string& str) {
    uint rst = 0,i = 0;
    if (str[0] == '@') ++i;
    for (; str[i]; ++i)
        rst = (rst << 4) + ToUint(str[i]);
    return rst;
}
#endif //RISCV_SIMULATOR_COMMON_H
