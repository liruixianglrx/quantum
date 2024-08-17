#include "StockPool.h"

void StockPool::addStockByCode(const std::string &stk_code){
    m_stock_pool.push_back(new Stock());
    m_code_idx_mapping[stk_code] = m_stock_pool.size() -1;
}

Stock* StockPool::getStockByCode(const std::string &stk_code){
    return m_stock_pool[m_code_idx_mapping[stk_code]];
}


Stock* StockPool::getStockByIdx(const int& idx){
    return m_stock_pool[idx];
}

int StockPool::getDataLen(){
if (m_data_len == 0) {
    m_data_len = m_stock_pool[0]->getDataLen();
}
    return m_data_len;
}

int StockPool::getStockNum(){
    return m_stock_pool.size();
}

void StockPool::addStock(Stock *stk) {
    m_stock_pool.push_back(stk);
    m_code_idx_mapping[stk->m_stock_code]=m_stock_pool.size()-1;
}

StockPool::~StockPool(){
    // Debug
    // for (auto it :m_stock_pool){
    //     delete []it;
    // }
}