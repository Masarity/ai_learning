#include "agent.h"

Agent::Agent(int dimension)
    :_dimension(dimension)
    ,_valueTable(new std::map<int, double>)
    ,_policiesList(new std::map<int , Action>)
{
    std::cout << "智能体构造" << std::endl;
    for (int i=0; i<dimension; i++)
        for (int j=0; j<dimension; j++)
        {
            _valueTable->insert(std::pair<int, double>(i+j*10, 0));
            _policiesList->insert(std::pair<int, Action>(i+j*10, Action::down));
        }
}

Agent::~Agent()
{
    std::cout << "智能体析构" << std::endl;
    if (_valueTable != nullptr)
    {
        delete _valueTable;
        _valueTable = nullptr;
    }
    if (_policiesList != nullptr)
    {
        delete _policiesList;
        _policiesList = nullptr;
    }
}

void Agent::setDiscount(double gamma)
{
    if (gamma >= 0 && gamma <= 1)
    {
        std::cout << "DISCOUNT> SET GAMMA :" << gamma << std::endl;
        _gamma = gamma;
    }
    else
    {
        std::cout << "DISCOUNT> ERROR: INVALID RANGE GAMMA SHOULD BE IN [0, 1]" << std::endl;

    }
}

double Agent::getDiscount()
{
    return _gamma;
}

bool Agent::isStateValueExist(int state)
{
    if (_valueTable->count(state))
        return true;
    else
        std::cout << "GET> ERROR: INVALID STATE VALUE" << std::endl;
    return false;
}

double Agent::getStateValue(int state)
{
    return _valueTable->at(state);
}

void Agent::setStateValue(int state, double value)
{ 
    _valueTable->at(state) = value;
}

void Agent::printStateValue(int decimalPlace)
{
    for (auto iter=_valueTable->begin(); iter != _valueTable->end(); iter++)
    {
        std::cout << std::round(iter->second*decimalPlace)/decimalPlace << (((iter->first+1)%10)%(_dimension) == 0 ? "\n" : "\t");
    }
}


std::pair<int, int> Agent::nextStateAndReward(int state, Action action, World& world)
{
    int nextState = state + _actionsList[static_cast<int>(action)];
    return world.getNextStateAndReward(state, nextState);
}


double Agent::worldProbablity(int nextState, int reward, int state, Action action, World& world)
{
    return world.getWorldProbablity(nextState, reward, state, action);
}

bool Agent::randomTrigger(double probability)
{

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<double> average(0, 1);

    if (average(eng) < probability)
        return true;
    return false;
}


double Agent::findMaxDelta(std::map<int, double>& v)
{
    double max=-10000;
    for (int i=0; i < _dimension; i++)
        for (int j=0; j < _dimension; j++)
        {
            int key = i + j*10;
            if (max < std::fabs((v.at(key) - _valueTable->at(key))))
                max = std::fabs((v.at(key) - _valueTable->at(key)));
        }
    /* std::cout << "max:" << max << std::endl; */
    return max;
}

Action Agent::argMaxa(int state, World& world)
{
    double maxState = -10000;
    double tmp;
    Action action = Action::up;
    auto nsAr = nextStateAndReward(state, action, world);

    if (nsAr.first == -1)
        maxState = nsAr.second;
    else
        maxState = nsAr.second + getDiscount() * _valueTable->at(nsAr.first);
    for (int i=1; i < 4; i++)
    {
        auto nsar = nextStateAndReward(state, static_cast<Action>(i), world);
        /* std::cout << "key: " << nsar.first << std::endl; */
        if (nsar.first == -1)
            tmp = nsar.second;
        else
            tmp = nsar.second + getDiscount() * _valueTable->at(nsar.first);
        /* std::cout << "tmp: " << tmp << std::endl; */
        if (tmp > maxState)
        {
            maxState = tmp;
            action = static_cast<Action>(i);
        }
    }
    return action;
}
