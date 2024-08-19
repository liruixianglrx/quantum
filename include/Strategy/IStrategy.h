#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <string>
#include <vector>
#include "StockPool.h"
#include "Enum.h"
class IStrategy {
    public:
        virtual ~IStrategy(){};
        virtual std::vector<std::vector<Operation>> compute()=0;
        virtual std::vector<std::string> getDataName() =0; 
        void setStockPool(StockPool *s);
        virtual void preCompute()=0;

    protected:
        StockPool *m_stock_pool;
};
#endif  //ISTRATEGY_H