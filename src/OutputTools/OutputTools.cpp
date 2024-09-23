#include "OutputTools.h"
#include "Enum.h"
#include "DateTime.h"
#include <fstream> 
void OutputSignals(CallBack *callback,int day) {
     // 打印信号
    auto signals = callback->m_stratege->m_signals;
    // auto size = s.size();
    DateTime start_time("1900-01-01");
    Operation pre_op=HOLD;
    std::ofstream outputFile("signal.txt",std::ios::app);
    // for (int i=0;i<size;i++){
    //     if (s[i] != HOLD && pre_op != s[i]) {
    //         pre_op = s[i];
    //         outputFile<<DateTime::daysBefore(start_time,-callback.getStockPool()->m_dates[i]+2).toString() <<" "<< s[i] <<"\n";
    //         outputFile<<"positions are ";
    //         for (int idx=0;idx<callback.m_cur_position.size();idx++) {
    //             outputFile<<callback.m_cur_position[idx][i] << " ";
    //         }
    //         outputFile<<"\n";
    //         outputFile<<"prices are " ;
    //         for (int idx=0;idx<callback.getStockPool()->getStockNum();idx++) {
    //             outputFile<<callback.getStockPool()->getStockByIdx(idx)->getDataByDataName("收盘价")[i]<<" ";
    //         }
    //         outputFile<<"\n";
    //         outputFile<<"-----------------"<<"\n";
    //     }
    //     // outputFile<<"idx " <<i <<" "<<DateTime::daysBefore(start_time,-callback.getStockPool()->m_dates[i]+2).toString() <<" "<< s[i] <<"\n";
    // }

    for (auto s:signals) {
        if (s.second != HOLD) {
            outputFile<<DateTime::daysBefore(start_time,-callback->m_stk_pool->m_dates[day]+2).toString() <<" "<< s.second <<"\n";
            auto trading_info = callback->m_stratege->m_trading_info[s.first];
            outputFile<<"stock code is : "<<s.first<<" stock name is " << callback->m_stk_pool->getStockByCode(s.first)->m_stock_info[0]<<" \n";
            outputFile<<"positions are : "<<trading_info.pos<<" buy prices are : "<<trading_info.buy_price<<" sell prices are : "<<trading_info.sell_price<<"\n";
            outputFile<<"-----------------"<<"\n";
        }
    }
     outputFile.close();
}