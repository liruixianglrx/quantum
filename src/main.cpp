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
    CallBack callback(&stk_pool2,&pst);

    ADFTest::startTest(pst.m_ratio);
    cout<<"\033[31m IS STATION ???? : \033[0m"<<ADFTest::isStationary()<<endl;
    plot::plotYValue(pst.m_ratio);
    plot::plotYValue(pst.m_zscore);

    cout<<"Corelations are :";
    cout<<Statics::correlationCoefficient(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"),stk_pool.getStockByIdx(2)->getDataByDataName("收盘价"));
    cout<<endl;

    ADFTest::startTest(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"));
    callback.setInitialCapital(10000);
    callback.generateSignals();

    return 0;
}