#include "LaomaStrategy.h"
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
    DataReader dr ("all_stk");
    StockPool stk_pool;
    dr.readDataFromWorksheet("历史行情",&stk_pool);

    LaomaStrategy l;

    CallBack callback(&stk_pool,&l);
    for (auto it:l.m_stks) {
        cout<<it.stk_code<<endl;
    }
    // callback.setStartDate("2015-09-23");
    // callback.setEndDate("2024-09-23");

    // callback.setInitialCapital(100000);
    // callback.computeProfit();

    cout<<callback. printResult();
    return 0;
}
