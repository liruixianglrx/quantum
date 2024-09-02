#ifndef PAIRTRADINGSTRATEGY_H
#define PAIRTRADINGSTRATEGY_H

#include "IStrategy.h"
#include "StockPool.h"
#include <vector> 
class PairTradingStrategy:public IStrategy {
    // TODO：止损点
    public:
        void computeSignals() override;
        std::vector<std::string> getDataName() override;
        void preCompute() override;
        void callbackByDay(std::vector<std::vector<Operation>> &signals,std::vector<int> &cur_pos,double &capital,int day) override;
        void setEnterPoint(double e);
        void setExitPoint(double e);

        // double get_ratio_mean(){return m_ration_mean;};
        double m_ration_mean;
        std::vector<double> m_ratio;
        std::vector<double> m_zscore;

    private:
        void getRatio();
        void getMean();
        void getStdDeviation();
        void getZScore(int window_size=30);
        double m_std_dev;
        double m_enter_point;
        double m_exit_point;
        int m_window_size;
        // std::vector<double> m_zscore;
        // std::vector<std::string> m_data_name;

        //当ratio大于exit_point时，记录day至m_pos_has，如果没有建立头寸则为-1;
        int m_pos_has=-1,m_neg_has=-1;
        // double m_ration_mean;
};

#endif //PAIRTRADINGSTRATEGY