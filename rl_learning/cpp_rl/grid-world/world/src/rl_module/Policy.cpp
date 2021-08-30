#include "rl_module/Policy.h"
 
Policy::Policy()
{
    /* m_log.classLog("Policy constructor is called!"); */
}
 
Policy::~Policy()
{
    /* m_log.classLog("Policy deconstructor is called!"); */
}
 
const MyKey& Policy::policy(const MyKey& state) const
{
    auto policy = m_policy.find(state);
    if (policy != m_policy.end())
        return policy->second;
    m_log.errorLog("state dosen't exist in the current policy!");
    return policy->second;
}
 
double Policy::policy(const MyKey& action, const MyKey& state) const
{
    auto distribution = m_distribution.find(std::make_pair(action, state));
    if (distribution != m_distribution.end())
        return distribution->second;
    m_log.errorLog("action-state pair doesn't exist in the current distribution!");
    return -1;
}
 
void Policy::insertPolicy(const MyKey& action, const MyKey& state, const double probabilty)
{
    /* 有报错很奇怪 */
    {
        /* m_policy[state] = action; */
        /* m_distribution[std::make_pair(action, state)] = probabilty; */
    }
    m_policy.insert(std::make_pair(state, action));
    m_distribution.insert(std::make_pair(std::make_pair(action, state), probabilty));
}
 
void Policy::eraseDistribution(const MyKey& action, const MyKey& state)
{
    /* action.printKey(); */
    auto findDistribution = m_distribution.find(std::make_pair(action, state));
    if (findDistribution != m_distribution.end())
        m_distribution.erase(std::make_pair(action, state));
    else
    {
        m_log.infoLog("do nothing!");
    }
}
 
void Policy::modifyAction(const MyKey state, const MyKey action)
{
    auto findPolicy = m_policy.find(state);
    if (findPolicy != m_policy.end())
    {
        m_policy.at(state) = action;
        /* m_log.warningLog("mark3~"); */
        modifyDistribution(state, action, 1);
        /* m_distribution.at(std::make_pair(action, state)) = 1; */
    }
    else
    {
        m_log.infoLog("create new state & distribution!");
        insertPolicy(action, state, 1);
    }
}
 
void Policy::modifyDistribution(const MyKey action, const MyKey state, const double probability)
{
    auto findDistribution = m_distribution.find(std::make_pair(action, state));
    if (findDistribution != m_distribution.end())
        m_distribution.at(std::make_pair(action, state)) = probability;
    else
    {
        /* m_log.infoLog("create new distribution!"); */
        m_distribution.insert(std::make_pair(std::make_pair(action, state), probability));
    }
}
 
const std::map<MyKey, MyKey>& Policy::getPolicy() const
{
    return m_policy;
}
 
const std::map<std::pair<MyKey, MyKey>, double>& Policy::getDistribution() const
{
    return m_distribution;
}
 
void Policy::clearPolicy()
{
    m_policy.clear();
    m_distribution.clear();
    /* 调试代码 */
    {
        /* std::stringstream ss; */
        /* ss << "m_policy's size: " << m_policy.size() */
        /*    << "\n\tm_distribution's size: " << m_distribution.size(); */
        /* m_log.infoLog(ss.str()); */
    }
}
 
int Policy::getDistributionSize()
{
    return m_distribution.size();
}
 
int Policy::getPolicySize()
{
    return m_policy.size();
}
