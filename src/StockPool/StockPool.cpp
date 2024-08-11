#include "StockPool.h"

void StockPool::addStockByCode(const std::string &stk_code){
    m_stock_pool[stk_code] = new Stock();
}

Stock *StockPool::getStockByCode(const std::string &stk_code){
    return m_stock_pool[stk_code];
}