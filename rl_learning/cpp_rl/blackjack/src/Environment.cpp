#include "Environment.h"


Environment::Environment()
{
    /* std::cout << "Environment constructor is called" << std::endl; */
}

Environment::~Environment()
{

}

void Environment::createLibray()
{
    //打乱牌序
    std::random_shuffle(newCardLibrary.begin(), newCardLibrary.end());

    //每次初始化将牌库清理一波
    std::stack<Card> emptyLibrary;

    cardLibrary.swap(emptyLibrary);

    //21点最多不会使用超过15张牌
    for (int i=0; i<15; i++)
    {
        /* cardLibrary.push(newCardLibrary.at(randomSelection(53))); */
        //将牌洗好取前15张
        cardLibrary.push(newCardLibrary.at(i));
    }
}

int Environment::randomSelection(int end, int begin)
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> u(begin, end);
    return u(gen);
}

void Environment::initLibrary()
{
    //4张Ace、2、3、4、5、6、7、8、9牌
    for (int i=0; i<4; i++)
    {
        //细节取11, 保证最开始是usable状态
        newCardLibrary.push_back(Card(11));
        newCardLibrary.push_back(Card(2));
        newCardLibrary.push_back(Card(3));
        newCardLibrary.push_back(Card(4));
        newCardLibrary.push_back(Card(5));
        newCardLibrary.push_back(Card(6));
        newCardLibrary.push_back(Card(7));
        newCardLibrary.push_back(Card(8));
        newCardLibrary.push_back(Card(9));
    }

    //18张10
    for (int i=0; i<18; i++)
    {
        newCardLibrary.push_back(Card(10));
    }
}

void Environment::printLibrary()
{
    int cnt = 1;
    std::stack<Card> tmp(cardLibrary);

    while (!cardLibrary.empty())
    {
        std::cout << cardLibrary.top().getValue() << "\t";
        cardLibrary.pop();
        if (cnt < 5)
            cnt++;
        else
        {
            cnt = 1;
            std::cout << std::endl;
        }
    }
    cardLibrary.swap(tmp);
}

void Environment::dealtCard(Agent& agent)
{
    agent.getCard(cardLibrary.top());
    cardLibrary.pop();
}

void Environment::createEpisode()
{
    //创建牌库
    createLibray();
    /* //输出牌库瞅瞅 */
    /* printLibrary(); */

    //清除玩家&庄家手牌
    masa.clearCards();
    monika.clearCards();

    //将上一个片段任务存储的状态清除
    std::stack<std::tuple<int, int, bool>> emptyStates;
    episodeStates.swap(emptyStates);

    //开始一局21点，双方发两张牌
    for (int i=0; i<2; i++)
    {
        dealtCard(masa);
        dealtCard(monika);
    }

    //测试代码
    {
    /* std::cout << "monika's sum of card: " << monika.getPoints() << std::endl; */
    /* std::cout << "monika's showOneCard: " << monika.showOneCard() << std::endl; */

    /* std::cout << "masa's sum of card: " << masa.getPoints() << std::endl; */
    /* std::cout << "masa has Ace: " << masa.hasUsableAce() << std::endl; */

    }

    dealerShowCard = monika.showOneCard() == 11 ? 1 : monika.showOneCard();

    episodeStates.push(std::make_tuple(dealerShowCard, masa.getPoints(),
                                       masa.hasUsableAce()));
}

void Environment::createActionEpisode()
{
    //创建牌库
    createLibray();
    /* //输出牌库瞅瞅 */
    /* printLibrary(); */

    //清除玩家&庄家手牌
    masa.clearCards();
    monika.clearCards();

    //将上一个片段任务存储的状态清除
    std::stack<std::tuple<int, int, bool, bool>> emptyActionStates;
    episodeActionStates.swap(emptyActionStates);

    //开始一局21点，双方发两张牌
    for (int i=0; i<2; i++)
    {
        dealtCard(masa);
        dealtCard(monika);
    }

    //测试代码
    {
    /* std::cout << "monika's sum of card: " << monika.getPoints() << std::endl; */
    /* std::cout << "monika's showOneCard: " << monika.showOneCard() << std::endl; */

    /* std::cout << "masa's sum of card: " << masa.getPoints() << std::endl; */
    /* std::cout << "masa has Ace: " << masa.hasUsableAce() << std::endl; */

    }

    dealerShowCard = monika.showOneCard() == 11 ? 1 : monika.showOneCard();

    episodeActionStates.push(std::make_tuple(dealerShowCard, masa.getPoints(),
                                             randomSelection(1), masa.hasUsableAce()));
}

void Environment::hits(Agent &agent, bool isPlayer)
{
    if (isPlayer)
    {
        /* std::cout << "masa's sum of cards: " << agent.getPoints() << "\n"; */
        auto state = std::make_pair(std::get<0>(episodeStates.top()), std::get<1>(episodeStates.top()));
        bool action = agent.policy(state);
        /* while (agent.getPoints() < 22 && agent.policy(state)) */
        while (agent.getPoints() < 22 && action)
        {
            dealtCard(agent);
            //如果是玩家，并且玩家的点数小于22那么玩家在此片段训练中获得一个新的状态
            /* if (masa.getPoints() < 22) */
            episodeStates.push(std::make_tuple(dealerShowCard, agent.getPoints(), agent.hasUsableAce()));
            /* if (!action) */
            /*     break; */
            state = std::make_pair(std::get<0>(episodeStates.top()), std::get<1>(episodeStates.top()));
            action = agent.policy(state);
            /* std::cout << "masa's sum of cards: " << agent.getPoints() << "\n"; */
        }
    }
    else 
    {
        /* std::cout << "monika's sum of cards: " << agent.getPoints() << "\n"; */
        while (agent.policy())
        {
            dealtCard(agent);
            /* std::cout << "monika's sum of cards: " << agent.getPoints() << "\n"; */
        }
    }

}

void Environment::hitsAction(Agent &agent, bool isPlayer)
{
    if (isPlayer)
    {
        auto state = std::make_pair(std::get<0>(episodeActionStates.top()), std::get<1>(episodeActionStates.top()));
        bool action = agent.policy(state);
        while (agent.getPoints() < 22)
        {
            dealtCard(agent);
            //如果是玩家，并且玩家的点数小于22那么玩家在此片段训练中获得一个新的状态
            episodeActionStates.push(std::make_tuple(dealerShowCard, agent.getPoints(),
                                               action, agent.hasUsableAce()));
            if (!action)
                break;
            state = std::make_pair(std::get<0>(episodeActionStates.top()), std::get<1>(episodeActionStates.top()));
            action = agent.policy(state);
        }
    }
    else 
    {
        while (agent.policy())
        {
            dealtCard(agent);
        }
    }

}

int Environment::reward()
{
    //玩家&庄家点数相等默认为0
    int r = 0;
    //如果玩家爆牌且庄家没有爆牌
    if (masa.getPoints() > 21 && monika.getPoints() < 22)
        r = -1;
    //如果玩家&庄家都爆牌
    else if (masa.getPoints() > 21 && monika.getPoints() > 21)
        r = 0;
    //还剩下玩家未爆牌庄家爆牌，玩家&庄家都未爆牌的情况
    else
    {
        if (monika.getPoints() > 21 || masa.getPoints() > monika.getPoints())
            r = 1;
        else if (masa.getPoints() < monika.getPoints())
            r = -1;
    }
    return r;
}

void Environment::simulate()
{
    int times;
    std::cout << "the times of simulation: ";
    std::cin >> times;
    bool evaluateStateValue= false;

    bool loadDataFromFile = false;
    std::cout << "continue last training staff? [1/0] ";
    std::cin >> loadDataFromFile;


    std::cout << "evaluate stateValues? [1/0] ";
    std::cin >> evaluateStateValue;

    if (loadDataFromFile)
    {
        std::cout << "load value" << std::endl;
        loadData("cardsLibrary");
        masa.loadData();
    }
    else
    {
        std::cout << "init value" << std::endl;
        initLibrary();
        masa.initVirables();
    }

    for (int i=0; i<times; i++)
    {
        //创建片段任务
        createActionEpisode();
        //玩家先叫牌
        hitsAction(masa, true);
        //庄家后叫牌
        hitsAction(monika);
        //玩家进行策略评估，现在是计算值函数
        masa.policyEvaluation(reward(), episodeActionStates);
        masa.policyImprovement(episodeActionStates);
    }       
    /* masa.printActionValues(); */
    /* masa.printPolicy(); */
    /* std::cout << "isStable:" << stable << std::endl; */

    saveData("cardsLibrary");
    if (evaluateStateValue)
    {
        for (int i=0; i<500000; i++)
        {
            //创建片段任务
            createEpisode();
            //玩家先叫牌
            hits(masa, true);
            //庄家后叫牌
            hits(monika);
            //玩家进行策略评估，现在是计算值函数
            masa.policyEvaluation(reward(), episodeStates);
        }       
        /* masa.printStateValues(); */

        auto uStateValuesConstPtr = masa.getStateValues(true);
        auto stateValuesConstPtr = masa.getStateValues();

        recordData("new_usableData.dat", uStateValuesConstPtr);
        recordData("new_noUsableData.dat", stateValuesConstPtr);
        /* recordData("usableData.dat", uStateValuesConstPtr); */
        /* recordData("noUsableData.dat", stateValuesConstPtr); */
    }
    masa.saveData();
}

void Environment::recordData(std::string fileName, const std::vector<std::tuple<int, int, double>>& stateValues)
{

    std::ofstream ofs;
    ofs.open(fileName, std::ios_base::out);

    int cnt = 1;
    if (ofs.is_open())
    {
        std::cout << fileName << " is opened" << std::endl;
        for (auto &iter : stateValues)
        {
            ofs << std::get<0>(iter) << " "; 
            ofs << std::get<1>(iter) << " "; 
            ofs << std::get<2>(iter) << " "; 
            ofs << std::endl;
            if (cnt < 10)
                cnt++;
            else
            {
                ofs << std::endl;
                cnt = 1;
            }
        }
    }
    ofs.close();
}

void Environment::saveData(std::string fileName)
{
    std::ofstream ofs;
    std::stringstream ss;

    ss << "../trainData/";
    ss << fileName;
    ofs.open(ss.str(), std::ios_base::out);

    if (ofs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        for (auto &iter : newCardLibrary)
        {
            ofs << iter.getValue(); 
            ofs << std::endl;
        }
    }
    ofs.close();

}

void Environment::loadData(std::string fileName)
{
    std::ifstream ifs;
    std::stringstream ss;

    ss << "../trainData/";
    ss << fileName;

    ifs.open(ss.str(), std::ios_base::in);

    if (ifs.is_open())
    {
        int cardPoint;
        while (!ifs.eof())
        {
            ifs >> cardPoint;
            newCardLibrary.push_back(Card(cardPoint));
        }
    } 

    ifs.close();
}
