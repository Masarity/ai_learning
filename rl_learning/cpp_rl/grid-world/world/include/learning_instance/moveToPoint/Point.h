#pragma once

#include "rl_module/Agent.h"

class Point
    : public Agent
{
public:
    explicit Point(std::vector<MyKey>& states, std::map<MyKey, std::vector<MyKey>>& actions);
    virtual ~Point();

    /* void saveData() override; */

    void loadData(std::string foldName = "") override;

protected:
    /* void saveActionValue(std::string) override; */
    /* void saveTargetPolicy(std::string) override; */
    /* void saveBehaviorPolicy(std::string) override; */

    void loadActionValue(std::string foldName);
    void loadTargetPolicy(std::string foldName);
    void loadBehaviorPolicy(std::string foldName);

public:

private:

};

