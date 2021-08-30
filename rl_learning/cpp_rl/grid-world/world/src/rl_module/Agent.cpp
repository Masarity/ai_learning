#include "rl_module/Agent.h"
 
Agent::Agent(std::vector<MyKey>& states, std::map<MyKey, std::vector<MyKey>>& actions)
    : m_states(states)
    , m_actions(actions)
    , p_behaviorPolicy(new Policy)
    , p_targetPolicy(new Policy)
{
    initAgent();
}
 
Agent::~Agent()
{
    if (p_targetPolicy)
    {
        delete p_targetPolicy;
        p_targetPolicy = nullptr;
    }
    if (p_behaviorPolicy)
    {
        delete p_behaviorPolicy;
        p_behaviorPolicy = nullptr;
    }

    if (p_targetPolicy || p_behaviorPolicy)
    {
        m_log.errorLog("some thing hadn't been deleted in Class Agent!");
    }
}
 
void Agent::setName(const std::string name)
{
    m_name = name;
}
 
std::string Agent::getName()
{
    return m_name;
}
 
const MyKey& Agent::targetPolicy(const MyKey& state) const
{
    return p_targetPolicy->policy(state);
}
 
const MyKey& Agent::behaviorPolicy(const MyKey& state/*state*/) const
{
    return p_behaviorPolicy->policy(state);
}
 
void Agent::setDiscount(double discount)
{
    m_gamma = discount;
}
 
double Agent::gamma() const
{
    return m_gamma;
}
 
void Agent::resetWG()
{
    m_G = 0;
    m_W = 1;
}
 
void Agent::initAgent()
{
    m_name = "delfaut";
    m_epsilon = 0.1;
    for (auto &state : m_states)
    {
        for (auto &action : m_actions.at(state))
        {
            m_Q.insert(std::make_pair(std::make_pair(state, action), cf::randomRealNumber()));
            m_C.insert(std::make_pair(std::make_pair(state, action), 0));
            p_behaviorPolicy->insertPolicy(action, state, 1 / static_cast<double>(m_actions.at(state).size()));
        }

        MyKey argMaxa = m_actions.at(state).at(0);
        cf::maxArga(m_Q, state, m_actions.at(state), argMaxa);
        p_targetPolicy->insertPolicy(argMaxa, state, 1);
    }
}
 
void Agent::setEpsilon(double epsilon)
{
    m_epsilon = epsilon;
}
 
void Agent::generateSoftPolicy(const MyKey& action, const MyKey& state)
{
    epsilonSoft(action, state);
}
 
void Agent::epsilonSoft(const MyKey& action, const MyKey& state)
{
    int A = m_actions.at(state).size();
    for (auto &a : m_actions.at(state))
    {
        if (action == a)
            p_behaviorPolicy->modifyDistribution(a, state, 1.0 + (1.0 - A) * m_epsilon / A);
        else
            p_behaviorPolicy->modifyDistribution(a, state,  m_epsilon / A);
    }
}
 
void Agent::policyIteration(std::stack<std::tuple<MyKey*, MyKey*, double>> episodes)
{
    resetWG();

    while (!episodes.empty())
    {
        auto episode = episodes.top();

        MyKey state = *std::get<0>(episode);
        MyKey action = *std::get<1>(episode);
        double reward = std::get<2>(episode);

        m_G += m_gamma * m_G + reward;

        m_C.at(std::make_pair(state, action)) += m_W;

        double old_Q = m_Q.at(std::make_pair(state, action)); 
        double new_C = m_C.at(std::make_pair(state, action));

        m_Q.at(std::make_pair(state, action)) = old_Q + (m_W / new_C) * (m_G - old_Q); 

        MyKey argMaxa = m_actions.at(state).at(0);
        cf::maxArga(m_Q, state, m_actions.at(state), argMaxa);

        /* 调试代码 */
        {
            /* m_log.warningLog("mark2~"); */
            /* state.printKey(); */
            /* argMaxa.printKey(); */
        }
        p_targetPolicy->modifyAction(state, argMaxa);
        generateSoftPolicy(argMaxa, state);
        if (argMaxa == action)
        {
            /* m_log.warningLog("mark1~"); */
            /* m_W *= p_targetPolicy->policy(action, state) / p_behaviorPolicy->policy(action, state); */
            m_W *= 1 / p_behaviorPolicy->policy(action, state);
        }
        else
        {
            //to do::是否要加下面
            {
                /* p_targetPolicy->modifyDistribution(action, state, 0); */
                /* p_targetPolicy->eraseDistribution(action, state); */
            }
            break;
        }
        episodes.pop();
    }
}
 
const Policy& Agent::getBehaviorPolicy()
{
    return *p_behaviorPolicy;
}
 
void Agent::saveData(std::string foldName)
{
    if (foldName == "")
        foldName = m_name;

    std::stringstream ss;
    ss << "mkdir -p ../res/training/data/" + foldName;
    ::system(ss.str().c_str());

    saveActionValue(foldName);
    saveTargetPolicy(foldName);
    saveBehaviorPolicy(foldName);
}
 
std::string Agent::getDataFilePath(std::string foldName, std::string fileName)
{
    std::stringstream ss;
    ss << "../res/training/data/" << foldName << "/" << fileName << ".txt";
    return ss.str();
}
 
void Agent::saveActionValue(std::string foldName)
{
    std::ofstream ofs;
    ofs.open(getDataFilePath(foldName, "actionValue"), std::ios_base::out);
    if (!ofs.is_open())
        m_log.errorLog("failed to open: " + foldName + "/actionValue.txt" + "!");

    /* 细节删除最后一行的回车 */
    auto endIter = m_Q.end();
    endIter--;

    for (auto &items : m_Q)
    {
        for (int i=0; i<items.first.first.getSize(); i++)
        {
            if (i != items.first.first.getSize() - 1)
                ofs << items.first.first.at(i) << " ";
            else
                ofs << items.first.first.at(i) << std::endl;
        }
        for (int i=0; i<items.first.second.getSize(); i++)
        {
            if (i != items.first.second.getSize() - 1)
                ofs << items.first.second.at(i) << " ";
            else
                ofs << items.first.second.at(i) << std::endl;
        }
        if (items != *endIter)
            ofs << items.second << std::endl;
        else
            ofs << items.second;
    }
    ofs.close();
}
 
void Agent::saveTargetPolicy(std::string foldName)
{
    std::ofstream ofs;
    ofs.open(getDataFilePath(foldName, "targetPolicy"), std::ios_base::out);
    if (!ofs.is_open())
        m_log.errorLog("failed to open: " + foldName + "/targetPolicy.txt" + "!");

    auto endIter = p_targetPolicy->getPolicy().end();
    endIter--;

    for (auto &items : p_targetPolicy->getPolicy())
    {
        for (int i=0; i<items.first.getSize(); i++)
        {
            if (i != items.first.getSize() - 1)
                ofs << items.first.at(i) << " ";
            else
                ofs << items.first.at(i) << std::endl;
        }
        for (int i=0; i<items.second.getSize(); i++)
        {
            if (i != items.second.getSize() - 1)
                ofs << items.second.at(i) << " ";
            else
            {
                if (items != *endIter)
                    ofs << items.second.at(i) << std::endl;
                else
                    ofs << items.second.at(i);
            }
        }
    }
    ofs.close();
}
 
void Agent::saveBehaviorPolicy(std::string foldName)
{
    std::ofstream ofs;
    ofs.open(getDataFilePath(foldName, "behaviorPolicy"), std::ios_base::out);

    if (!ofs.is_open())
        m_log.errorLog("failed to open: " + foldName + "/behaviorPolicy.txt" + "!");

    auto endIter = p_behaviorPolicy->getDistribution().end();
    endIter--;

    for (auto &items : p_behaviorPolicy->getDistribution())
    {
        for (int i=0; i<items.first.first.getSize(); i++)
        {
            if (i != items.first.first.getSize() - 1)
                ofs << items.first.first.at(i) << " ";
            else
                ofs << items.first.first.at(i) << std::endl;
        }
        for (int i=0; i<items.first.second.getSize(); i++)
        {
            if (i != items.first.second.getSize() - 1)
                ofs << items.first.second.at(i) << " ";
            else
                ofs << items.first.second.at(i) << std::endl;
        }
        if (items != *endIter)
            ofs << items.second << std::endl;
        else
            ofs << items.second;
    }
    ofs.close();
}
