#include "gridWorld.h"

GridWorld::GridWorld()
{
    std::cout << "网格世界构造" << std::endl;
    _states = new std::set<int>;
    for (int i=1; i<=5; i++)
        for (int j=0; j<5; j++)
        {
            _states->insert(i+j*10);
        }
    _agent = new Agent;
}

GridWorld::~GridWorld()
{
    std::cout << "网格世界析构" << std::endl;
    if (_states != nullptr)
    {
        delete _states;
        _states = nullptr;
        std::cout << "释放_states" << std::endl;
    }
    if (_agent != nullptr)
    {
        delete _agent;
        _agent = nullptr;
        std::cout << "释放_agent" << std::endl;
    }
}

std::pair<int, int> GridWorld::getNextStateAndReward(int state, Action action)
{
    //获得下一个状态
    int nextState = state + actionsList[static_cast<int>(action)];
    //奖励默认为零
    int reward = 0;
    //如果状态为A
    if (state == 2)
    {
        nextState = 42;
        reward = 10;
    }
    //如果状态为B
    else if (state == 4)
    {
        nextState = 24;
        reward = 5;
    }
    //如果状态不在网格世界中
    else if (!_states->count(nextState))
    {
        nextState = state;
        reward = -1;
    }
    return std::pair<int, int>(nextState, reward);
}

void GridWorld::simulate()
{
    //智能体进行计算
    int state;
    double v, pv;
    do 
    {
        //pv用来确认收敛
        pv = _agent->getStateValue(1);
        for (auto iter=_states->begin(); iter!=_states->end(); iter++)
        {
            //对每个状态重置估计值
            v=0;
            state = *iter;
            /* std::cout << state << ((state % 5 == 0) ? "\n" : "\t"); */
            for (Action action = Action::up; action <= Action::right; action = static_cast<Action>(static_cast<int>(action) + 1))
            {
                auto nextStateAndReward = getNextStateAndReward(state, action);
                /* std::cout << "reward: " << nextStateAndReward.second <<  " s: " << nextStateAndReward.first <<  " v(s'): " << _agent->getStateValue(nextStateAndReward.first) << std::endl << std::endl; */
                v += _agent->policy(action) * (nextStateAndReward.second + _agent->gamma() * _agent->getStateValue(nextStateAndReward.first));
            }
            _agent->setStateValue(state, v);
        }
        /* std::cout << cnt++ << std::endl; */
        /* std::cout <<pv - _agent->getStateValue(1) << std::endl; */
    } while (std::fabs(pv - _agent->getStateValue(1)) > 1e-5);
    _agent->printStateValue();
}
