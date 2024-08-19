#ifndef PAIRTRADINGSTRATEGY_H
#define PAIRTRADINGSTRATEGY_H

#include "IStrategy.h"
#include "StockPool.h"
#include <vector>
class PairTradingStrategy:public IStrategy {
    // TODO：止损点
    public:
        std::vector<std::vector<Operation>> compute() override;
        std::vector<std::string> getDataName() override;
        void setExitPoint(double e);
        void preCompute() override;
        std::vector<double> m_ratio;

    private:
        void getRatio();
        void getMean();
        void getStdDeviation();
        void getZScore();
        double m_mean;
        double m_std_dev;
        double m_exit_point;
        std::vector<double> m_zscore;
        // std::vector<std::string> m_data_name;

        //当ratio大于exit_point时，记录day至m_pos_has，如果没有建立头寸则为-1;
        int m_pos_has=-1,m_neg_has=-1;
};

#endif //PAIRTRADINGSTRATEGY