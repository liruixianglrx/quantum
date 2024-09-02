#ifndef CALLBACK_H
#define CALLBACK_H

// #include <string>
// #include <vector>
#include "StockPool.h"
#include "IStrategy.h"
#include "Enum.h"
#include <vector>
/* Write your declarations here */
struct CallBackResult {
    std::string cointergration;
    double final_cap;
    double roe;
    double max_pullback;
    CallBackResult(){}
    CallBackResult (std::string c,double f,double r, double m):cointergration(c),final_cap(f),roe(r),max_pullback(m){}
};

class CallBack
{
private:
    StockPool *m_stk_pool;
    IStrategy *m_stratege;
    double m_capital,m_init_capital;
    double m_max_pullback=0;
    //买序号为idx，date的stock
    std::vector<std::vector<Operation>> m_signals;
    double getRealtimeCapital(int idx);

public:
    CallBack(StockPool *stk_pool,IStrategy *s);
    void generateSignals();
    std::vector<std::vector<Operation>>& getSignals();
    void setInitialCapital(double c);
    std::vector<double> computeProfit();
    std::string printResult();

    std::vector<int> m_cur_position;
    std::vector<double> m_realtime_capital;
    CallBackResult m_callBackResult;
};

#endif // CALLBACK_H