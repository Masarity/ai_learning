#pragma once
#include <iostream>
#include <random>
#include <map>
#include <vector>
#include "EstimateMethods.hpp"
#include "SimpleGnuplot.hpp"

class KarmedBandit
{
public:
    KarmedBandit(int k, int timeStep);
    ~KarmedBandit();
    //初始化，可以重载
    void initialize(double init);
    //高斯分布随机值
    double getRandom(double miu, double sigma);
    //返回奖励
    double getReward(int action);
    //计算平均奖励
    void averageRewards(int timeStep, double reward);
    void resetAvgRewards();
    void returnAvgReward(bool isFirst, std::string name, std::string color="3", std::string with="l");
    //返回组数（自增）
    int getGroup();
    //估计方法做成类
    void start(bool isStationary, double init, int);
    void start(bool isStationary, double init, double alpha, int);
    void start(bool isStationary, double epsilon, double);
    void start(bool isStationary, double epsilon, double alpha, double);
    void start(bool isStationary, double confidence, std::string);
    void start(bool isStationary, double alpha, bool, std::string);
    //显示图像
    void showFigure();


private:
    //臂数
    int _k;
    //时间步
    int _timeStep;
    //组数
    int _group;
    //真实奖励期望
    std::map<int, double>* _trueActionValue;
    bool _isStationary = true;
    //递推表<a, pair<N(a), Q(a)>>
    std::map<int, std::pair<int, double>>* _testTable;
    //随机逼近梯度下降表
    std::map<int, std::pair<double, double>>* _gbaTable;
    //平均奖励
    std::map<int, double>* _averageRewards;
    //估计方法对象，开辟在堆区
    EstimateMethods* _estimateMethods;
    /* int method = 0; */
    //画图对象，开辟堆区
    SimpleGnuplot* _sPlot;
};

