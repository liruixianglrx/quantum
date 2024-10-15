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
    double m_capital,m_init_capital;
    std::string m_start_date,m_end_date;
    double m_max_pullback=0;
    //买序号为idx，date的stock
    std::vector<std::unordered_map<std::string,Operation>> m_signals;
    double getRealtimeAllCapital(int idx);
    double getAllCapitalBycost(int day);
public:
    CallBack(StockPool *stk_pool,IStrategy *s);
    // void generateSignals();
    std::vector<std::unordered_map<std::string,Operation>> &getSignals();
    void setInitialCapital(double c);
    std::vector<double> computeProfit();
    std::string printResult();
    // 回撤日期，双闭区间，输出信号包括end_后一天
    void setStartDate(std::string date);
    void setEndDate(std::string date);
    // stock_code和仓位的映射
    std::unordered_map<std::string,int> m_cur_position;
    std::vector<double> m_realtime_capital;
    CallBackResult m_callBackResult;
    StockPool *m_stk_pool;
    IStrategy *m_stratege;
};

#endif // CALLBACK_H