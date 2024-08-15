#include "CallBack.h"

void CallBack::generateSignals(){
    m_data_name = m_stratege->getDataName();

    for (int day=0;day<m_stk_pool->getDataLen();day++) {
        std::vector <double> data_per_day;

        for (int idx=0;idx<m_stk_pool->getStockNum();idx++) {
            auto datas = m_stk_pool->getStockByIdx(idx)->getDataByDataName(m_data_name[idx]);

            data_per_day.push_back(datas[idx]);
            
        } 
    }
}
std::vector<std::vector<bool>>& CallBack::getSignals(){

}