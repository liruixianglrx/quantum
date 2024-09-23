#include "IStrategy.h"
#include "Statics.h"
TradingInfo::TradingInfo(double b,double s,double p):buy_price(b),sell_price(s),pos(p){};

double TradingInfo::getRevenue(){
    return (sell_price-buy_price)*pos;
}
double TradingRecords::getWinningRates(){
    return double(profit_rates.size()) / double(profit_rates.size() + loss_rates.size());
}

void TradingRecords::printResult() {
        //for debug: 
    auto win_profit = Statics::mean(profit_rates);
    auto loss_profit = Statics::mean(loss_rates);
    printf("win p:%f lose p : %f\n",win_profit,loss_profit);
    printf("win rates: %f\n",getWinningRates());
    printf("total trading num: %f\n",trade_times);
    printf("total profit is %f\n",total_profit);
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

TradingInfo IStrategy::getTradingInfoByStkCode(std::string code) {
    return m_trading_info[code];
}

void IStrategy::clearSellStocks(){
    for (auto signal=m_signals.begin();signal != m_signals.end();){
        if (signal->second == SELL) {
            m_trading_info.erase(signal->first);
            signal = m_signals.erase(signal);
        } else {
            signal++;
        }
    }
}