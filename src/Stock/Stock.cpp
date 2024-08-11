#include "Stock.h"

void Stock::addNewData(std::string data_name,double data) {
    m_datas[data_name].emplace_back(data);
}