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
    DataReader dr ("shangzheng200");
    StockPool stk_pool;
    dr.readDataFromWorksheet("历史行情",&stk_pool);

    RSIStrategy rstg;
    CallBack callback(&stk_pool,&rstg);

    callback.setInitialCapital(100000);
    callback.computeProfit();

    cout<<callback.printResult();
    return 0;
}
