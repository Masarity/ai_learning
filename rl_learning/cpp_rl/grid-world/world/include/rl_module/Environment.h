#pragma once

#include "rl_module/Agent.h"

#include <algorithm>

class Environment
{
public:
    explicit Environment();
    virtual ~Environment();

    /* 片段循环，给定循环次数 */
    virtual void episodesLoop(int times);

    /* 生成行为策略 */
    virtual void generateBehaviorPolicy(const Policy& behaviorPolicy);

    /* 必须要实现的三个方法 */
    /* 根据传入的策略生成片段任务 */
    virtual void generateEpisode(const Policy& behaviorPolicy, int maxLength=10/*behaviorPolicy & length*/) = 0;
    /* 返回下一个状态，生成片段任务调用 */
    virtual bool getNextState(MyKey& state, const MyKey& action/*current state & action */) = 0;
    /* 返回奖励 */
    virtual double getReward(const MyKey& state/*state*/) const = 0;

    /* 保存训练数据 */
    virtual void saveData();

    virtual void loadData();

    /* 将片段任务的训练可视化 */
    virtual void visualization();

protected:
    /* 初始化环境
     * 1.给出状态列表&行动列表
     * 2.初始化片段任务栈
     * 3.初始化智能体
     */
    virtual void initEnvironment();
    /* 子类需要实现 */
    virtual void initStates() = 0;
    virtual void initActions() = 0;
    virtual void initAgents() = 0;

    /* 清除使用结束的片段任务 */
    void clearEpisodes();

public:
    Log m_log;

protected:
    /* 环境提供——智能需要处理的状态 */
    std::vector<MyKey> m_states;
    /* 环境提供——智能体在状态s下可以采取那些行动 */
    std::map<MyKey, std::vector<MyKey>> m_actions;

    /* 使用栈来描述生成片段任务的状态-行动-奖励序列 */
    std::stack<std::tuple<MyKey*, MyKey*, double>> m_episodes;

    /* 在环境中的行为策略，与智能体中的行为策略不同，单一指向！ */
    Policy* p_behaviorPolicy;

    /* 子类只需要负责创建智能体对象不同管析构 */
    //to do::可能一个环境中不止有一个智能体，可以修改为map
    Agent* p_agent;

private:

};

