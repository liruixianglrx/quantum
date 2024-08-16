#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <string>
#include <vector>
#include "StockPool.h"
#include "Enum.h"
class IStrategy {
    public:
        virtual std::vector<std::vector<Operation>> compute();
        virtual std::vector<std::string> getDataName(); 
        void setStockPool(StockPool *s){m_stock_pool = s;}
    protected:
        StockPool *m_stock_pool;
};
#endif  //ISTRATEGY_H