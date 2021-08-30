#pragma once
#include <math.h>
#include <iostream>
#include <map>
#include "constants.h"

class Agent
{
public:
    Agent();
    ~Agent();
    double policy(Action action);
    double gamma();
    double getStateValue(int state);
    void setStateValue(int state, double value);
    void printStateValue();
    /* void computeValueFunction(); */
    void resetState(int state);
    void getStateAndAction(int state, Action action);

private:
    std::map<int, double>* _v;
    double _gamma = 0.9;
    int _state;
    Action _action;

};

