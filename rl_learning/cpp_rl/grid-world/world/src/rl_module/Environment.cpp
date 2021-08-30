#include "rl_module/Environment.h"
 
Environment::Environment()
    : p_behaviorPolicy(new Policy)
    , p_agent(nullptr)
{
    /* m_log.classLog("Environment constructored~"); */
}
 
Environment::~Environment()
{ 
    /* m_log.classLog("Environment deconstructored~"); */

    if (p_behaviorPolicy)
    {
        delete p_behaviorPolicy;
        p_behaviorPolicy = nullptr;
    }
    if (p_agent)
    {
        delete p_agent;
        p_agent = nullptr;
    }

    if (p_behaviorPolicy || p_agent)
    {
        m_log.errorLog("some thing hadn't been deleted in Class Agent!");
    }

    //to do::是否将行动集&状态集改变
    {
        /* if (m_states.size()) */
        /* { */
        /*     m_log.classLog("释放 状态"); */
        /*     for (auto &state : m_states) */
        /*     { */
        /*         delete state; */
        /*         state = nullptr; */
        /*     } */
        /* } */
        /* for (auto &items : m_actions) */
        /* { */
        /*     if (items.second.size()) */
        /*     { */
        /*         m_log.classLog("释放 行动"); */
        /*         for (auto &action : items.second) */
        /*         { */
        /*             delete action; */
        /*             action = nullptr; */
        /*         } */
        /*     } */
        /* } */
    }


    clearEpisodes();
}
 
void Environment::clearEpisodes()
{
    while (!m_episodes.empty())
    {
        /* m_log.classLog("释放 片段任务"); */
        if (std::get<0>(m_episodes.top()))
        {
            delete std::get<0>(m_episodes.top());
            std::get<0>(m_episodes.top()) = nullptr;
        }
        if (std::get<0>(m_episodes.top()))
        {
            delete std::get<1>(m_episodes.top());
            std::get<1>(m_episodes.top()) = nullptr;
        }
        m_episodes.pop();
    }
}
 
void Environment::episodesLoop(int times)
{
    std::stringstream ss;
    ss << "totall episodes: ";
    ss << times;

    loadData();

    while (times--)
    {
        generateEpisode(p_agent->getBehaviorPolicy());
        clearEpisodes();
    }
    m_log.infoLog(ss.str());

    /* saveData("testDir"); */
    saveData();
}
 
void Environment::generateBehaviorPolicy(const Policy& behaviorPolicy)
{
    p_behaviorPolicy->clearPolicy();
    for (auto &state : m_states)
    {
        auto action = cf::chooseAction(behaviorPolicy.getDistribution(), state, m_actions.at(state));
        p_behaviorPolicy->insertPolicy(action, state, behaviorPolicy.policy(action, state));
    }
}
 
void Environment::initEnvironment()
{
    initStates();
    initActions();
    initAgents();
}
 
void Environment::visualization()
{
    m_log.warningLog("可视化需要重写~");
}
 
void Environment::saveData()
{
    bool saveData = false;
    m_log.inputLog("是否保存本次训练数据?[1/0]");
    std::cin >> saveData;

    if (saveData)
    {
        bool isDefault = true;
        std::string foldName = p_agent->getName();
        m_log.inputLog("是否将训练数据保存到默认文件夹?[1/0]");
        std::cin >> isDefault;
        if (!isDefault)
        {
            m_log.inputLog("输入目标文件夹名称");
            std::cin >> foldName;
        }
        p_agent->saveData(foldName);
        m_log.infoLog("训练数据以保存至: " + foldName);
    }
}
 
void Environment::loadData()
{
    bool loadData = false;
    m_log.inputLog("是否载入上次训练数据?[1/0]");
    std::cin >> loadData;

    if (loadData)
    {
        bool isDefault = true;
        std::string foldName = "";
        m_log.inputLog("是否从默认文件夹载入训练数据?[1/0]");
        std::cin >> isDefault;

        if (!isDefault)
        {
            m_log.inputLog("输入一波文件名：（现在还没做好这个功能, 还是从默认文件夹读取~）");
            std::cin >> foldName;
        }

        foldName = "";

        p_agent->loadData(foldName);
    }
}
