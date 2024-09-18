#include "ConcurrentPairTradingStrategy.h"
#include "ADFTest.h"
#include "Enum.h"
#include "Plot.h"
#include "Statics.h"

#include <iostream>
#include <vector>

void ConcurrentPairTradingStrategy::computeSignals(){
    for (int idx=0;idx<m_pair_idx_mapping.size();idx++) {
        m_pairs[idx]->computeSignals();
    }

    // // debug use delete later
    // for (int i=0;i<m_pairs[0]->getSignals()[0].size();i++) {
    //     std::vector<Operation> tmp;
    //     for (auto &t_stg:m_pairs) {
    //         tmp.push_back(t_stg->getSignals()[0][i]);
    //     }
    //     m_debug_signals.push_back(tmp);
    // }
    // for (auto &t_stg:m_pairs){
    //     std::vector<double> tmp;
    //     bool has_pos=false;
    //     for (int idx=0;idx<500;idx++) {
    //         if (!has_pos && (t_stg->getSignals()[0][idx] == BUY || t_stg->getSignals()[0][idx] == SELL)) {
    //             has_pos = true;
    //         }

    //         if (has_pos && t_stg->getSignals()[0][idx] == LIQUID) {
    //             has_pos = false;
    //         }
    //         tmp .push_back(has_pos) ;
    //     }
    //     plot::plotYValue(tmp);
    // }
}
std::vector<std::string> ConcurrentPairTradingStrategy::getDataName(){
    std::vector<std::string> ans;
    ans.push_back("收盘价");
    return ans;
}
void ConcurrentPairTradingStrategy::preCompute(){
    addVaildStrategy();
}
void ConcurrentPairTradingStrategy::callbackByDay(std::vector<int> &cur_pos,double &capital,int day){
   if (m_stg_lock == -1) {
    for (int idx=0;idx<m_pairs.size();idx++) {
        if (m_pairs[idx]->getSignals()[0][day] == BUY || m_pairs[idx]->getSignals()[0][day] == SELL) {
            m_stg_lock = idx;
            std::vector<int> tmp_cur_pos(2);
            tmp_cur_pos[0]=cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx1];
            tmp_cur_pos[1]=cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx2];
            m_pairs[m_stg_lock]->callbackByDay(tmp_cur_pos,capital,day);
            cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx1]=tmp_cur_pos[0];
            cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx2]=tmp_cur_pos[1];
            break;
        }
    }
   } else {
    if (m_pairs[m_stg_lock]->getSignals()[0][day] == HOLD) {
        return ;
    }
    std::vector<int> tmp_cur_pos(2);
    tmp_cur_pos[0]=cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx1];
    tmp_cur_pos[1]=cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx2];
    m_pairs[m_stg_lock]->callbackByDay(tmp_cur_pos,capital,day);
    cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx1]=tmp_cur_pos[0];
    cur_pos[m_pair_idx_mapping[m_pairs[m_stg_lock]]->idx2]=tmp_cur_pos[1];

    if (m_pairs[m_stg_lock]->getSignals()[0][day] == LIQUID) {
        m_stg_lock = -1;
    }
   }
}
void ConcurrentPairTradingStrategy::setEnterPoint(double e){
    m_enter_point = e;
}
void ConcurrentPairTradingStrategy::setExitPoint(double e){
    m_exit_point = e;
}
void ConcurrentPairTradingStrategy::addVaildStrategy(){
    for (int idx1 = 0;idx1 < m_stock_pool->getStockNum(); idx1++) {
        for (int idx2 = idx1+1;idx2 < m_stock_pool->getStockNum();idx2++) {
            PairTradingStrategy *pstg = new PairTradingStrategy();
            StockPool *stk = new StockPool();
            stk->addStock(m_stock_pool->getStockByIdx(idx1));
            stk->addStock(m_stock_pool->getStockByIdx(idx2));
            pstg->setStockPool(stk);
            pstg->setEnterPoint(m_enter_point);
            pstg->setExitPoint(m_exit_point);
            pstg->preCompute();
            std::cout<<"NEW     "<<idx1<<" "<<idx2<<std::endl;
            ADFTest::startTest(pstg->m_ratio);
            auto ADF_result =  std::stod(ADFTest::getResultByIndex(1));
            auto corelation = Statics::correlationCoefficient(m_stock_pool->getStockByIdx(idx1)->getDataByDataName("收盘价"), m_stock_pool->getStockByIdx(idx2) -> getDataByDataName("收盘价"));

            if (ADF_result >= m_lower_pvalue && ADF_result <= m_upper_pvalue && corelation > 0.7) {
                m_pair_idx_mapping[pstg]=new stkIdx(idx1,idx2);
                m_pairs.push_back(pstg);
                
                // DELETE
                std::cout<<"\033[31m Cointergration is :"<<ADF_result<<std::endl;
                std::cout<<" corelation is : " << corelation <<"\033[0m"<<std::endl;
            } else {
                delete pstg;
            }

        }
    }
}

void ConcurrentPairTradingStrategy::setUpLowBoundForPValue(double u,double l){
    m_upper_pvalue = u;
    m_lower_pvalue = l;
}