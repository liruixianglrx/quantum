#include "RSIStrategy.h"
#include "Statics.h"
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
            double price = m_stock_pool->getStockByCode(signal->first)->getDataByDataName("收盘价")[day];
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
            printf("revenue is : %f\n",m_trading_info[signal->first].getRevenue());
            addTradingRecord(m_trading_info[signal->first]);
            m_trading_info.erase(signal->first);
            signal = m_signals.erase(signal);
        }
    }
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
            if (m_holding_stocks_code.find(stk->m_stock_code) != m_holding_stocks_code.end()) {
                continue;
            }
            auto close_datas = stk->getDataByDataName("收盘价");
            auto high_datas = stk ->getDataByDataName("最高价");
            auto low_datas = stk->getDataByDataName("最低价");

            std::vector<double> tmp_rsi(close_datas.begin()+ day-m_period-1,close_datas.begin()+day);
            std::vector<double> tmp_sma(close_datas.begin()+day-200,close_datas.begin()+day+1);
            // todos: 尝试SMA为算术平均？？
            if (Statics::RSI(tmp_rsi,m_period) < 5 && Statics::SMA(tmp_sma,200,1) < close_datas[day]) {
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