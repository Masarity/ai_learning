#include "Agent1.h"

Agent1::Agent1(int dimension)
    :Agent(dimension)
{
    std::cout << "baby agent constructor" << std::endl;
}


Action Agent1::policy(int state)
{
    return _policiesList->at(state);
}

bool Agent1::policyEvaluation(World& world)
{
    std::map<int, double> v;
    do
    {
        Action action;
        v = *_valueTable;
        for (int i=0; i < _dimension; i++)
            for (int j=0; j < _dimension; j++)
        /* for (auto iter = _valueTable->begin(); iter != _valueTable->end(); iter++) */
        {
            int key = i + j*10;
            if (key == 0 || key == 33)
                continue;
            auto iter = _valueTable->find(key);
            action = policy(iter->first);
            auto nsAr = nextStateAndReward(iter->first, action, world);
            /* std::cout << "current sate:" << key << std::endl; */
            /* std::cout << "state and reward" << nsAr.first << ", " << nsAr.second << std::endl; */
            if (nsAr.first == -1)
            {
                iter->second = nsAr.second;
                /* break; */
            }
            else
                iter->second = nsAr.second + getDiscount() * _valueTable->at(nsAr.first);
        }
    }while (findMaxDelta(v) > 1e-3);   
    printStateValue(10);

    return true;
}

bool Agent1::policyImprovement(World& world)
{
    bool stable; 
    int i=2;
    Action oldAction;
    do
    {
        stable = true;
        policyEvaluation(world);
        for (int i=0; i < _dimension; i++)
            for (int j=0; j < _dimension; j++)
        {
            int key = i + j*10;
            if (key == 0 || key == 33)
                continue;
            auto iter = _policiesList->find(key);
            oldAction = policy(iter->first);
            iter->second = argMaxa(key, world);
            /* std::cout << (oldAction == Action::up) << std::endl; */
            /* std::cout << (iter->second == Action::up) << std::endl; */
            if (iter->second != oldAction)
                stable = false;
        }
    }while (!stable);   
    return stable;
}
