#pragma once
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <math.h>
#include "constants.h"
#include "agent.h"


class GridWorld
{
public:
    GridWorld();
    ~GridWorld();
    std::pair<int, int> getNextStateAndReward(int state, Action action);
    void simulate();

public:
    int actionsList[4] = {-10, 10, -1, 1};

private:
    //所有网格世界中的状态
    std::set<int>* _states;
    //创建智能体
    Agent* _agent;
};
