#pragma once

#include "rl_module/MyKey.h"

class State
    : public MyKey
{
public:
    explicit State(std::initializer_list<int> describes);
    virtual ~State();

    /* 调试用 */
    void printKey() const override;

private:

public:

private:

};

