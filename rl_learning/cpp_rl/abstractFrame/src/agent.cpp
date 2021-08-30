#include "agent.h"

Agent::Agent()
{
    std::cout << "智能体构造" << std::endl;
    _v = new std::map<int, double>;
    for (int i=1; i<=5; i++)
        for (int j=0; j<5; j++)
        {
            _v->insert(std::pair<int, double>(i+j*10, 0));
        }
}

Agent::~Agent()
{
    std::cout << "智能体析构" << std::endl;
    if (_v != nullptr)
    {
        delete _v;
        _v = nullptr;
    }
}

double Agent::policy(Action action)
{
    return 0.25;
}

double Agent::gamma()
{
    return _gamma;
}

double Agent::getStateValue(int state)
{
    return _v->find(state)->second;
}

void Agent::setStateValue(int state, double value)
{ 
    _v->at(state) = value;
}

void Agent::printStateValue()
{
    for (auto iter=_v->begin(); iter != _v->end(); iter++)
    {
        std::cout << std::round(iter->second*10)/10 << (iter->first%5 == 0 ? "\n" : "\t");
    }
}

void Agent::computeValueFunction()
{

}
