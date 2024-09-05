#include "CallBack.h"
#include "Enum.h"
#include <iostream>
//todo:computeProfit完成后删掉这个头文件
#include "PairTradingStrategy.h"
#include <cmath>

void CallBack::generateSignals(){
    m_stratege->computeSignals();
    m_signals = m_stratege->getSignals();
}

std::vector<std::vector<Operation>>& CallBack::getSignals(){
    return m_signals;
}

void CallBack::setInitialCapital(double c){
    m_capital = c;
    m_init_capital = c;
}

CallBack::CallBack(StockPool *stk_pool,IStrategy *s):m_stk_pool(stk_pool),m_stratege(s),m_callBackResult(){
    m_stratege->setStockPool(m_stk_pool);
    m_stratege->preCompute();
    m_cur_position.resize(m_stk_pool->getStockNum());
    for (auto idx = 0;idx < m_cur_position.size();idx++) {
        m_cur_position[idx] = 0;
    }
}

double CallBack::getRealtimeCapital(int day){
    double tmpCapital=m_capital;
    for (int idx=0;idx < m_stk_pool->getStockNum(); idx++) {
        auto price = m_stk_pool->getStockByIdx(idx)->getDataByDataName("收盘价")[day];
        tmpCapital  = tmpCapital + m_cur_position[idx] * price; 
    }
    return tmpCapital;
 }

std::vector<double> CallBack::computeProfit(){
    //todo : 应该在stategy里面有个成员函数，类型为函数指针
    std::vector<double> ans;
    // auto pstrategy = dynamic_cast<PairTradingStrategy*>(m_stratege);
    for (int day = 0;day < m_stk_pool->getDataLen();day++) {
        m_stratege->callbackByDay(m_cur_position,m_capital,day);

        ans.push_back(m_capital);
        auto tmp = getRealtimeCapital(day);
        if (tmp < m_init_capital) {
             tmp = (m_init_capital-tmp) / m_init_capital;
            if (tmp > m_max_pullback) {
                m_max_pullback = tmp;
            }
        }
    }

    if (m_cur_position[0] != 0) {
        m_capital = getRealtimeCapital(m_stk_pool->getDataLen());
    }
    m_callBackResult.max_pullback=m_max_pullback;
    m_callBackResult.final_cap=m_capital;
    double y = (m_capital / m_init_capital);
    m_callBackResult.roe = pow(y,0.1) -1;
    return ans;
}

std::string CallBack::printResult(){
    return "\033[31m cointergration is :"+ m_callBackResult.cointergration+" Final Capital is :"+ std::to_string(m_callBackResult.final_cap)+" ROE is :"+std::to_string(m_callBackResult.roe)+" MAX pullback "+std::to_string(m_callBackResult.max_pullback) +"\033[0m \n";
}