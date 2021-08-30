#include "Dealer.h"


Dealer::Dealer()
{
    /* std::cout << "Dealer construtor is called" << std::endl; */
    initPolicy();
}

void Dealer::initPolicy()
{
    for (int i=1; i<11; i++)
    {
        for (int o=12; o<17; o++)
        {
            std::get<0>(_policy) = i;
            std::get<1>(_policy) = o;
            std::get<2>(_policy) = true;
            _policys.push_back(_policy);
            _uPolicys.push_back(_policy);
        }
    }
    for (int i=1; i<11; i++)
    {
        for (int o=17; o<22; o++)
        {
            std::get<0>(_policy) = i;
            std::get<1>(_policy) = o;
            std::get<2>(_policy) = false;
            _policys.push_back(_policy);
            _uPolicys.push_back(_policy);
        }
    }

}

bool Dealer::policy()
{
    if (getPoints() < 17)
    {
        return true;
    }
    return false;
}

int Dealer::showOneCard()
{
    return _cards.begin()->getValue();
}
