#pragma once

#include "debug_module/Log.h"

#include "rl_module/MyKey.h"

#include "rl_module/commonFunc.h"

#include <map>

class Policy
{
public:
    explicit Policy();
    virtual ~Policy();

    /* 根据状态返回行动 */
    virtual const MyKey& policy(const MyKey& state) const;

    /* 根据行动-状态对返回概率 */
    virtual double policy(const MyKey& action, const MyKey& state) const;

    /* 插入新策略 */
    virtual void insertPolicy(const MyKey& action, const MyKey& state, const double probabilty);
    /* 移除非贪心策略的概率 */
    virtual void eraseDistribution(const MyKey& action, const MyKey& state);

    /* 修改原有的策略，并且不指定概率的话默认为1 */
    //to do::还待修改
    virtual void modifyAction(const MyKey state, const MyKey action);
    virtual void modifyDistribution(const MyKey action, const MyKey state, const double probability);

    /* 返回分布map */
    const std::map<std::pair<MyKey, MyKey>, double>& getDistribution() const;
    /* 返回策略map */
    const std::map<MyKey, MyKey>& getPolicy() const;
    /* 返回分布map的长度 */
    int getDistributionSize();
    /* 返回策略map的长度 */
    int getPolicySize();

    /* 清除已有策略 */
    void clearPolicy();


public:
    Log m_log;

protected:
    /* п(s) */
    std::map<MyKey, MyKey> m_policy; 
    /* п(a|s) */
    std::map<std::pair<MyKey, MyKey>, double> m_distribution;

private:

};

