#include "CallBack.h"
#include "Enum.h"
#include <assert.h>
#include <iostream>
//todo:computeProfit完成后删掉这个头文件
#include "PairTradingStrategy.h"

void CallBack::generateSignals(){
    m_signals = m_stratege->compute();
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
    cur_position.resize(2);
    cur_position[0]=cur_position[1]=0;
}

double CallBack::getRealtimeCapital(int idx){
    auto price1 = m_stk_pool->getStockByIdx(0)->getDataByDataName("收盘价")[idx];
    auto price2 = m_stk_pool->getStockByIdx(1)->getDataByDataName("收盘价")[idx];
    double tmp;
    tmp = m_capital + cur_position[0] * price1;
    tmp = tmp + cur_position[1] * price2;

    return tmp;
 }

std::vector<double> CallBack::computeProfit(){
    //todo : 应该在stategy里面有个成员函数，类型为函数指针
    std::vector<double> ans;
    auto pstrategy = dynamic_cast<PairTradingStrategy*>(m_stratege);
    for (int idx = 0;idx < m_signals[0].size();idx++) {
        if (m_signals[0][idx] == BUY && cur_position[0] <= 0) {
            // static_assert(cur_position[0] <= 0);
            assert(cur_position[0] <= 0);
            auto capital1 = m_capital * pstrategy->m_ration_mean/(1+ pstrategy->m_ration_mean);
            auto capital2 = m_capital - capital1;

            auto price1 = m_stk_pool->getStockByIdx(0)->getDataByDataName("收盘价")[idx];
            auto price2 = m_stk_pool->getStockByIdx(1)->getDataByDataName("收盘价")[idx];
            cur_position[0] = (capital1 / price1);
            cur_position[1] = -1 * (capital2 / price2);

            m_capital = m_capital - cur_position[0] * price1;
            m_capital = m_capital - cur_position[1] * price2;
        }
       else if (m_signals[0][idx] == SELL and cur_position[0] >= 0) {
            // static_assert(cur_position[0] <= 0);
            assert(cur_position[0] >= 0);
            auto capital1 = m_capital * pstrategy->m_ration_mean/(1+ pstrategy->m_ration_mean);
            auto capital2 = m_capital - capital1;

            auto price1 = m_stk_pool->getStockByIdx(0)->getDataByDataName("收盘价")[idx];
            auto price2 = m_stk_pool->getStockByIdx(1)->getDataByDataName("收盘价")[idx];
            cur_position[0] = -1 *(capital1 / price1);
            cur_position[1] = (capital2 / price2);

            m_capital = m_capital - cur_position[0] * price1;
            m_capital = m_capital - cur_position[1] * price2;
        }

        else if(m_signals[0][idx] == LIQUID) {
            auto price1 = m_stk_pool->getStockByIdx(0)->getDataByDataName("收盘价")[idx];
            auto price2 = m_stk_pool->getStockByIdx(1)->getDataByDataName("收盘价")[idx];

            m_capital = m_capital + cur_position[0] * price1;
            m_capital = m_capital + cur_position[1] * price2;

            cur_position[0]=cur_position[1]=0;
        } 

        ans.push_back(m_capital);
        auto tmp = getRealtimeCapital(idx);
        if (tmp < m_init_capital) {
             tmp = (m_init_capital-tmp) / m_init_capital;
            if (tmp > m_max_pullback) {
                m_max_pullback = tmp;
            }
        }
    }


    if (cur_position[0] != 0) {
        auto price1 = m_stk_pool->getStockByIdx(0)->getDataByDataName("收盘价")[m_stk_pool->getStockByIdx(0)->getDataLen() -1];
        auto price2 = m_stk_pool->getStockByIdx(1)->getDataByDataName("收盘价")[m_stk_pool->getStockByIdx(0)->getDataLen() -1];
        m_capital = m_capital + cur_position[0] * price1;
        m_capital = m_capital + cur_position[1] * price2;
        cur_position[0]=cur_position[1]=0;
    }
    m_callBackResult.max_pullback=m_max_pullback;
    m_callBackResult.final_cap=m_capital;
    double y = (m_capital / m_init_capital);
    m_callBackResult.roe = pow(y,0.1) -1;
    return ans;
}

std::string CallBack::printResult(){
    return "\033[31m cointergration is :"+ m_callBackResult.cointergration+" Final Capital is :"+ std::to_string(m_callBackResult.final_cap)+" ROE is :"+std::to_string(m_callBackResult.roe)+" MAX pullback "+std::to_string(m_callBackResult.max_pullback) +"\033[0m \n";
    // std::cout<<"\033[31m cointergration is :"<< m_callBackResult.cointergration<<" Final Capital is :"<<m_callBackResult.final_cap<<" ROE is :"<<m_callBackResult.roe<<" MAX pullback "<<m_callBackResult.max_pullback <<"\033[0m "<<std::endl;
}