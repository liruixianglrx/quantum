#ifndef CALLBACK_H
#define CALLBACK_H

// #include <string>
// #include <vector>
#include "StockPool.h"
#include "IStrategy.h"
#include <vector>
/* Write your declarations here */
class CallBack
{
private:
    StockPool *m_stk_pool;
    IStrategy *m_stratege;
    std::vector<std::string> m_data_name;
    // std::vector<int> m_op_stockidx;
    //买序号为idx，date的stock
    std::vector<std::vector<bool>> m_buy_stockidx_date;

public:
    CallBack(StockPool *stk_pool,IStrategy *s):m_stk_pool(stk_pool),m_stratege(s){};
    void generateSignals();
    std::vector<std::vector<bool>>& getSignals();
};

#endif // CALLBACK_H