#pragma once
#include <iostream>
#include <random>
#include <math.h>
#include <map>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <sstream>

class Card 
{
public:
    explicit Card(int value);

    //重载加号，让两张牌对象可以求和
    int operator+(Card& card);

    //将Ace由11转变为1
    bool usable();

    //如果爆牌了，传true将11改为1, 并且只会改Ace牌
    int getValue();

private:
    //牌的点数
    int _value;

};

