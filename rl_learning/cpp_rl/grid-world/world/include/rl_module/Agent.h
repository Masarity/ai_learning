#pragma once

#include "debug_module/Log.h"

#include "rl_module/MyKey.h"
#include "rl_module/Policy.h"

#include "rl_module/commonFunc.h"

#include <stack>
#include <tuple>

#include <fstream>

class Agent
{
public:
    /* 使用环境提供的状态列表&行动列表的引用创建智能体，智能体知道它能干啥 */
    explicit Agent(std::vector<MyKey>& states, std::map<MyKey, std::vector<MyKey>>& actions);
    virtual ~Agent();

    /* 智能体需要知道训练项目的名称，也是默认训练数据保存的文件夹名 */
    void setName(const std::string name);
    std::string getName();

    /* 初始化方法 */
    virtual void initAgent();

    /* 根据状态给出相应的行动 */
    /* 1. 可视化中可以选择使用目标策略
     * 2. 正常训练只采用行为策略
     */
    virtual const MyKey& targetPolicy(const MyKey& state/*state*/) const;
    virtual const MyKey& behaviorPolicy(const MyKey& state/*state*/) const;

    /* 设置&获取折扣值 */
    void setDiscount(double discount);
    double gamma() const;

    /* 每个episode开始时调用 */
    /* 1.将W修改为1
     * 2.将G修改为0
     */
    void resetWG();

    /* 根据环境生成的片段进行策略迭代 */
    virtual void policyIteration(std::stack<std::tuple<MyKey*, MyKey*, double>> episodes);

    /* 保存训练数据 */
    /* 1.是否要做成纯虚函数？？
     */
    virtual void saveData(std::string foldName="");

    virtual void loadData(std::string foldName="") = 0;

    /* 返回生成训练任务样本的行为策略 */
    //to do::采用\epsilon-soft 策略进行探索，等概率随机策略收敛有点慢
    const Policy& getBehaviorPolicy();

    void setEpsilon(double epsilon);

protected:
    /* 生成soft-policy——用于更新行为策略 */
    virtual void generateSoftPolicy(const MyKey& action, const MyKey& state);

    /* epsilon-soft-policy */
    virtual void epsilonSoft(const MyKey& action, const MyKey& state);

    /* 拿到训练数据文件 */
    virtual std::string getDataFilePath(std::string foldName, std::string fileName);

    /* 保存一个智能体最基本的训练数据，可以重载增加替他特定任务所需要的数据 */
    virtual void saveActionValue(std::string foldName);
    virtual void saveTargetPolicy(std::string foldName);
    virtual void saveBehaviorPolicy(std::string foldName);

public:
    Log m_log;

protected:
    /* 文件夹名字——用于保存数据 */
    std::string m_name;

    /* 智能体需要知道自己需要处理的状态 */
    std::vector<MyKey>& m_states;
    /* 智能体需要知道自己在状态s下可以采取那些行动 */
    std::map<MyKey, std::vector<MyKey>>& m_actions;

    /* 折扣因子 */
    double m_gamma;

    /* 行动值函数 */
    std::map<std::pair<MyKey, MyKey>, double> m_Q;

    /* 行为策略п */
    Policy* p_behaviorPolicy;
    double m_epsilon;
    /* 目标策略п */
    Policy* p_targetPolicy;

    /* step分母函数 */
    std::map<std::pair<MyKey, MyKey>, double> m_C;

    /* 权重——step分子 */
    double m_W;

    /* 返回值 */
    double m_G;

private:

};

