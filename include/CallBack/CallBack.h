#ifndef CALLBACK_H
#define CALLBACK_H

// #include <string>
// #include <vector>
#include "StockPool.h"
#include "IStrategy.h"
#include "Enum.h"
#include <vector>
/* Write your declarations here */
class CallBack
{
private:
    StockPool *m_stk_pool;
    IStrategy *m_stratege;
    double m_capital;
    // std::vector<int> m_op_stockidx;
    //买序号为idx，date的stock
    std::vector<std::vector<Operation>> m_signals;

public:
    CallBack(StockPool *stk_pool,IStrategy *s);
    void generateSignals();
    std::vector<std::vector<Operation>>& getSignals();
    void setInitialCapital(double c);
    std::vector<double> computeProfit();
};

#endif // CALLBACK_H