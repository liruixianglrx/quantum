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
    dr.readDataFromWorksheet("历史行情1",&stk_pool);

    RSIStrategy rstg;
    double RSIUpValue = 20;
    double RSIDownValue =3;
    double Slots = 4;
    rstg.setSlots(Slots);
    rstg.setRSIUpValue(RSIUpValue);
    rstg.setRSIDownValue(RSIDownValue);
    // std::string start_year ="2023";
    // for (int i=0;i<10;i++) {
    //     CallBack callback(&stk_pool,&rstg);
    //     std::string start_date = std::to_string(std::stoi(start_year)-i) + "-09-23";
    //     cout<<"start_date "<<start_date<<"\n";
    //     callback.setStartDate(start_date);
    //     callback.setEndDate("2024-09-23");

    //     callback.setInitialCapital(100000);
    //     callback.computeProfit();

    //     // printf("RSI : %f %f,Slots : %f\n",RSIDownValue,RSIUpValue,Slots);
    //     cout<<callback. printResult();
    // }

    CallBack callback(&stk_pool,&rstg);
    callback.setStartDate("2024-09-23");
    callback.setEndDate("2024-10-10");

    callback.setInitialCapital(100000);
    callback.computeProfit();

    printf("RSI : %f %f,Slots : %f\n",RSIDownValue,RSIUpValue,Slots);
    cout<<callback. printResult();
    return 0;
}
