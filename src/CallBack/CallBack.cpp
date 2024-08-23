#include "CallBack.h"
#include "Enum.h"
#include <assert.h>

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
}

CallBack::CallBack(StockPool *stk_pool,IStrategy *s):m_stk_pool(stk_pool),m_stratege(s){
    m_stratege->setStockPool(m_stk_pool);
    m_stratege->preCompute();
}

std::vector<double> CallBack::computeProfit(){
    //todo : 应该在stategy里面有个成员函数，类型为函数指针
    std::vector<int> cur_position(2,0);
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
    }


    if (cur_position[0] != 0) {
        auto price1 = m_stk_pool->getStockByIdx(0)->getDataByDataName("收盘价")[m_stk_pool->getStockByIdx(0)->getDataLen() -1];
        auto price2 = m_stk_pool->getStockByIdx(1)->getDataByDataName("收盘价")[m_stk_pool->getStockByIdx(0)->getDataLen() -1];
        m_capital = m_capital + cur_position[0] * price1;
        m_capital = m_capital + cur_position[1] * price2;
        cur_position[0]=cur_position[1]=0;
    }
    return ans;
}