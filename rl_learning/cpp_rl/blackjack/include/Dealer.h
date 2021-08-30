#pragma once

#include "Agent.h"


class Dealer
    :public Agent
{
public:
    Dealer();

    bool policy() override;

    //展示一张牌
    int showOneCard();

private:
    //初始化策略
    void initPolicy();

};
