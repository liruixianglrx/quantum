// #ifndef CONCURRENTPAIRTRADINGSTRATEGY_H
// #define CONCURRENTPAIRTRADINGSTRATEGY_H

// #include "IStrategy.h"
// #include "StockPool.h"
// #include "PairTradingStrategy.h"
// #include <vector> 
// #include <unordered_map>
// class ConcurrentPairTradingStrategy:public IStrategy {
//     // TODO：止损点
//     public:
//         void computeSignals() override;
//         std::vector<std::string> getDataName() override;
//         void preCompute() override;
//         void callbackByDay(std::vector<int> &cur_pos,double &capital,int day) override;
//         void setEnterPoint(double e);
//         void setExitPoint(double e);
//         void setUpLowBoundForPValue(double u,double l);
//     private:
//         double m_enter_point,m_exit_point;
//         double m_upper_pvalue,m_lower_pvalue;
//         int m_stg_lock = -1;
//         void addVaildStrategy();
//         std::vector <PairTradingStrategy*> m_pairs;
//         std::vector<std::vector<Operation>> m_debug_signals;
//         struct stkIdx{
//             int idx1;
//             int idx2;
//             stkIdx(int i1,int i2):idx1(i1),idx2(i2){}
//         };
//         std::unordered_map<PairTradingStrategy*,stkIdx *> m_pair_idx_mapping;
// };

// #endif //PAIRTRADINGSTRATEGY