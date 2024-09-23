#include "IStrategy.h"

TradingInfo::TradingInfo(double b,double s,double p):buy_price(b),sell_price(s),pos(p){};

double TradingInfo::getRevenue(){
    return (sell_price-buy_price)*pos;
}
double TradingRecords::getWinningRates(){
    return double(profit_rates.size()) / double(profit_rates.size() + loss_rates.size());
}
void IStrategy::setStockPool(StockPool *s){m_stock_pool = s;}

void IStrategy::addTradingRecord(TradingInfo &t){
    m_trading_records.trade_times++;
    double cost = t.buy_price * t.pos;
    double profit = (t.sell_price - t.buy_price) * t.pos;
    m_trading_records.total_profit+=profit;
    if (profit > 0) {
        m_trading_records.profit_rates.push_back(profit/cost);
    } else {
        m_trading_records.loss_rates.push_back(profit/cost);
    }
}
