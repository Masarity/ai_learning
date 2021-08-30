#pragma once
#include <iostream>

#include <set>

#include <math.h>

#include "constants.h"


class World
{
public:
    World(int dimension);
    ~World();
    //获取下一个状态以及获得的奖励
    virtual std::pair<int, int> getNextStateAndReward(int state, int nextState)=0;
    //世界概率
    virtual double getWorldProbablity(int nextState, int reward, int state, Action action)=0;
    /* virtual void simulate()=0; */

public:
    int _dimension;
    //所有网格世界中的状态
    std::set<int>* _states;
};
