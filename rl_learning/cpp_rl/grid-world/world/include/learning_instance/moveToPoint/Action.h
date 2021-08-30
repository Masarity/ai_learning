#pragma once

#include "rl_module/MyKey.h"

class Action
    :public MyKey
{
public:
    explicit Action(std::initializer_list<int> describes);
    virtual ~Action();

    /* 调试用 */
    void printKey() const override;

public:
    enum Move
    {
        UP = 2,
        DOWN,
        LEFT,
        RIGHT,
    };

    enum Speed
    {
        DECEL = -1,
        STILL = 0,
        ACCEL = 1,
    };

private:

};

