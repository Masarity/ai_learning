#include "Agent.h"


Agent::Agent()
{
    /* std::cout << "Agent constructor called" << std::endl; */
}

void Agent::clearCards()
{
    _cards.clear();
    _sum = 0;
}

void Agent::getCard(Card card)
{
    _cards.push_back(card);
    _sum += card.getValue();
    //如果爆牌了，还有使用Ace牌的机会
    if (_sum > 21)
        _sumCards(true);
    findAce();
}

void Agent::findAce()
{
    for (auto &iter : _cards)
    {
        if (iter.getValue() == 11)
        {
            _usableAce = true;
            //找到了退出的逻辑
            return;
        }
    }
    _usableAce = false;
}

void Agent::_sumCards(bool usable)
{
    _sum = 0;
    if (usable)
    {
        for (auto &iter : _cards)
        {
            //将Ace牌11转成1，转成功返回true
            if (iter.usable())
                break;
        }
    }
    for (auto &iter : _cards)
    {
        _sum += iter.getValue();
    }
}

int Agent::getPoints()
{
    return _sum;
}

bool Agent::hasUsableAce()
{
    return _usableAce;
}

bool Agent::policy(std::pair<int, int> episodeState)
{
    if (!_usableAce)
    {
        auto iter = std::find_if(_policys.begin(), _policys.end(), [episodeState](std::tuple<int, int, bool> state)
                                 {
                                    return (episodeState.first == std::get<0>(state) && episodeState.second == std::get<1>(state));
                                 });
        //如果没有找到状态，那么就是无脑叫牌
        if (iter == _policys.end())
            return true;
        else 
            return std::get<2>(*iter);
    }
    auto iter = std::find_if(_uPolicys.begin(), _uPolicys.end(), [episodeState](std::tuple<int, int, bool> state) {
                                return (episodeState.first == std::get<0>(state) && episodeState.second == std::get<1>(state));
                             });
    //如果没有找到状态，那么就是无脑叫牌
    if (iter == _uPolicys.end())
        return true;
    else 
        return std::get<2>(*iter);

}
