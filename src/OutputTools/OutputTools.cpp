#include "OutputTools.h"
#include "Enum.h"
#include "DateTime.h"
#include <fstream> 
void OutputSignals(CallBack *callback,int day) {
    static double total_profit = 0;
     // 打印信号
    auto signals = callback->m_stratege->m_signals;
    // auto size = s.size();
    DateTime start_time("1900-01-01");
    Operation pre_op=HOLD;
    std::ofstream outputFile("signal.txt",std::ios::app);

    for (auto s:signals) {
        if (s.second != HOLD) {
            int days;
            if (day < callback->m_stk_pool->m_dates.size()) {
                days = -callback->m_stk_pool->m_dates[day]+2;
            } else {
                days = -callback->m_stk_pool->m_dates[day-1]+1;
            }
            outputFile<<DateTime::daysBefore(start_time,days).toString() <<" "<< s.second <<"\n";
            auto trading_info = callback->m_stratege->m_trading_info[s.first];
            outputFile<<"股票代码 : "<<s.first<<" 股票名字 " << callback->m_stk_pool->getStockByCode(s.first)->m_stock_info[0]<<" \n";
            outputFile<<"仓位 : "<<trading_info.pos<<" 买入价 : "<<trading_info.buy_price<<" 卖出价 : "<<trading_info.sell_price<<"\n";
            if (s.second == SELL){
                double profit = trading_info.getRevenue();
                total_profit += profit;
                outputFile<<"单比交易利润 :"<<profit<<"利润率: "<<profit/(trading_info.buy_price*trading_info.pos) <<"\n";
                outputFile<<"累计收入 :"<<total_profit<<"\n";
            }
            outputFile<<"-----------------"<<"\n";
        }
    }
     outputFile.close();
}