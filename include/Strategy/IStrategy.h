#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <string>
#include <vector>
#include "StockPool.h"
#include "Enum.h"
class IStrategy {
    public:
        virtual ~IStrategy(){};
        virtual void computeSignals()=0;
        virtual std::vector<std::string> getDataName() =0; 
        virtual void callbackByDay(std::vector<std::vector<Operation>> &signals,std::vector<int> &cur_pos,double &capital,int day)=0;
        virtual void preCompute()=0;
        std::vector<std::vector<Operation>> getSignals(){return m_signals;}
        void setStockPool(StockPool *s);
    protected:
        StockPool *m_stock_pool;
        std::vector<std::vector<Operation>>  m_signals;
};
#endif  //ISTRATEGY_H