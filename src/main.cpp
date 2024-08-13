#include "OpenXLSX.hpp"
#include <string.h>
#include <vector>
#include "DateTime.h"
#include "DataReader.h"
#include "Statics.h"
#include "ADFTest.h"
using namespace OpenXLSX;
using namespace std;

int main() {
    DataReader dr("t");
    StockPool stk_pool;

    dr.readDataFromWorksheet("Sheet1",&stk_pool);
    
    std::vector <std::string> ADFT_result;
    auto stk = stk_pool.getStockByCode("000001.SZ");
    auto arr = stk->getDataByDataName("收盘价");
    ADFTest::startTest(arr,ADFT_result);
    return 0;
}