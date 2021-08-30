#include "rl_module/commonFunc.h"

double cf::randomRealNumber(double begin, double end)
{
    auto num = std::uniform_real_distribution<double>(begin, end);
    return num(cf::gen);
}
 
int cf::randomIntNumber(int end)
{
    auto num = std::uniform_int_distribution<int>(0, end);
    return num(cf::gen);
}
 
int cf::randomIntNumber(int begin, int end)
{
    auto num = std::uniform_int_distribution<int>(begin, end);
    return num(cf::gen);
}
 
bool cf::randomTrigger(double probability)
{
    double trigger = cf::randomRealNumber(0, 1);
    if (!probability)
        return false;
    if (trigger <= probability)
        return true;
    return false;
}
 
void cf::maxArga(const std::map<std::pair<MyKey, MyKey>, double>& Q, const MyKey& state, const std::vector<MyKey>& actions, MyKey& action)
{
    for (auto &iter : actions)
    {
        double actionValue =  Q.find(std::make_pair(state, action))->second;
        /* 调试代码 */
        {
            /* std::cout << "actionValue: " << actionValue << " "; */
            /* std::cout << "iterValue: "  << Q.find(std::make_pair(state, iter))->second << std::endl; */
        }
        if (Q.find(std::make_pair(state, iter))->second > actionValue)
            action = iter;
    }
}
 
const MyKey cf::chooseAction(const std::map<std::pair<MyKey, MyKey>, double>& distribution, const MyKey& state, const std::vector<MyKey>& actions)
{
    double nTrigger = 1;
    for (auto &action : actions)
    {
        double probability = distribution.at(std::make_pair(action, state));
        if (cf::randomTrigger(probability/ nTrigger))
            return action;
        else
        {
            nTrigger = nTrigger * (1 - (probability / nTrigger));
        }
    }
    return actions.at(actions.size() - 1);
}
