#include "learning_instance/moveToPoint/PointMoveEnv.h"
 
PointMoveEnv::PointMoveEnv()
{
    /* m_log.classLog("PointMoveEnv constructored~"); */
    initEnvironment();
}
 
PointMoveEnv::~PointMoveEnv()
{
    /* m_log.classLog("PointMoveEnv deconstructored~"); */
    /* if (p_point) */
    /* { */
    /*     delete p_point; */
    /*     p_point = nullptr; */
    /* } */
    /* if (p_point) */
    /*     m_log.errorLog("some thing hadn't been deleted in Class PointMoveEnv!"); */
}
 
void PointMoveEnv::generateEpisode(const Policy &behaviorPolicy, int maxLength) 
{
    generateBehaviorPolicy(behaviorPolicy);

    std::tuple<MyKey*, MyKey*, double> episode;
    MyKey state = m_states.at(cf::randomIntNumber(m_states.size() - 1));
    p_state = new State({state.at(0), state.at(1)});
    MyKey action = p_behaviorPolicy->policy(*p_state);
    p_action = new Action({action.at(0), action.at(1)});

    m_speed = 0;
    /* 调试代码 */
    {
        /* if (s == state) */
        /*     m_log.infoLog("s == state"); */
        /* s.printKey(); */
        /* a.printKey(); */
        /* std::get<0>(episode) = p_state; */
        /* std::get<1>(episode) = p_action; */
        /* std::get<2>(episode) = getReward(*p_state); */
        /* m_episodes.push(episode); */
        /* m_episodes.push(episode); */
    }
    bool isEndState = false;
    while (maxLength--)
    {
        std::get<0>(episode) = p_state;
        std::get<1>(episode) = p_action;
        /* p_state->printKey(); */
        /* p_action->printKey(); */
        isEndState = getNextState(*p_state, *p_action);
        std::get<2>(episode) = getReward(*p_state);
        /* std::stringstream ss; */
        /* ss << "reward: " << getReward(*p_state); */
        if (getReward(*p_state) == 1)
            m_cnt++;
        /* m_log.infoLog(ss.str()); */

        m_episodes.push(episode);
        if (isEndState)
        {
            /* m_log.infoLog("end!"); */
            /* p_point->policyIteration(m_episodes); */
            p_agent->policyIteration(m_episodes);
            break;
        }
        action = p_behaviorPolicy->policy(*p_state);
        p_action = new Action({action.at(0), action.at(1)});
    }
    /* p_point->policyIteration(m_episodes); */
    p_agent->policyIteration(m_episodes);
}
 
bool PointMoveEnv::getNextState(MyKey &state, const MyKey &action) 
{
    std::stringstream ss;
    int rx = state.at(0), ry = state.at(1);
    /* ss << "rx: " << rx << " ry: " << ry << "\n\t"; */
    int dx=0, dy=0;
    switch (action.at(0))
    {
    case Action::UP:
        dy = 1;
        break;
    case Action::DOWN:
        dy = -1;
        break;
    case Action::LEFT:
        dx = -1;
        break;
    case Action::RIGHT:
        dx = 1;
        break;
    default:
        break;
    }
    switch (action.at(1))
    {
    case Action::ACCEL:
        m_speed += 1;
        break;
    case Action::DECEL:
        m_speed += -1;
        break;
    case Action::STILL:
        break;
    default:
        break;
    }
    if (m_speed == 0)
        return true;

    /* ss << "dx: " << dx << " dy: " << dy << " speed: " << m_speed << "\n\t"; */

    rx += dx * m_speed; ry += dy * m_speed;

    /* ss << "rx: " << rx << " ry: " << ry << "\n\t"; */

    /* m_log.infoLog(ss.str()); */

    State* nextState = new State({rx, ry});

/*     nextState->printKey(); */

    auto findState = find_if(m_states.begin(), m_states.end(), [nextState](MyKey& state)
                             {
                             return (state == *nextState);
                             });

    p_state = nextState;
    if (findState == m_states.end())
    {
        return true;
    }

    if (*findState == m_targetState)
        return true;
    return false;
}
 
double PointMoveEnv::getReward(const MyKey &state) const 
{
    if (state == m_targetState && m_speed == 0)
        return 1;
    return -1;
}
void PointMoveEnv::initStates() 
{
    //to do::创建智能体可以探索的状态
    /* m_log.infoLog("to do::创建智能体可以探索的状态"); */
    for (int i=-5; i<5; i++)
        for (int o=-5; o<5; o++)
        {
            m_states.push_back(State({i, o}));
        }
    /* 调试代码 */
    {
        /* int cnt=0; */
        /* for (auto &state : m_states) */
        /* { */
        /*     cnt++; */
        /*     /1* state.printKey(); *1/ */
        /* } */
        std::cout << "states' cnt: " << m_states.size() << std::endl;
    }
}
 
void PointMoveEnv::initActions() 
{
    //to do::修改智能体可以采用的行动列表
    m_log.infoLog("to do::修改智能体可以采用的行动列表");
    std::vector<MyKey> actions;
    for (auto &state : m_states)
    {

        if (state.at(0) > 0 && state.at(1) > 0)
        {
            for (int i=3; i<5; i++)
                for (int o=-1; o<2; o++)
                {
                    actions.push_back(Action({i, o}));
                }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) < 0 && state.at(1) > 0)
        {
            for (int i=3; i<6; i+=2)
                for (int o=-1; o<2; o++)
                {
                    actions.push_back(Action({i, o}));
                }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) < 0 && state.at(1) < 0)
        {
            for (int i=2; i<6; i+=3)
                for (int o=-1; o<2; o++)
                {
                    actions.push_back(Action({i, o}));
                }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) > 0 && state.at(1) < 0)
        {
            for (int i=2; i<6; i+=2)
                for (int o=-1; o<2; o++)
                {
                    actions.push_back(Action({i, o}));
                }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) == 0 && state.at(1) < 0)
        {
            for (int o=-1; o<2; o++)
            {
                actions.push_back(Action({2, o}));
            }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) == 0 && state.at(1) > 0)
        {
            for (int o=-1; o<2; o++)
            {
                actions.push_back(Action({3, o}));
            }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) < 0 && state.at(1) == 0)
        {
            for (int o=-1; o<2; o++)
            {
                actions.push_back(Action({5, o}));
            }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) > 0 && state.at(1) == 0)
        {
            for (int o=-1; o<2; o++)
            {
                actions.push_back(Action({4, o}));
            }
            m_actions.insert(std::make_pair(state, actions));
        }
        else if (state.at(0) == 0 && state.at(1) == 0)
        {
            for (int o=-1; o<2; o++)
            {
                actions.push_back(Action({3, o}));
            }
            m_actions.insert(std::make_pair(state, actions));
        }
        actions.clear();
        /* for (int i=2; i<6; i++) */
        /*     for (int o=-1; o<2; o++) */
        /*     { */
        /*         actions.push_back(Action({i, o})); */
        /*     } */
        /* m_actions.insert(std::make_pair(state, actions)); */
        /* actions.clear(); */
    }
    /* 调试代码 */
    {
        int cnt=0;
        for (auto &items : m_actions)
        {
            /* items.first.printKey(); */
            cnt += items.second.size();
            /* for (auto &action : items.second) */
            /* { */
            /*     action.printKey(); */
            /*     cnt++; */
            /* } */
        }
        std::cout << "actions' cnt: " << cnt << std::endl;
    }
}
 
void PointMoveEnv::initAgents() 
{
    //to do::使用状态列表&行动列表创建智能体
    m_log.infoLog("to do::使用状态列表&行动列表创建智能体");
    /* p_point = new Point(m_states, m_actions); */
    /* p_point->setDiscount(0.9); */
    p_agent = new Point(m_states, m_actions);
    p_agent->setDiscount(0.9);
}
 
/* void PointMoveEnv::saveData(std::string foldName) */ 
/* { */
 /*    //to do::写一波保存数据的方法 */
 /*    m_log.infoLog("to do::写一波保存数据的方法"); */
 /*    /1* p_point->saveData(foldName); *1/ */
 /*    p_agent->saveData(foldName); */
/* } */
 
 
/* void PointMoveEnv::loadData() */ 
/* { */
 /*    bool loadData = false; */
 /*    m_log.inputLog("是否载入上次训练数据?[1/0]"); */
 /*    std::cin >> loadData; */

 /*    bool isDefault = true; */
 /*    std::string foldName = ""; */
 /*    m_log.inputLog("是否从默认文件夹载入训练数据?[1/0]"); */
 /*    std::cin >> isDefault; */

 /*    if (!isDefault) */
 /*    { */
 /*        m_log.inputLog("输入一波文件名：（现在还没做好这个功能, 还是从默认文件夹读取~）"); */
 /*        std::cin >> foldName; */
 /*    } */

 /*    foldName = ""; */

 /*    if (loadData) */
 /*        /1* p_point->loadData(foldName); *1/ */
 /*        p_agent->loadData(foldName); */
/* } */
 
/* void PointMoveEnv::episodesLoop(int times) */ 
/* { */
 /*    std::stringstream ss; */
 /*    ss << "totall episodes: "; */
 /*    ss << times; */

 /*    loadData(); */

 /*    while (times--) */
 /*    { */
 /*        /1* generateEpisode(p_point->getBehaviorPolicy()); *1/ */
 /*        generateEpisode(p_agent->getBehaviorPolicy()); */
 /*        clearEpisodes(); */
 /*    } */
 /*    ss << " success: " << m_cnt << "times!"; */
 /*    m_log.infoLog(ss.str()); */
 /*    saveData("testDir"); */
 /*    /1* saveData(); *1/ */
/* } */
 
/* void PointMoveEnv::generateBehaviorPolicy(const Policy &behaviorPolicy) */ 
/* { */
 /*    p_behaviorPolicy->clearPolicy(); */
 /*    /1* std::cout << "===========================" << std::endl; *1/ */
 /*    /1* int cnt = 0; *1/ */
 /*    for (auto &state : m_states) */
 /*    { */
 /*        auto action = cf::chooseAction(behaviorPolicy.getDistribution(), state, m_actions.at(state)); */

 /*        /1* std::cout << "probability: " << behaviorPolicy.policy(action, state) << std::endl; *1/ */
 /*        /1* cnt++; *1/ */
 /*        p_behaviorPolicy->insertPolicy(action, state, behaviorPolicy.policy(action, state)); */
 /*    } */
 /*    /1* std::cout << "cnt: " << cnt << std::endl; *1/ */
 /*    /1* std::cout << "===========================" << std::endl; *1/ */
/* } */
