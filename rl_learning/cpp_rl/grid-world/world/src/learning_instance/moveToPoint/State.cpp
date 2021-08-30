#include "learning_instance/moveToPoint/State.h"
 
State::State(std::initializer_list<int> describes)
    :MyKey(describes)
{
}
 
State::~State()
{
}
 
void State::printKey() const
{
    std::stringstream ss;
    ss << "size: " << m_size << std::endl << "\t" << "state: ";
    for (auto &iter : m_myKey)
    {
        ss << iter << " "; 
    }
    m_log.infoLog(ss.str());
}
 
