#include "ConcurrentPairTradingStrategy.h"
#include "ADFTest.h"

#include <iostream>

void ConcurrentPairTradingStrategy::computeSignals(){}
std::vector<std::string> ConcurrentPairTradingStrategy::getDataName(){}
void ConcurrentPairTradingStrategy::preCompute(){}
void ConcurrentPairTradingStrategy::callbackByDay(std::vector<std::vector<Operation>> &signals,std::vector<int> &cur_pos,double &capital,int day){}
void ConcurrentPairTradingStrategy::setEnterPoint(double e){}
void ConcurrentPairTradingStrategy::setExitPoint(double e){}
void ConcurrentPairTradingStrategy::addVaildStrategy(){
    for (int idx1 = 0;idx1 < m_stock_pool->getStockNum(); idx1++) {
        for (int idx2 = idx1+1;idx2 < m_stock_pool->getStockNum();idx2++) {
            PairTradingStrategy pstg;
            StockPool stk;
            stk.addStock(m_stock_pool->getStockByIdx(idx1));
            stk.addStock(m_stock_pool->getStockByIdx(idx2));
            pstg.setStockPool(&stk);
            pstg.setEnterPoint(m_enter_point);
            pstg.setExitPoint(m_exit_point);
            pstg.preCompute();
            ADFTest::startTest(pstg.m_ratio);
            auto ADF_result =  std::stod(ADFTest::getResultByIndex(1));
            if (ADF_result >= m_lower_pvalue && ADF_result <= m_upper_pvalue) {
                m_pair_idx_mapping[&pstg]=new stkIdx(idx1,idx2);
                
                // DELETE
                std::cout<<"Cointergration is :"<<ADF_result<<std::endl;
            }
        }
    }
}