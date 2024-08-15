#ifndef STOCKPOOL_H
#define STOCKPOOL_H

#include "Stock.h"
#include <unordered_map>
#include <vector>
/* Write your declarations here */
class StockPool
{
private:
    // std::unordered_map<std::string,Stock*> m_stock_pool;
    std::vector<Stock*> m_stock_pool;
    std::unordered_map<std::string,int> m_code_idx_mapping;
    int m_data_len;
public:
    StockPool(/* args */){};
    ~StockPool(){};
    void addStockByCode(const std::string &stk_code);
    Stock *getStockByCode(const std::string &stk_code);
    Stock *getStockByIdx(const int& idx);
    int getDataLen();
    int getStockNum();
};

// StockPool::StockPool(/* args */)
// {
// }

// StockPool::~StockPool()
// {
// }

#endif // STOCKPOOL_H