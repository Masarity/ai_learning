#include "gridWorld2.h"

GridWorld2::GridWorld2()
{
    std::cout << "网格世界2构造" << std::endl;
    _states = new std::set<int>;
    for (int i=0; i<=3; i++)
        for (int j=0; j<4; j++)
        {
            _states->insert(i+j*10);
        }
}

GridWorld2::~GridWorld2()
{
    std::cout << "网格世界2析构" << std::endl;
    if (_states != nullptr)
    {
        delete _states;
        _states = nullptr;
        std::cout << "释放_states" << std::endl;
    }
}


std::pair<int, int> GridWorld2::getNextStateAndReward(int state, Action action)
{
    //获得下一个状态
    int nextState = state + actionsList[static_cast<int>(action)];
    //奖励默认为零
    int reward = 0;
    //如果是终止状态
    if (nextState == 0 || nextState == 43)
    {
        nextState = -1;
        reward = 0;
    }
    //如果状态不在网格世界中
    else if (!_states->count(nextState))
    {
        nextState = state;
        reward = -1;
    }
    /* return std::pair<int, int>(nextState, reward); */
    /* return std::pair<int, int>(nextState, reward + 1); */
    return std::pair<int, int>(nextState, reward);
    /* return std::pair<int, int>(nextState, reward + 10); */
}


void GridWorld2::simulate()
{
    //智能体进行计算
    int state;
    double v, pv, max, tmp, cnt=0;
    do 
    {
        //pv用来确认收敛
        pv = _agent->getStateValue(2);
        for (auto iter=_states->begin(); iter!=_states->end(); iter++)
        {
            //对每个状态重置估计值
            v=0;
            max=0;
            state = *iter;
            /* std::cout << state << ((state % 5 == 0) ? "\n" : "\t"); */
            for (Action action = Action::up; action <= Action::right; action = static_cast<Action>(static_cast<int>(action) + 1))
            {
                auto nextStateAndReward = getNextStateAndReward(state, action);
                /* std::cout << "reward: " << nextStateAndReward.second <<  " s: " << nextStateAndReward.first <<  " v(s'): " << _agent->getStateValue(nextStateAndReward.first) << std::endl << std::endl; */
                /* v += _agent->policy(action) * (nextStateAndReward.second + _agent->gamma() * _agent->getStateValue(nextStateAndReward.first)); */
                tmp = (nextStateAndReward.second + _agent->gamma() * _agent->getStateValue(nextStateAndReward.first));  
                if (tmp > max)
                {
                    max = tmp;
                }
            }
            v = max;
            _agent->setStateValue(state, v);
        }
        std::cout << cnt++ << std::endl;
        /* std::cout <<pv - _agent->getStateValue(1) << std::endl; */
        //收敛不能只判断一个值，可能会出问题（已找到例子）
    } while (std::fabs(pv - _agent->getStateValue(2)) > 1e-5);
    _agent->printStateValue();
}
