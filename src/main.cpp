#include "OpenXLSX.hpp"
#include <string.h>
#include <vector>
#include "DateTime.h"
#include "DataReader.h"
#include "Statics.h"
#include "ADFTest.h"
#include "PairTradingStrategy.h"
#include "CallBack.h"
#include "Plot.h"
using namespace OpenXLSX;
using namespace std;

int main() {
    DataReader dr("exchange pairs");
    StockPool stk_pool;
    
    dr.readDataFromWorksheet("Sheet1",&stk_pool);

    StockPool stk_pool2;
    stk_pool2.addStock(stk_pool.getStockByIdx(0));
    stk_pool2.addStock(stk_pool.getStockByIdx(2));
    // TODO:STOCK selector
 
    PairTradingStrategy pst;
    pst.setExitPoint(1.5);
    auto &data = stk_pool2.getStockByIdx(1)->getDataByDataName("收盘价");
    for (int idx=0;idx < stk_pool2.getStockByIdx(1)->getDataLen();idx++) {
        if (data[idx] > 2) {
            cout<<"idx "<<idx <<endl;
            data[idx] = data[idx-1];
        }
    }

    auto &data2 = stk_pool2.getStockByIdx(0)->getDataByDataName("收盘价");
    for (int idx=0;idx < stk_pool2.getStockByIdx(1)->getDataLen();idx++) {
        if (data2[idx]< 0.3) {
            cout<<"idx "<<idx <<endl;
            data2[idx] = data2[idx-1];
        }
    }
    CallBack callback(&stk_pool2,&pst);

    ADFTest::startTest(pst.m_ratio);
    cout<<"\033[31m IS STATION ???? : \033[0m"<<ADFTest::isStationary()<<endl;
    plot::plotYValue(pst.m_ratio);
    plot::plotYValue(pst.m_zscore);
    //debug
    // cout<<"异常价格"<<endl;
    // auto data= pst.m_ratio;
    // for (int idx = 0;idx < pst.m_ratio.size();idx++) {
    //     if (pst.m_ratio[idx] < 0.5) pst.m_ratio[idx]=pst.m_ratio[idx-1];
    // }
    // cout<<endl;

    // plot::plotYValue(pst.m_ratio);


    cout<<"Corelations are :";
    cout<<Statics::correlationCoefficient(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"),stk_pool.getStockByIdx(2)->getDataByDataName("收盘价"));
    cout<<endl;

    ADFTest::startTest(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"));
    callback.setInitialCapital(10000);
    callback.generateSignals();
    // for (auto it: callback.getSignals()[0])
    // {
    //     switch (it)
    //     {
    //     case 0:
    //         cout<<"HOLD ";
    //         break;
    //     case 1:
    //         cout<<"BUY ";
    //         break;
    //     case 2:
    //         cout<<"SELL ";
    //         break;
    //     case 3:
    //         cout<<"LIQUID ";
    //         break;
    //     default:
    //         break;
    //     }
    // }
    auto ans = callback.computeProfit();
    // for (auto it: ans)
    // {
    //     cout<<it <<" ";
    // }
    // cout<<endl;
    return 0;
}