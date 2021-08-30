#include "GridWorld1.h"

GridWorld1::GridWorld1(int dimension)
    :World(dimension)
{
    std::cout << "child constructor" << std::endl;
}

std::pair<int, int> GridWorld1::getNextStateAndReward(int state, int nextState)
{
    /* std::cout << "get nextState and reward" << std::endl; */
    int ns = nextState;
    int reward = -1;
    if (nextState == 0 || nextState == 33)
    {
        ns = -1;
        reward = 0;
    }
    else if (!_states->count(ns))
    {
        ns = state;
    }
    return std::pair<int, int>(ns, reward);
}

double GridWorld1::getWorldProbablity(int nextState, int reward, int state, Action action)
{
    std::cout << "get world probabilty"<< std::endl;
    return 1;
}
