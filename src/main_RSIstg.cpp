#include "RSIStrategy.h"

#include "CallBack.h"
#include "OpenXLSX.hpp"
#include <string.h>
#include <vector>
#include "DateTime.h"
#include "DataReader.h"
#include "CallBack.h"
#include "Plot.h"

using namespace std;


int main() {
    //纳指参数 0 5 slots 5, >
    //上证100 3 20 slots 4, <
    DataReader dr ("zhongzheng100real");
    StockPool stk_pool;
    dr.readDataFromWorksheet("历史行情2",&stk_pool);

    RSIStrategy rstg;
    double RSIUpValue = 20;
    double RSIDownValue =3;
    double Slots = 4;
    rstg.setSlots(Slots);
    rstg.setRSIUpValue(RSIUpValue);
    rstg.setRSIDownValue(RSIDownValue);
    CallBack callback(&stk_pool,&rstg);
    callback.setStartDate("2024-09-23");
    callback.setEndDate("2024-09-25");

    callback.setInitialCapital(100000);
    callback.computeProfit();

    printf("RSI : %f %f,Slots : %f\n",RSIDownValue,RSIUpValue,Slots);
    cout<<callback. printResult();
    return 0;
}
