#include "Enum.h"

// 在源文件中定义运算符<<重载
std::ostream& operator<<(std::ostream& os, const Operation& op) {
    switch (op) {
        case BUY:
            os << "BUY";
            break;
        case SELL:
            os << "SELL";
            break;
        case HOLD:
            os << "HOLD";
            break;
        case LIQUID:
            os << "LIQUID";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}
