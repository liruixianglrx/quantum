#include "RSIStrategy.h"
#include "Statics.h"
#include "OutputTools.h"
#include <fstream>
// void RSIStrategy::computeSignals() {

// }
void RSIStrategy::preCompute() {
    // do nothing
}
void RSIStrategy::callbackByDay(std::unordered_map<std::string,int> &cur_pos,double &capital,int day) {
    if (day < 200) return;
    computeSignalsByDay(day);

    double capital_per_slot ;
    if (m_slots_nums > m_holding_stocks_code.size()) {
        capital_per_slot = capital / (m_slots_nums - m_holding_stocks_code.size());
    } else {
        capital_per_slot = 0;
    }
    for (auto signal=m_signals.begin();signal != m_signals.end();) {
        if (signal->second == HOLD) {
            signal++;
            continue;
        } else if (signal->second == BUY) {
            double price = m_stock_pool->getStockByCode(signal->first)->getDataByDataName("开盘价")[day];
            int pos = capital_per_slot / price;
            cur_pos[signal->first] = cur_pos[signal->first] + pos;
            capital = capital - (price * pos);
            m_holding_stocks_code.emplace(signal->first);
            TradingInfo info(price,0,pos);
            m_trading_info[signal->first] = info;
            signal++;
        } else if (signal->second == SELL){
            double price = m_stock_pool->getStockByCode(signal->first)->getDataByDataName("开盘价")[day];
            capital = capital + (price * cur_pos[signal->first]);
            cur_pos.erase(signal->first);
            m_holding_stocks_code.erase(signal->first);
            m_trading_info[signal->first].sell_price = price;
            // printf("name is %s\n",m_stock_pool->getStockByCode(signal->first)->m_stock_info[0].c_str()); 
            // printf("revenue is : %f   name is : %s\n",m_trading_info[signal->first].getRevenue(),m_stock_pool->getStockByCode(signal->first)->m_stock_info[0].c_str());
            addTradingRecord(m_trading_info[signal->first]);
            // m_trading_info.erase(signal->first);
            // signal = m_signals.erase(signal);
            signal++;
        }
    }

    // for (auto signal=m_signals.begin();signal != m_signals.end();){
    //     if (signal->second == SELL) {
    //         m_trading_info.erase(signal->first);
    //         signal = m_signals.erase(signal);
    //     } else {
    //         signal++;
    //     }
    // }
}

void RSIStrategy::computeSignalsByDay(int day) {
    //检测是否有卖出的信号产生
    for (auto it:m_holding_stocks_code) {
        Stock *stk = m_stock_pool->getStockByCode(it);
        double close_price = stk->getDataByDataName("收盘价")[day-1];
        double yesterday_high_price = stk->getDataByDataName("最高价")[day-2];

        //满足卖出条件。卖出股票
        if (yesterday_high_price < close_price) {
            m_signals[stk->m_stock_code] = SELL;
        } else {
            m_signals[stk->m_stock_code] = HOLD;
        }
    }

    // 买入新股票
    if (m_holding_stocks_code.size()<m_slots_nums){
        std::priority_queue<std::pair<std::string,double>,std::vector<std::pair<std::string,double>>, Comparator> heap;
        for (int idx = 0;idx<m_stock_pool->getStockNum();idx++ ){
            Stock* stk = m_stock_pool->getStockByIdx(idx); 
            // 如果已经有持仓，跳过
            if (m_holding_stocks_code.find(stk->m_stock_code) != m_holding_stocks_code.end()) {
                continue;
            }
            auto close_datas = stk->getDataByDataName("收盘价");
            auto high_datas = stk ->getDataByDataName("最高价");
            auto low_datas = stk->getDataByDataName("最低价");

            // 如果还没有股票数据，跳过
            if (day < close_datas.size() && close_datas[day] == 0) {
                continue;
            }
            std::vector<double> tmp_rsi(close_datas.begin()+ day-m_period-1,close_datas.begin()+day);
            std::vector<double> tmp_sma(close_datas.begin()+day-200,close_datas.begin()+day);
            // todos: 尝试SMA为算术平均？？

            //debug
            auto rsi = Statics::RSI(tmp_rsi,m_period);
            if (rsi < m_RSI_up_value && rsi >= m_RSI_down_value && Statics::SMA(tmp_sma,200,1) > close_datas[day-1]) {
                double NATR = Statics::NormalizedAverageTrueRange(close_datas,high_datas,low_datas);
                heap.push(std::make_pair(stk->m_stock_code,NATR));
                while (heap.size() > m_slots_nums - m_holding_stocks_code.size()) {
                    heap.pop();
                }
            }
        }

        // 加入到持仓中
        while (!heap.empty()) {
            auto it = heap.top();
            heap.pop();
            // m_holding_stocks_code.emplace(it.first);
            Stock * stk = m_stock_pool->getStockByCode(it.first);
            m_signals[stk->m_stock_code]=BUY;
        }
        // m_cur_slots = m_holding_stocks_index.size();
    }
}

void RSIStrategy::setSlots(int num){
    m_slots_nums = num;
}

void RSIStrategy::setRSIUpValue(double r){
    m_RSI_up_value = r;
}

void RSIStrategy::setRSIDownValue(double r){
    m_RSI_down_value = r;
}