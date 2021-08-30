#include "Card.h"


Card::Card(int value)
        :_value(value)
{
    //card constructor
    /* std::cout << "Card constructor" << std::endl; */
}


int Card::operator+(Card& card)
{
    int sum = 0;
    sum = _value + card.getValue();
    return sum;
}

bool Card::usable()
{
    //只提转换Ace牌
    if ( _value == 11)
    {
        _value = 1;
        return true;
    }
    return false;
}

int Card::getValue()
{
    return _value;
}
