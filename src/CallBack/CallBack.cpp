#include "CallBack.h"
#include "Enum.h"

void CallBack::generateSignals(){
    m_signals = m_stratege->compute();
}

std::vector<std::vector<Operation>>& CallBack::getSignals(){
    return m_signals;
}

void CallBack::setInitialCapital(double c){
    m_capital = c;
}

CallBack::CallBack(StockPool *stk_pool,IStrategy *s):m_stk_pool(stk_pool),m_stratege(s){
    m_stratege->setStockPool(m_stk_pool);
    m_stratege->preCompute();
}