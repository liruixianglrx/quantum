#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "StockPool.h"
#include "Enum.h"
#include "DateTime.h"
//每次交易的信息
struct TradingInfo {
    TradingInfo(){};
    TradingInfo(double b,double s,double p);
    double buy_price,sell_price;
    int pos;
    double getRevenue();
};
 struct TradingRecords
{
    double total_profit=0;
    double trade_times=0;
    // 每次盈利和亏损的百分百
    std::vector<double> profit_rates,loss_rates;
    double getWinningRates();
    void printResult();
    
};
class IStrategy {
    public:
        virtual ~IStrategy(){};
        // virtual void computeSignals()=0;
        virtual void callbackByDay(std::unordered_map<std::string,int> &cur_pos,double &capital,int day)=0;
        virtual void preCompute()=0;
        virtual void computeSignalsByDay(int day)=0;
        void generateSignalsByDay(int day);
        std::unordered_map<std::string,Operation> getSignals(){return m_signals;}
        void setStockPool(StockPool *s);
        void addTradingRecord(TradingInfo &t);
        void clearSellStocks();
        TradingInfo getTradingInfoByStkCode(std::string code);
        // 交易总体的统计类
        TradingRecords m_trading_records;
        //stk_code 与 signal的mapping
        std::unordered_map<std::string,Operation> m_signals;
        //stk_code 与 单笔交易的mapping
        std::unordered_map<std::string,TradingInfo> m_trading_info;

        void removeStkAtDate(std::string date, std::string stk_code);
        void addStkAtDate(std::string date,std::string stk_code);
    protected:
        StockPool *m_stock_pool;
        // std::vector<std::vector<Operation>> m_signals;
        // 持仓的stk_code
        std::unordered_set<std::string> m_holding_stocks_code;
        void addOrRemoveStkManually(std::string date);
            // 按日期添加的股票信息
        std::unordered_map<std::string,std::vector<std::string>> m_add_list;
        std::unordered_map<std::string,std::vector<std::string>> m_remove_list;
};
#endif  //ISTRATEGY_H