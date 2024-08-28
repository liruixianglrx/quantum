#include "PairTradingStrategy.h"
#include "Statics.h"
#include "Enum.h"
#include <string>
#include <vector>

std::vector<std::vector<Operation>> PairTradingStrategy::computeSignals(){
    int days = m_stock_pool->getDataLen();
    // std::vector<std::vector<Operation>> signals(2,std::vector<Operation>(days));
    m_signals.resize(2,std::vector<Operation>(days));
    for (int day = 0; day < days; day++) {
        if  (m_zscore[day] > m_enter_point) {
            m_signals[0][day] = SELL;
            m_signals[1][day] = BUY;
            m_pos_has = day;
        }

        if (m_pos_has != -1 && m_zscore[day] <= m_exit_point) {
            m_signals[0][day] = LIQUID;
            m_signals[1][day] = LIQUID;
            m_pos_has = -1;
        }

        if  (m_zscore[day] < -1*m_enter_point) {
            m_signals[0][day] = BUY;
            m_signals[1][day] = SELL;
            m_neg_has = day;
        }

        if (m_neg_has != -1 && m_zscore[day] >= -1* m_exit_point) {
            m_signals[0][day] = LIQUID;
            m_signals[1][day] = LIQUID;
            m_neg_has = -1;
        }
    }

    return m_signals;
}

std::vector<std::string> PairTradingStrategy::getDataName(){
    return std::vector<std::string> {"收盘价"};
}

void PairTradingStrategy::getRatio(){
    auto data0=m_stock_pool->getStockByIdx(0)->getDataByDataName(getDataName()[0]);
    auto data1=m_stock_pool->getStockByIdx(1)->getDataByDataName(getDataName()[0]);
    
    for (int day=0;day<m_stock_pool->getDataLen();day++) {
        m_ratio.push_back(data0[day] / data1[day]);
    }
}
void PairTradingStrategy::getMean(){
    m_ration_mean = Statics::mean(m_ratio);
}
void PairTradingStrategy::getStdDeviation(){
    m_std_dev = Statics::standardDeviation(m_ratio);
}

void PairTradingStrategy::getZScore(int window_size){
    double mean;
    double std;
    for (int i=0;i<window_size;i++) {
        m_zscore.push_back(0);
    }
    
    for (int i=window_size;i<m_ratio.size();i++) {
        mean = Statics::mean(std::vector<double> (m_ratio.begin()+i-window_size,m_ratio.begin()+i));
        std =  Statics::standardDeviation(std::vector<double> (m_ratio.begin()+i-window_size,m_ratio.begin()+i));
        m_zscore.push_back((m_ratio[i]-mean) / std);
    }

    // for (int i=window_size -1;i<m_ratio.size();i++) {
    //     mean = Statics::mean(std::vector<double> (m_ratio.end()-window_size,m_ratio.end()));
    //     std =  Statics::standardDeviation(std::vector<double> (m_ratio.begin()+i,m_ratio.begin()+i+window_size));
    //     m_zscore.push_back((m_ratio[i]-mean) / std);
    // }
}

void PairTradingStrategy::setExitPoint(double e){
    m_exit_point = e;
}

void PairTradingStrategy::setEnterPoint(double e){
    m_enter_point = e;
}

void PairTradingStrategy::preCompute(){
    getRatio();
    getMean();
    getStdDeviation();
    getZScore(30);
}