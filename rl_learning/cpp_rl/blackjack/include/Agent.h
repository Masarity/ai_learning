#pragma once
#include "Card.h"

class Agent
{
public:
    Agent();

    //手牌重新洗入牌库
    void clearCards();

    //获得手牌，也获得新的状态,立即进行求和后判断Ace牌是否存在
    void getCard(Card card);

    //返回手牌的点数
    int getPoints();

    //返回手牌中是否含有Ace牌
    bool hasUsableAce();

    //返回true叫牌，false叫停
    virtual bool policy() = 0;
    //根据状态查找策略
    bool policy(std::pair<int, int> episodeState);



protected:
    //将手牌求和
    void _sumCards(bool usable=false);
    //判断手牌中是否有可用的Ace牌
    void findAce();

    //手牌
    std::vector<Card> _cards;
    int _sum = 0;
    //手牌中是否有可用的Ace牌
    bool _usableAce = false;

    //策略
    std::vector<std::tuple<int, int, bool>> _policys;
    std::vector<std::tuple<int, int, bool>> _uPolicys;
    std::tuple<int, int, bool> _policy;


};
