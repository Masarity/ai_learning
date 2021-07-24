#include "EstimateMethods.hpp"

class EstimateMethods;
EstimateMethods::EstimateMethods()
{
    std::cout << "估计算法对象载入成功~"  << std::endl;

}

EstimateMethods::~EstimateMethods()
{
    std::cout << "估计算法对象析构成功~"  << std::endl;

}

int EstimateMethods::randomSelection(std::vector<int>& table)
{   
    /* int a; */
    /* srand((unsigned int)time(NULL));//设置当前时间为种子 */
    /* a = rand()%((int)table.size()); */
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> average(0, (int)table.size() - 1);
    /* std::cout << "seke: \t" << average(eng) << std::endl; */
    /* std:: cout << "ta:\t" << table.at(1) << std::endl; */
    return table.at(average(eng));
    /* return table.at(a); */
}

bool EstimateMethods::randomTrigger(double probability)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<double> average(0, 1);
    if (probability >= average(eng))
        return true;
    return false;
}

std::vector<int> EstimateMethods::findActionList(const std::map<int, std::pair<int, double>>* table)
{
    std::vector<int> actionList;
    double maxQ=INT_MIN;
    for (auto iter=table->begin(); iter != table->end(); iter++)
    {
        /* std::cout << fabs(maxQ - iter->second.second) << std::endl; */
        if (fabs(maxQ - iter->second.second) < 1e-5)
        {
            actionList.emplace_back(iter->first);
        }
        else if (maxQ < iter->second.second)
        {
            actionList.clear();
            maxQ = iter->second.second;
            actionList.emplace_back(iter->first);
        }
    }
    return actionList;
}

int EstimateMethods::greedySelection(const std::map<int, std::pair<int, double>>* esTable)
{
    //找最大值
    std::vector<int> actionList;
    actionList = findActionList(esTable);
    /* std::cout << "action size:\t" << (int)actionList.size() << std::endl; */
    return randomSelection(actionList);
}

int EstimateMethods::epsilonGreedySelection(const std::map<int, std::pair<int, double>>* esTable, double epsilon)
{
    std::vector<int> actionList;
    if (randomTrigger(epsilon))
    {
        for (int i=1; i<=(int)esTable->size(); i++)
        {
            actionList.emplace_back(i);
        }
        return randomSelection(actionList);
    }
    actionList = findActionList(esTable);
    return randomSelection(actionList);
}

int EstimateMethods::ucbSelection(const std::map<int, std::pair<int, double>>* esTable, double confidence, int t)
{
    auto newEsTable = *esTable;
    for (auto iter=newEsTable.begin(); iter!=newEsTable.end(); iter++)
    {
        if (iter->second.first != 0)
            iter->second.second += confidence * std::sqrt(std::log(t) / iter->second.first);
        else
            iter->second.second = 1000;
    }
    std::vector<int> actionList;
    actionList = findActionList(&newEsTable);
    return randomSelection(actionList);
}

int EstimateMethods::sGrandAscSelection(std::map<int, std::pair<double, double>>* esTable)
{
    double denominator = 0;
    for (auto iter=esTable->begin(); iter!=esTable->end(); iter++)
    {
        denominator += std::exp(iter->second.second);
    }
    /* std::cout << "denominator " << denominator << std::endl; */
    for (auto iter=esTable->begin(); iter!=esTable->end(); iter++)
    {
        //更新策略
        /* std::cout << "pssssll " << std::exp(iter->second.second) << std::endl; */
        iter->second.first = std::exp(iter->second.second) / denominator;
        /* std::cout << "pi " << iter->first << iter->second.first << std::endl; */
    }
    double selector=0;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<double> average(0, 1);
    double hit = average(eng);
    int choose=1;
    for (auto iter=esTable->begin(); iter!=esTable->end(); iter++)
    {
        selector += iter->second.first;
        if (selector >= hit)
        {
            choose = iter->first;
            break;
        }
    }   
    /* std::cout << "choose " << choose << std::endl; */
    return choose;
}
