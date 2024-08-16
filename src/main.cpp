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
    cout<<"testing !!!"<<endl;
    DataReader dr("t");
    StockPool stk_pool;

    dr.readDataFromWorksheet("Sheet1",&stk_pool);
    
    std::vector <std::string> ADFT_result;
    auto stk = stk_pool.getStockByCode("000001.SZ");
    auto arr = stk->getDataByDataName("收盘价");
    // vector<double> arr {1.265,156165,1.01561,16156,1.15615,894589,65.449681,48594.41564};
    ADFTest::startTest(arr,ADFT_result);
    return 0;
}