#pragma once

#include "rl_module/Environment.h"
#include "learning_instance/moveToPoint/State.h"
#include "learning_instance/moveToPoint/Action.h"
#include "learning_instance/moveToPoint/Point.h"

class PointMoveEnv
    : public Environment
{
public:
    explicit PointMoveEnv();
    virtual ~PointMoveEnv();

    /* void episodesLoop(int times) override; */

    /* void generateBehaviorPolicy(const Policy &behaviorPolicy) override; */

    void generateEpisode(const Policy &behaviorPolicy, int maxLength = 100) override;

    bool getNextState(MyKey &state, const MyKey &action) override;

    double getReward(const MyKey &state) const override;

    /* void saveData(std::string foldName="") override; */

    /* void loadData() override; */

protected:
    void initStates() override;
    void initActions() override;
    void initAgents() override;

    /* void createActions(); */
protected:

public:

private:
    /* Point* p_point; */
    int m_speed;

    State* p_state;
    Action* p_action;
    State m_targetState = State({0, 0});

    int m_cnt=0;

};

