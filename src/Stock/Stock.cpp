#include "Stock.h"

void Stock::addNewData(const std::string &data_name,double data) {
    m_datas[data_name].emplace_back(data);
}

 std::vector<double>& Stock::getDataByDataName(const std::string &data_name){
    return m_datas[data_name];
 }

 int Stock::getDataLen(){
    return m_datas.begin()->second.size();
 }