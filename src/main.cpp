#include "OpenXLSX.hpp"
#include <string.h>
#include <vector>
#include "DateTime.h"
#include "DataReader.h"
#include "Statics.h"
#include "ADFTest.h"
#include "PairTradingStrategy.h"
#include "CallBack.h"
using namespace OpenXLSX;
using namespace std;

int main() {
    DataReader dr("USD");
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
    cout<<"IS STATION ???? : "<<ADFTest::isStationary()<<endl;
    
    // auto arr={1.4554,1.4554,1.4553,1.4555,1.4556,1.4554,1.4557,1.4552};
    // ADFTest::startTest(arr);
    // cout<<"IS STATION ???? : "<<ADFTest::isStationary()<<endl;

    cout<<"Corelations are :";
    cout<<Statics::correlationCoefficient(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"),stk_pool.getStockByIdx(2)->getDataByDataName("收盘价"));
    cout<<endl;

    ADFTest::startTest(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"));
    callback.setInitialCapital(10000);
    callback.generateSignals();

    return 0;
}