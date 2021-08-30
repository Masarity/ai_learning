#pragma once
#include "agent.h"

class Agent1: public Agent
{
public:
    Agent1(int dimension);

    Action policy(int state) override;
    bool policyEvaluation(World& world) override;
    bool policyImprovement(World& world) override;


private:

};

