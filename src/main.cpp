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
#include <utility>

using namespace OpenXLSX;
using namespace std;

int main() {
    DataReader dr("riyuan");
    StockPool stk_pool;
    
    dr.readDataFromWorksheet("历史行情",&stk_pool);

    std::vector<pair<std::string,double> > ans_all;
    for (int i=0;i<4;i++){
        for (int j=i+1;j<4;j++) {
        StockPool stk_pool2;
        stk_pool2.addStock(stk_pool.getStockByIdx(i));
        stk_pool2.addStock(stk_pool.getStockByIdx(j));
        // TODO:STOCK selector
    
        PairTradingStrategy pst;
        pst.setEnterPoint(2);
        pst.setExitPoint(0);
        auto &data = stk_pool2.getStockByIdx(1)->getDataByDataName("收盘价");
        for (int idx=0;idx < stk_pool2.getStockByIdx(1)->getDataLen();idx++) {
            if (data[idx] < 0.3) {
                cout<<"idx1 "<<idx <<endl;
                data[idx] = data[idx-1];
            }
        }

        auto &data2 = stk_pool2.getStockByIdx(0)->getDataByDataName("收盘价");
        for (int idx=0;idx < stk_pool2.getStockByIdx(1)->getDataLen();idx++) {
            if (data2[idx]< 0.3) {
                cout<<"idx2"<<idx <<endl;
                data2[idx] = data2[idx-1];
            }
        }
        CallBack callback(&stk_pool2,&pst);

        ADFTest::startTest(pst.m_ratio);
        cout<<"\033[31m IS STATION ???? : \033[0m"<<ADFTest::isStationary()<<endl;
        // plot::plotYValue(pst.m_ratio);
        // plot::plotYValue(pst.m_zscore);

        cout<<"Corelations are :";
        cout<<Statics::correlationCoefficient(stk_pool.getStockByIdx(i)->getDataByDataName("收盘价"),stk_pool.getStockByIdx(j)->getDataByDataName("收盘价"));
        cout<<endl;

        // ADFTest::startTest(stk_pool.getStockByIdx(0)->getDataByDataName("收盘价"));
        callback.setInitialCapital(10000);
        callback.generateSignals();
        auto ans = callback.computeProfit();
        // for (auto it: ans)
        // {
        //     cout<<it <<" ";
        // }
        // cout<<endl;

        // cout <<"\033[31m Final Capital is  \033[0m "<<ans[ans.size()]<<endl;
        auto final_cap = std::move(ans[ans.size()-1]) ;
        ans_all.push_back(make_pair(ADFTest::getResultByIndex(1),final_cap));
        }
    }

    for (int idx =0 ;idx <ans_all.size();idx++) {
        double y = ans_all[idx].second / 10000;
        double roe = pow(y,0.1) - 1;
        cout<<"\033[31m cointergration is :"<< ans_all[idx].first<<" Final Capital is :"<<ans_all[idx].second<<" ROE is :"<<roe <<endl;
    }
        cout<<"\033[0m ";
    return 0;
}