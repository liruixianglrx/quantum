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
    printf("profit percentage:%f lose percentage : %f\n",win_profit,loss_profit);
    printf("profit 1 sigma : %f,lose 1 sigma %f \n",Statics::standardDeviation(profit_rates),Statics::standardDeviation(loss_rates));
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
void IStrategy::addStkAtDate(std::string date,std::string stk_code){
    if (m_add_list.find(date) == m_add_list.end()) {
        m_add_list[date] = std::vector{stk_code};
    } else {
        m_add_list[date].push_back(stk_code);
    }
}
void IStrategy::removeStkAtDate(std::string date, std::string stk_code){
   if (m_remove_list.find(date) == m_remove_list.end()) {
        m_remove_list[date] = std::vector{stk_code};
    } else {
        m_remove_list[date].push_back(stk_code);
    }
}

void IStrategy::addOrRemoveStkManually(std::string date) {
    //无手动添加的股票
    if (m_add_list.find(date) == m_add_list.end() && m_remove_list.find(date) == m_remove_list.end()){
        return ;
    }

    if (m_add_list.find(date) != m_add_list.end()){
        auto stk_codes = m_add_list[date];
        for (auto stk_code : stk_codes) {
            m_signals[stk_code] = BUY;
        }
        m_add_list.erase(date);
    }

    if (m_remove_list.find(date) != m_remove_list.end()){
        auto stk_codes = m_remove_list[date];
        for (auto stk_code : stk_codes) {
            m_signals.erase(stk_code);
        }
        m_remove_list.erase(date);
    }
}

void IStrategy::generateSignalsByDay(int day){
    computeSignalsByDay(day);
    addOrRemoveStkManually(DateTime::IToD(m_stock_pool->m_dates[day]).toString());
}