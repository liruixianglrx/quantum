#ifndef STOCKPOOL_H
#define STOCKPOOL_H

#include "Stock.h"
#include <unordered_map>
/* Write your declarations here */
class StockPool
{
private:
    std::unordered_map<std::string,Stock*> m_stock_pool;

public:
    StockPool(/* args */){};
    ~StockPool(){};
    void addStockByCode(const std::string &stk_code);
    Stock *getStockByCode(const std::string &stk_code);
};

// StockPool::StockPool(/* args */)
// {
// }

// StockPool::~StockPool()
// {
// }

#endif // STOCKPOOL_H