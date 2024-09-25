#include "CallBack.h"
#include "DateTime.h"
#include "Enum.h"
#include <iostream>
//todo:computeProfit完成后删掉这个头文件
#include "PairTradingStrategy.h"
#include "Statics.h"
#include <cmath>
#include "OutputTools.h"

// void CallBack::generateSignals(){
//     m_stratege->computeSignals();
//     m_signals = m_stratege->getSignals();
// }

std::vector<std::unordered_map<std::string,Operation>>& CallBack::getSignals(){
    return m_signals;
}

void CallBack::setInitialCapital(double c){
    m_capital = c;
    m_init_capital = c;
}

CallBack::CallBack(StockPool *stk_pool,IStrategy *s):m_stk_pool(stk_pool),m_stratege(s),m_callBackResult(){
    m_stratege->setStockPool(m_stk_pool);
    m_stratege->preCompute();
    // m_cur_position.resize(m_stk_pool->getStockNum());
    // for (auto idx = 0;idx < m_cur_position.size();idx++) {
    //     m_cur_position[idx] = 0;
    // }
}

double CallBack::getRealtimeAllCapital(int day){
    double tmpCapital=m_capital;
    // for (int idx=0;idx < m_stk_pool->getStockNum(); idx++) {
    //     auto price = m_stk_pool->getStockByIdx(idx)->getDataByDataName("收盘价")[day];
    //     tmpCapital  = tmpCapital + m_cur_position[idx] * price; 
    // }
    for (auto pos:m_cur_position) {
        auto price = m_stk_pool->getStockByCode(pos.first)->getDataByDataName("收盘价")[day];
        tmpCapital = tmpCapital + pos.second * price; 
    }
    return tmpCapital;
 }

 double CallBack::getAllCapitalBycost(int day){
    double tmpCapital=m_capital;
    for (auto pos :m_cur_position) {
        auto price = m_stratege->getTradingInfoByStkCode(pos.first).buy_price;
        tmpCapital = tmpCapital + pos.second * price;
    }
    return tmpCapital;
 }

std::vector<double> CallBack::computeProfit(){
    //todo : 应该在stategy里面有个成员函数，类型为函数指针
    std::vector<double> ans;
    std::vector<double> realtime_capital;

    // debug
    std::vector<double> cost_capital;

    DateTime start_time = DateTime(m_start_date);
    DateTime end_time = DateTime(m_end_date);
    // auto pstrategy = dynamic_cast<PairTradingStrategy*>(m_stratege);
    int day = 0;
    for (day = 0;day < m_stk_pool->getDataLen();day++) {
        auto today = DateTime::daysBefore(DATETIME_START,-m_stk_pool->m_dates[day]+2).toString();
        if (today < m_start_date) {
            continue;
        }
        if (today > m_end_date) {
            break;
        }

        m_stratege->callbackByDay(m_cur_position,m_capital,day);
        OutputSignals(this,day);
        m_stratege->clearSellStocks();
        ans.push_back(m_capital);
        auto tmp = getRealtimeAllCapital(day);
        realtime_capital.push_back(tmp);
        cost_capital.push_back(getAllCapitalBycost(day));
        if (tmp < m_init_capital) {
             tmp = (m_init_capital-tmp) / m_init_capital;
            if (tmp > m_max_pullback) {
                m_max_pullback = tmp;
            }
        }
    }
   
    // 最新一天回测,只产生信号，不调整仓位
    m_stratege->computeSignalsByDay(day);
    OutputSignals(this,day);

    m_capital = getRealtimeAllCapital(m_stk_pool->getDataLen()-1);
    m_callBackResult.max_pullback=m_max_pullback;
    m_callBackResult.final_cap=m_capital;
    double y = (m_capital / m_init_capital);
    double days = end_time.daysBetween(start_time);
    double year = 365.0 / days;
    m_callBackResult.roe = pow(y,year) -1;

    m_stratege->m_trading_records.printResult();
    return ans;
}

std::string CallBack::printResult(){
    return "\033[31m cointergration is :"+ m_callBackResult.cointergration+" Final Capital is :"+ std::to_string(m_callBackResult.final_cap)+" ROE is :"+std::to_string(m_callBackResult.roe)+" MAX pullback "+std::to_string(m_callBackResult.max_pullback) +"\033[0m \n";
}

void CallBack::setStartDate(std::string date){
    m_start_date = date;
}
void CallBack::setEndDate(std::string date){
    m_end_date = date;
}