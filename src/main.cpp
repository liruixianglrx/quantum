// #include "ConcurrentPairTradingStrategy.h"
// #include "OpenXLSX.hpp"
// #include <string.h>
// #include <vector>
// #include "DateTime.h"
// #include "DataReader.h"
// #include "Statics.h"
// #include "ADFTest.h"
// #include "PairTradingStrategy.h"
// #include "CallBack.h"
// #include "Plot.h"
// #include <utility>

// using namespace OpenXLSX;
// using namespace std;

// int main() {
//     DataReader dr("t");
//     StockPool stk_pool;
    
//     dr.readDataFromWorksheet("历史行情",&stk_pool);

//     std::vector<std::string> ans_all;
//     ConcurrentPairTradingStrategy cst;
//     cst.setEnterPoint(2.5);
//     cst.setExitPoint(0);
//     cst.setUpLowBoundForPValue(0.3,0.01);
//     CallBack callback(&stk_pool,&cst);

//     callback.setInitialCapital(10000);
//     callback.generateSignals();
//     callback.computeProfit();
//     // auto ans = callback.computeProfit();

//     // for (auto &it:ans_all)
//     //     cout<<it;
//     cout<<callback.printResult();
//     return 0;
// }