#include "LaomaStrategy.h"
#include "Plot.h"
void LaomaStrategy::preCompute(){
    for (int idx=0;idx<m_stock_pool->getStockNum();idx++) {
        Stock *stk = m_stock_pool->getStockByIdx(idx);
        LaomaStkData data;
        if (isGoodStk(stk,&data)) {
            m_stks.push_back(data);
        }
    }
}

bool LaomaStrategy::isGoodStk(Stock *stk,LaomaStkData *data){
    printf("searching Good stk %s\n",stk->m_stock_code.c_str());
    auto prices = stk->getDataByDataName("收盘价");
    double a1=0;
    for (int i1=0;i1<prices.size();i1++) {
        if (prices[i1] ==0) {
            continue;
        }

        a1= prices[i1];
        for (int i2=i1+1;i2<prices.size();i2++) {
            double a2=prices[i2];
            // 查找符合条件的a2：a1上涨至少5倍
            if (a2 >= a1 * 5) {

                for (int i3=i2+1;i3<prices.size();i3++) {
                    double a3 = prices[i3];
                    //查找符合条件的a3：a2价格至少下跌 60%
                    if (a3 <= a2 *0.4) {

                        for (int i4=i3+1;i4<prices.size();i4++) {
                            double a4=prices[i4];
                            //查找符合条件的a3：a2价格至少上涨 50%
                            if (a4 >= a3*1.5){

                                for (int i5=i4+1;i5<prices.size();i5++) {
                                    double a5 = prices[i5];
                                    //至少跌到高位0.25
                                    if (a5 <= a2*0.25){
                                        data->stk_code = stk->m_stock_code;
                                        std::vector<double> color;
                                        for (int i=0;i<prices.size();i++) {
                                            if (i >=i1 && i<=i2) 
                                                color.push_back(1);
                                            else if (i>=i2 && i <= i3)
                                                color.push_back(-1);
                                            else if (i>=i3 && i <= i4)
                                                color.push_back(1);
                                            else if (i>=i4 && i <= i5)
                                                color.push_back(-1);
                                            else 
                                                color.push_back(0);
                                        }
                                        plot::plotYValueWithColor(prices,color);
                                        return true;
                                        // 振荡3年
                                        // bool flag =true;
                                        // for (int i6=i5+1;i6<i5+1000;i6++) {
                                        //     if (prices[i6] < a5*0.8 || prices[i6] > a5*1.4) {
                                        //         flag = false;
                                        //         break;
                                        //     }
                                        // }
                                        // 满足条件
                                        // if (flag) {
                                        //     data->stk_code = stk->m_stock_code;
                                        //     std::vector<double> color;
                                        //     for (int i=0;i<prices.size();i++) {
                                        //         if (i >=i1 && i<=i2) 
                                        //             color.push_back(1);
                                        //         else if (i>=i2 && i <= i3)
                                        //             color.push_back(-1);
                                        //         else if (i>=i3 && i <= i4)
                                        //             color.push_back(1);
                                        //         else if (i>=i4 && i <= i5)
                                        //             color.push_back(-1);
                                        //         else 
                                        //             color.push_back(0);
                                        //     }
                                        //     plot::plotYValueWithColor(prices,color);
                                        //     return true;
                                        // } else {
                                        //     break;
                                        // }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}