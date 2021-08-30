#pragma once
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <math.h>
#include "constants.h"
#include "agent.h"


class World
{
public:
    World();
    ~World();
    virtual std::pair<int, int> getNextStateAndReward(int state, Action action)=0;
    virtual void simulate()=0;

public:
    //所有网格世界中的状态
    std::set<int>* _states;
    //创建智能体
    Agent* _agent;
};
