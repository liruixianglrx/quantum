#ifndef RSISTRATEGY_H
#define RSISTRATEGY_H

// https://substack.com/@quantitativo/p-147005114

#include "IStrategy.h"
#include <queue>
#include <unordered_set>
struct Comparator {
    bool operator() (const std::pair<std::string,double> &a,const std::pair<std::string,double> &b) {
        return a.second > b.second;
    }
};
class RSIStrategy: public IStrategy
{
private:
    int m_slots_nums=3;
    // RSI的默认周期
    int m_period = 2;
    // int m_cur_slots =0;

public:
    RSIStrategy(/* args */){};
    ~RSIStrategy(){};
    // void computeSignals() override;
    void preCompute() override;
    void callbackByDay(std::unordered_map<std::string,int> &cur_pos,double &capital,int day) override;
    void computeSignalsByDay(int day) override;
    void setSlots(int num);
};


#endif // RSISTRATEGY_H