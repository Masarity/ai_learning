#pragma once

#include "Card.h"
#include "Player.h"
#include "Dealer.h"

class Environment
{
public:
    Environment();
    ~Environment();

    //创建牌库
    void createLibray();
    //输出牌库测试
    void printLibrary();

    //生成训练片段
    void createEpisode();
    void createActionEpisode();

    //发牌
    void dealtCard(Agent& agent);
    //叫牌
    void hits(Agent& agent, bool isPlayer = false);
    void hitsAction(Agent& agent, bool isPlayer = false);

    //返回奖励
    int reward();
    void simulate();

    //输出训练结果到文件
    void recordData(std::string fileName, const std::vector<std::tuple<int, int, double>>& stateValues);
    void saveData(std::string fileName);
    void loadData(std::string fileName);

protected:
    std::random_device rd;
    //庄家——monika
    Dealer monika;
    //庄家展示的牌
    int dealerShowCard;
    //玩家——masa
    Player masa;

    //第一次创建的崭新的一副牌
    std::vector<Card> newCardLibrary;
    //栈作为牌库
    std::stack<Card> cardLibrary;

    //生成的片段状态庄家出示手牌，玩家手牌之和，玩家是否拥有可用的Ace
    std::stack<std::tuple<int, int, bool>> episodeStates;
    //生成的片段状态庄家出示手牌，玩家手牌之和，玩家采取的行动，玩家是否拥有可用的Ace
    std::stack<std::tuple<int, int, bool, bool>> episodeActionStates;


private:
    int randomSelection(int end, int begin = 0);

    //初始化牌库
    void initLibrary();

};

