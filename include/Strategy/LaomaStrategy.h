#ifndef LAOMASTRATEGY_H
#define LAOMASTRATEGY_H

#include "IStrategy.h"

struct LaomaStkData{
    std::string stk_code;
    int date1,date2,date3,date4,date5;
    double price1,price2,price3,price4,price5;
};

class LaomaStrategy:public IStrategy
{
private:
    bool isGoodStk(Stock *stk,LaomaStkData *data);
public:
    LaomaStrategy(/* args */){};
    ~LaomaStrategy(){};
    void preCompute() override;
    void callbackByDay(std::unordered_map<std::string,int> &cur_pos,double &capital,int day){};
    void computeSignalsByDay(int day){};
    //符合筛选条件的stks
    std::vector<LaomaStkData> m_stks;
};


#endif // LAOMASTRATEGY_H