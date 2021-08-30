#include <iostream>
#include "SimpleGnuplot.hpp"

#include <random>
#include <math.h>
#include <map>
#include <vector>

//全局便便
SimpleGnuplot plot;
std::random_device rd;
std::mt19937 gen(rd());

int state[21][21];
int stateValue[21][21];
int v[21][21];
int actionsList[11] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
int policy[21][21];

int lambdaRet[2] = {3, 2};
int lambdaReq[2] = {3, 4};

double factorialPlus(int lambda, int n)
{
    if (n == 0 || n == 1)
        return (double)lambda;
    return ((double)lambda / n) * factorialPlus(lambda, n-1);
}

double poisson(int n, int lambda)
{
    /* std::cout << "poisson " << "lambda=" << lambda << " n=" << n << " value=" <<(std::pow(lambda, n) / factorial(n)) * std::exp(-lambda); */
    return factorialPlus(lambda, n) * std::exp(-lambda); 
}

void generateData(int lambda,std::string name, bool isFirst=true)
{
    std::vector<std::pair<int, double>> data;
    for (int i=0; i<21; i++)
    {
        data.push_back(std::pair<int, double>(i, poisson(i, lambda)));

    }
    plot.sendPlotData(data, isFirst, name, std::to_string(lambda), "l");
}

//生成泊松分布搞定
int poissonRetReq(int lambda)
{
    //泊松分布
    std::poisson_distribution<int> p(3);
    /* std::cout << "poisson:" << p.mean() << ", " << p(gen) << std::endl; */
    std::cout << "泊松分布:\t" << "mean= " << p.mean() << ", max= " << p.max() << std::endl;
    return p(gen);
}

int randomSelection(int end, int begin=0)
{
    std::uniform_int_distribution<int> u(begin, end);
    return u(gen);
}

void initialize()
{
    /* for (int i=0; i<21; i++) */
    /*     for (int j=0; j<21; j++) */
    /*         policy[i][j] = actionsList[randomSelection(11)]; */
}

void copyArray()
{
    for (int i=0; i<21; i++)
        for (int j=0; j<21; j++)
            v[i][j] = stateValue[i][j];
}

bool isApproximation()
{
    for (int i=0; i<21; i++)
        for (int j=0; j<21; j++)
            if (std::fabs(v[i][j] - stateValue[i][j]) < 1e-3)
            {
                return false;
            }
    return true;
}

int getMin(int a, int b)
{
    if (a > b)
        return b;
    return a;
}

int getMax(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

std::tuple<int, int, int> getNextStateAndReward(int i, int j, int action)
{
    int iNext, jNext;
    int iRet = poissonRetReq(lambdaRet[0]), jRet = poissonRetReq(lambdaRet[1]);
    int iReq = poissonRetReq(lambdaReq[0]), jReq = poissonRetReq(lambdaReq[1]);
    int reward = 0;
    //更新奖励
    reward += 10 * getMin(i+iRet, iReq);
    reward += 10 * getMin(j+jRet, jReq);
    iNext = i+iRet - iReq < 0 ? 0 : i+iRet - iReq;
    jNext = j+jRet - jReq < 0 ? 0 : j+jRet - jReq;
    if (action > 0)
    {
        //感觉又要输了
        //还好有那个狗比的清心丸，不然整死了。小老板杀了我的猫~~！！！！
        //猫猫死了很难受,我原本可以保护它的，后悔~
        //重新扩一波房子
        reward -= 2 * getMin(iNext, action);
        iNext = iNext - action < 0 ? 0 : iNext - action;
        jNext += action;

    }
    else
    {
        //奖励为1&-1
        reward -= 2 * getMin(jNext, std::abs(action));
        jNext = jNext + action < 0 ? 0 : jNext + action;
        iNext -= action;
        reward++;
    }

    return std::tuple<int, int, int>(iNext, jNext, reward);
}

void printPolicy(int(* arr)[21])
{
    for (int i=0; i<78; i++)
        std::cout << '-';
    std::cout << std::endl;
    for (int i=0; i<21; i++)
    {
        for (int j=0; j<21; j++)
        {
            //遍历所有策略
            if (arr[i][j] < 0)
                std::cout <<arr[i][j] << " ";
            else
                std::cout << " " << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i=0; i<78; i++)
        std::cout << '-';
    std::cout << std::endl;
}

bool policyEvaluation()
{
    //稳定值
    bool stable = false;
    do 
    {
        //拷贝
        copyArray();
        for (int i=0; i<21; i++)
        {
            for (int j=0; j<21; j++)
            {
                //poisson reward
                //poisson reward
                auto nsr = getNextStateAndReward(i, j, policy[i][j]);
                stateValue[i][j] = std::get<2>(nsr) + 0.9 * stateValue[std::get<0>(nsr)][std::get<1>(nsr)];
            }
            if (isApproximation())
                stable = true;
        }
        /* printPolicy(); */

    } while(!stable);
    printPolicy(stateValue);
    return true;
}

//获取参数最大值
int argMaxa(int i, int j)
{
    int tmp;
    int action = actionsList[0];
    auto nsr = getNextStateAndReward(i, j, action);
    int maxa = std::get<2>(nsr);
    for (int i=1; i<11; i++)
    {
        nsr = getNextStateAndReward(i, j, actionsList[i]);
        tmp = std::get<2>(nsr);
        if (maxa < tmp)
        {
            maxa = tmp;
            action = actionsList[i];
        }
    }
    return action;
}

bool policyImprovement()
{
    //操作策略优化
    bool stable = true;
    //旧行动
    int oldAction;
    for (int i=0; i<21; i++)
    {
        for (int j=0; j<21; j++)
        {
            //策略
            oldAction = policy[i][j];
            policy[i][j] = argMaxa(i, j);
            //判断行动是否稳定
            if (policy[i][j] != oldAction)
                stable = false;
        }
    }
    //打印策略
    /* printPolicy(); */
    return stable;
}

void policyIteration()
{
    int cnt = 0;
    do
    {
        std::cout << "cnt: " << ++cnt << std::endl;
        policyEvaluation();
    } while (!policyImprovement());
}


int main(int argc, char** argv)
{
    std::cout << "jack's car rental start~" << std::endl;
    /* plot.setXLabel("'return & request number'"); */
    /* plot.setYLabel("'probability'"); */
    /* generateData(2, "'lambda=2'"); */
    /* generateData(3, "'lambda=3'",false); */
    /* generateData(4, "'lambda=4'", false); */
    /* plot.showFigure(); */

    /* for (int i=0; i<50; i++) */
    /*     std::cout << poissonRetReq(3) << std::endl; */
    /* for (int i=0; i<50; i++) */
    /*     std::cout << randomSelection(11) << std::endl; */
    initialize();
    /* printPolicy(policy); */
    /* printPolicy(stateValue); */

    policyIteration();

    printPolicy(policy);
    return 0;
}

