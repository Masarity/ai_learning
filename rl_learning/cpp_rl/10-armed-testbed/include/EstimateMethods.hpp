#pragma once
#include <iostream>
#include <limits.h>
#include <cmath>
#include <map>
#include <vector>
#include <random>
#include <algorithm>

class EstimateMethods
{
public:
    EstimateMethods();
    ~EstimateMethods();
    //用模板写~
    template <typename RT>
        double sampleAverage(double Qa, RT reward, int N);

    template <typename RT>
        double constantStepSize(double Qa, RT reward, double alpha);
    
    template <typename RT>
        void numericalPreference(int action, RT reward, double baseline, double alpha, std::map<int, std::pair<double, double>>* esTable);

    //随机选择
    int randomSelection(std::vector<int>& table);
    //随机触发
    bool randomTrigger(double probability);
    //寻找合适的行动列表
    std::vector<int> findActionList(const std::map<int, std::pair<int, double>>* table);
    /* int selectMethod(int method); */
    /* int selectMethod(int method, double epsilon); */
    //贪心选择法
    int greedySelection(const std::map<int, std::pair<int, double>>* esTable);
    //epsilon-贪心选择法
    int epsilonGreedySelection(const std::map<int, std::pair<int, double>>* esTable, double epsilon);
    //置信上界选择法UCB
    int ucbSelection(const std::map<int, std::pair<int, double>>* esTable, double confidence, int t);
    //随机逼近梯度梯度下降
    int sGrandAscSelection(std::map<int, std::pair<double, double>>* esTable);
private:

};

//样本平均估计法
template <typename RT>
    double EstimateMethods::sampleAverage(double Qa, RT reward, int N)
    {
        /* std::cout << "sampleAverage: " << Qa + (1/(double)N) * (reward - Qa) << std::endl; */
        return Qa + (1/(double)N) * (reward - Qa); 
    }

//常量步长估计法
template <typename RT>
    double EstimateMethods::constantStepSize(double Qa, RT reward, double alpha)
    {
        return Qa + (alpha) * (reward - Qa); 
    }

template <typename RT>
    void EstimateMethods::numericalPreference(int action, RT reward, double baseline, double alpha, std::map<int, std::pair<double, double>>* esTable)
    {
        for (auto iter=esTable->begin(); iter!=esTable->end(); iter++)
        {
            iter->second.second += alpha * (reward - baseline) * ((action == iter->first ? 1 : 0) - iter->second.first);
            /* std::cout << "Ha " << iter->second.second << std::endl; */
        }
    }
