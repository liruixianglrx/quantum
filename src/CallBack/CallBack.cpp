#include "CallBack.h"
#include "Enum.h"

void CallBack::generateSignals(){
    m_stratege->setStockPool(m_stk_pool);
    m_signals = m_stratege->compute();
}

std::vector<std::vector<Operation>>& CallBack::getSignals(){
    return m_signals;
}