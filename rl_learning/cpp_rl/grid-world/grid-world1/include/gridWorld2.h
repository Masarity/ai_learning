#pragma once
#include "world.h"

class GridWorld2: private World
{
public:
    GridWorld2();
    ~GridWorld2();
    std::pair<int, int> getNextStateAndReward(int state, Action action) override;
    void simulate() override;

public:
    int actionsList[4] = {-10, 10, -1, 1};

private:
    std::set<int>* _states;

};

