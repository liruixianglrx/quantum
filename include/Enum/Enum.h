#include <iostream>
#ifndef ENUM_H
#define ENUM_H
enum Operation{
    BUY,
    SELL,
    HOLD,
    LIQUID
};
// 重载运算符<<，使其支持输出Operation类型
std::ostream& operator<<(std::ostream& os, const Operation& op);
enum Position {
    GoLong,
    GoShort,
    Empty
};
#endif // ENUM_H