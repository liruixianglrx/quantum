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
    DataReader dr ("zhongzheng100");
    StockPool stk_pool;
    dr.readDataFromWorksheet("历史行情",&stk_pool);

    RSIStrategy rstg;
    double RSIUpValue = 20;
    double RSIDownValue =3;
    double Slots = 4;
    rstg.setSlots(Slots);
    rstg.setRSIUpValue(RSIUpValue);
    rstg.setRSIDownValue(RSIDownValue);
    CallBack callback(&stk_pool,&rstg);

    callback.setInitialCapital(100000);
    callback.computeProfit();

    printf("RSI : %f %f,Slots : %f\n",RSIDownValue,RSIUpValue,Slots);
    cout<<callback. printResult();
    return 0;
}
