#include "PairTradingStrategy.h"
#include "Statics.h"
#include "Enum.h"
#include <string>
#include <vector>

    std::vector<std::vector<Operation>> PairTradingStrategy::compute() {
    getRatio();
    getMean();
    getStdDeviation();
    getZScore();

    int days = m_stock_pool->getDataLen();
    std::vector<std::vector<Operation>> signals(2,std::vector<Operation>(days));
    for (int day = 0; day < days; day++) {
        if  (m_zscore[day] > m_exit_point) {
            signals[0][day] = SELL;
            signals[1][day] = BUY;
            m_pos_has = day;
        }

        if (m_pos_has != -1 && m_zscore[day] <= 0) {
            signals[0][day] = BUY;
            signals[1][day] = SELL;
            m_pos_has = -1;
        }

        if  (m_zscore[day] < -1*m_exit_point) {
            signals[0][day] = BUY;
            signals[1][day] = SELL;
            m_neg_has = day;
        }

        if (m_neg_has != -1 && m_zscore[day] >= 0) {
            signals[0][day] = SELL;
            signals[1][day] = BUY;
            m_neg_has = -1;
        }
    }

    return signals;
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
    m_mean = Statics::mean(m_ratio);
}
void PairTradingStrategy::getStdDeviation(){
    m_std_dev = Statics::standardDeviation(m_ratio);
}

void PairTradingStrategy::getZScore(){
    for (int i=0;i<m_ratio.size();i++) {
        m_zscore.push_back((m_ratio[i]-m_mean) / m_std_dev);
    }
}