#include "OutputTools.h"
#include "Enum.h"
#include "DateTime.h"
#include <fstream> 
void OutputSignals(CallBack &callback) {
     // 打印信号
    auto s = callback.getSignals()[0];
    auto size = s.size();
    DateTime start_time("1900-01-01");
    Operation pre_op=HOLD;
    std::ofstream outputFile("signal.txt");
    for (int i=0;i<size;i++){
        if (s[i] != HOLD && pre_op != s[i]) {
            pre_op = s[i];
            outputFile<<DateTime::daysBefore(start_time,-callback.getStockPool()->m_dates[i]+2).toString() <<" "<< s[i] <<"\n";
            outputFile<<"positions are ";
            for (int idx=0;idx<callback.m_cur_position.size();idx++) {
                outputFile<<callback.m_cur_position[idx][i] << " ";
            }
            outputFile<<"\n";
            outputFile<<"prices are " ;
            for (int idx=0;idx<callback.getStockPool()->getStockNum();idx++) {
                outputFile<<callback.getStockPool()->getStockByIdx(idx)->getDataByDataName("收盘价")[i]<<" ";
            }
            outputFile<<"\n";
            outputFile<<"-----------------"<<"\n";
        }
        // outputFile<<"idx " <<i <<" "<<DateTime::daysBefore(start_time,-callback.getStockPool()->m_dates[i]+2).toString() <<" "<< s[i] <<"\n";
    }

     outputFile.close();
}