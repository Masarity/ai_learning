#pragma once
#include "world.h"

class GridWorld1: public World
{
public:
    GridWorld1(int dimension);
    std::pair<int, int> getNextStateAndReward(int state, int nextState) override;
    double getWorldProbablity(int nextState, int reward, int state, Action action) override;

private:

};

