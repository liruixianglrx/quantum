#include "PairTradingStrategy.h"
#include "Statics.h"
#include "Enum.h"
#include <string>
#include <vector>

void PairTradingStrategy::computeSignals(){
    int days = m_stock_pool->getDataLen();
    // std::vector<std::vector<Operation>> signals(2,std::vector<Operation>(days));
    m_signals.resize(2,std::vector<Operation>(days,HOLD));
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

void PairTradingStrategy::callbackByDay(std::vector<int> &cur_pos,double &capital,int day) {
    if (m_signals[0][day] == BUY && cur_pos[0] <= 0) {
            // static_assert(cur_pos[0] <= 0);
            auto capital1 = capital * m_ration_mean/(1+ m_ration_mean);
            auto capital2 = capital - capital1;

            auto price1 = m_stock_pool->getStockByIdx(0)->getDataByDataName("收盘价")[day];
            auto price2 = m_stock_pool->getStockByIdx(1)->getDataByDataName("收盘价")[day];
            cur_pos[0] = (capital1 / price1);
            cur_pos[1] = -1 * (capital2 / price2);

            capital = capital - cur_pos[0] * price1;
            capital = capital - cur_pos[1] * price2;
        }
        else if (m_signals[0][day] == SELL and cur_pos[0] >= 0) {
            // static_assert(cur_pos[0] <= 0);
            auto capital1 = capital * m_ration_mean/(1+ m_ration_mean);
            auto capital2 = capital - capital1;

            auto price1 = m_stock_pool->getStockByIdx(0)->getDataByDataName("收盘价")[day];
            auto price2 = m_stock_pool->getStockByIdx(1)->getDataByDataName("收盘价")[day];
            cur_pos[0] = -1 *(capital1 / price1);
            cur_pos[1] = (capital2 / price2);

            capital = capital - cur_pos[0] * price1;
            capital = capital - cur_pos[1] * price2;
        }
        else if(m_signals[0][day] == LIQUID) {
            auto price1 = m_stock_pool->getStockByIdx(0)->getDataByDataName("收盘价")[day];
            auto price2 = m_stock_pool->getStockByIdx(1)->getDataByDataName("收盘价")[day];

            capital = capital + cur_pos[0] * price1;
            capital = capital + cur_pos[1] * price2;

            cur_pos[0]=cur_pos[1]=0;
        } 
}

std::vector<double> PairTradingStrategy::holdingSignal(int idx)
{
    // debug use delete later
    std::vector<double>  ans;
    double signal=0;
 
    // std::vector<double> tmp;
    bool has_pos=false;
    for (int day=0;day<getSignals()[idx].size();day++) {
        if (!has_pos && (getSignals()[idx][day] == BUY || getSignals()[idx][day] == SELL)) {
            if (getSignals()[idx][day] == BUY ) {
                signal = 1;
            } else {
                signal = -1;
            }
            has_pos = true;
        }

        if (has_pos && getSignals()[idx][day] == LIQUID) {
            has_pos = false;
            signal = 0;
        }
        ans.push_back(signal) ;
    }
    return ans;
    
}