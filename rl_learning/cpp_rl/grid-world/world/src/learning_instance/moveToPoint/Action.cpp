#include "learning_instance/moveToPoint/Action.h"
 
Action::Action(std::initializer_list<int> describes)
    :MyKey(describes)
{
}
 
Action::~Action()
{
}
 
void Action::printKey() const
{
    std::stringstream ss;
    ss << "size: " << m_size << std::endl << "\t" << "action: ";
    for (auto &iter : m_myKey)
    {
        switch (iter)
        {
        case Action::UP:
            ss << "UP";
            break;
        case Action::DOWN:
            ss << "DOWN";
            break;
        case Action::LEFT:
            ss << "LEFT";
            break;
        case Action::RIGHT:
            ss << "RIGHT";
            break;
        case Action::ACCEL:
            ss << "ACCEL";
            break;
        case Action::DECEL:
            ss << "DECEL";
            break;
        case Action::STILL:
            ss << "STILL";
            break;
        default:
            ss << "??";
            break;
        }
        ss << " "; 
    }
    m_log.infoLog(ss.str());
}
