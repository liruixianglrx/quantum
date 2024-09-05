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
#include <utility>

using namespace OpenXLSX;
using namespace std;

int main() {
    DataReader dr("riyuan");
    StockPool stk_pool;
    
    dr.readDataFromWorksheet("历史行情",&stk_pool);

    std::vector<std::string> ans_all;
    for (int i=0;i<stk_pool.getStockNum();i++){
        for (int j=i+1;j<stk_pool.getStockNum();j++) {
        StockPool stk_pool2;
        stk_pool2.addStock(stk_pool.getStockByIdx(i));
        stk_pool2.addStock(stk_pool.getStockByIdx(j));
        // TODO:STOCK selector
    
        PairTradingStrategy pst;
        pst.setEnterPoint(2.5);
        pst.setExitPoint(0);
        CallBack callback(&stk_pool2,&pst);

        ADFTest::startTest(pst.m_ratio);
        cout<<"\033[31m IS STATION ???? : \033[0m"<<ADFTest::isStationary()<<endl;

        cout<<"Corelations are :";
        cout<<Statics::correlationCoefficient(stk_pool.getStockByIdx(i)->getDataByDataName("收盘价"),stk_pool.getStockByIdx(j)->getDataByDataName("收盘价"));
        cout<<endl;
        callback.setInitialCapital(10000);
        callback.generateSignals();
        auto ans = callback.computeProfit();
        callback.m_callBackResult.cointergration = ADFTest::getResultByIndex(1);
        ans_all.push_back(callback.printResult());
        }
    }

    for (auto &it:ans_all)
        cout<<it;
    return 0;
}