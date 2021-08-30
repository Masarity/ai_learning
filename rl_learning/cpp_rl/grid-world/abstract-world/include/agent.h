#pragma once
#include <iostream>

#include <vector>
#include <stack>
#include <map>

#include <math.h>
#include <random>

#include "constants.h"
#include "world.h"

class Agent
{
public:
    Agent(int dimension);
    ~Agent();
    //折扣因子的设定&使用
    void setDiscount(double gamma);
    double getDiscount();
    //修改&获取值函数估计表中的值
    bool isStateValueExist(int state);
    double getStateValue(int state);
    void setStateValue(int state, double value);
    //打印值函数表
    void printStateValue(int decimalPlace);
    //重置智能体的状态
    void resetState(int state);

    //拿到下一个状态&奖励
    std::pair<int, int> nextStateAndReward(int state, Action action, World& world);
    //拿到世界策略
    double worldProbablity(int nextState, int reward, int state, Action action, World& world);
    bool randomTrigger(double probability);
    double findMaxDelta(std::map<int, double>& v);
    Action argMaxa(int state, World& world);
    double maxa(int action, double (*_finc)(int action));
    //策略为条件函数
    virtual Action policy(int state)=0;
    //策略评估
    virtual bool policyEvaluation(World& world)=0;
    //策略优化
    virtual bool policyImprovement(World& world)=0;

public:
    int _dimension;
    //值函数估计表
    std::map<int, double>* _valueTable;
    //行动数组
    int _actionsList[4] = {-10, 10, -1, 1};
    std::map<int, Action>* _policiesList;
    //折扣因子 
    double _gamma = 0;
    //智能体的状态&行动
    int _state;
};

