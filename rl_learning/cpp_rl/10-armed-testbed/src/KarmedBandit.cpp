#include "KarmedBandit.h"
#define forEachIter( container ) for (auto iter = container.begin(); iter != container.end(); iter++)

KarmedBandit::KarmedBandit(int k, int timeStep):_k(k),_timeStep(timeStep)
{
    std::cout << _k << "-" << "臂老虎机问题构造成功~" << "\n时间步为:\t" << _timeStep << std::endl;
    _estimateMethods = new EstimateMethods;
    _sPlot = new SimpleGnuplot;
    _averageRewards = new std::map<int, double>;
    _trueActionValue = new std::map<int, double>;
    _testTable = new std::map<int, std::pair<int, double>>;
    _gbaTable = new std::map<int, std::pair<double, double>>;
    resetAvgRewards();
    /* for (int i=1; i<=_timeStep; i++) */
    /* { */
    /*     //初始化奖励平均值 */
    /*     _averageRewards->insert(std::pair<int, double>(i, 0)); */
    /* } */
}

KarmedBandit::~KarmedBandit()
{
    if (_estimateMethods != nullptr)
    {
        delete _estimateMethods;
        _estimateMethods = nullptr;
    }
    if (_averageRewards != nullptr)
    {
        delete _averageRewards;
        _averageRewards = nullptr;
    }
    if (_trueActionValue != nullptr)
    {
        delete _trueActionValue;
        _trueActionValue = nullptr;
    }
    if (_testTable != nullptr)
    {
        delete _testTable;
        _testTable = nullptr;
    }
    if (_gbaTable != nullptr)
    {
        delete _gbaTable;
        _gbaTable = nullptr;
    }
    std::cout << _k << "-" << "臂老虎机问题析构成功~" << std::endl;
}

void KarmedBandit::initialize(double init)
{
    _trueActionValue->clear();
    _testTable->clear();
    _gbaTable->clear();
    for (int i=1; i<=_k; i++)
    {
        //真实奖励值正态分布
        if (_isStationary)
            _trueActionValue->insert(std::pair<int, double>(i, getRandom(0, 1)));
        else
            _trueActionValue->insert(std::pair<int, double>(i, 0));
        //初始化奖励估计值
        _testTable->insert(std::pair<int, std::pair<int, double>>(i, std::pair<int, double>(0, init)));
        //初始化随机逼近梯度下降的值
        _gbaTable->insert(std::pair<int, std::pair<double, double>>(i, std::pair<double, double>(1/_k, 0)));
    }
}

double KarmedBandit::getRandom(double miu, double sigma)
{
    std::normal_distribution<double> norm{miu, sigma};
    std::random_device rd;
    std::default_random_engine drg{rd()};
    /* std::cout << "miu=" << miu << " sigma=" << sigma << " 的高斯分布测试值：\t" << norm(drg) << ", " << norm(drg) << ", " << norm(drg) << std:: endl; */
    return norm(drg);
}

void KarmedBandit::returnAvgReward(bool isFirst, std::string name, std::string color, std::string with)
{
    std::vector<std::pair<int, double>> da;
    da.reserve(_timeStep + 1);
    std::cout << "avg: " << _averageRewards->at(1);
    da.emplace_back(1, _averageRewards->at(1));
    for (int i=2; i<=_timeStep; i++)
    {
        std::cout << " " << _averageRewards->at(i);
        da.emplace_back(i, _averageRewards->at(i));
    }
    std::cout << std::endl;
    _sPlot->sendPlotData(da, isFirst, name, color, with);
    resetAvgRewards();
}

void KarmedBandit::resetAvgRewards()
{
    _averageRewards->clear();
    for (int i=1; i<=_timeStep; i++)
    {
        //初始化奖励平均值
        _averageRewards->insert(std::pair<int, double>(i, 0));
    }
    //组数归零
    _group = 0;
}

void KarmedBandit::averageRewards(int timeStep, double Rnplus1)
{
    auto avgRewardIter = _averageRewards->find(timeStep);
    double Rn = avgRewardIter->second;
    avgRewardIter->second = (_group * Rn + Rnplus1) / (_group + 1);
}

int KarmedBandit::getGroup()
{
    return ++_group;
}

void KarmedBandit::start(bool isStationary, double init, int)
{
    _isStationary = isStationary;
    initialize(init);
    for (int timeStep=1; timeStep <= _timeStep; timeStep++)
    {
        //选择行动
        int action = _estimateMethods->greedySelection(_testTable);
        /* int action = _estimateMethods->greedySelection(_testTable); */
        /* std::cout << "select action:\t" << action << std::endl; */
        auto esPairIter = _testTable->find(action);
        auto trueValue = _trueActionValue->find(action);
        //获得对应奖励
        double reward = getRandom(trueValue->second, 1);
        //N++, Qa更新
        esPairIter->second.first++;
        esPairIter->second.second = _estimateMethods->sampleAverage(esPairIter->second.second, reward, esPairIter->second.first);
        //更新平均奖励
        averageRewards(timeStep, reward);
        /* std::cout << "at: " << timeStep << " get: " << reward << std::endl; */
        if (!_isStationary)
        {
            for (auto iter=_trueActionValue->begin(); iter!=_trueActionValue->end(); iter++)
            {
                iter->second += getRandom(0, 0.01);
            }
        }
    }
}

void KarmedBandit::start(bool isStationary, double init, double alpha, int)
{
    _isStationary = isStationary;
    initialize(init);
    for (int timeStep=1; timeStep <= _timeStep; timeStep++)
    {
        //选择行动
        int action = _estimateMethods->greedySelection(_testTable);
        /* int action = _estimateMethods->greedySelection(_testTable); */
        /* std::cout << "select action:\t" << action << std::endl; */
        auto esPairIter = _testTable->find(action);
        auto trueValue = _trueActionValue->find(action);
        //获得对应奖励
        double reward = getRandom(trueValue->second, 1);
        //N++, Qa更新
        esPairIter->second.first++;
        esPairIter->second.second = _estimateMethods->constantStepSize(esPairIter->second.second, reward, alpha);
        //更新平均奖励
        averageRewards(timeStep, reward);
        /* std::cout << "at: " << timeStep << " get: " << reward << std::endl; */
        if (!_isStationary)
        {
            for (auto iter=_trueActionValue->begin(); iter!=_trueActionValue->end(); iter++)
            {
                iter->second += getRandom(0, 0.01);
            }
        }
    }
}

void KarmedBandit::start(bool isStationary, double epsilon, double)
{
    _isStationary = isStationary;
    initialize(0);
    for (int timeStep=1; timeStep <= _timeStep; timeStep++)
    {
        //选择行动
        int action = _estimateMethods->epsilonGreedySelection(_testTable, epsilon);
        /* int action = _estimateMethods->greedySelection(_testTable); */
        /* std::cout << "select action:\t" << action << std::endl; */
        auto esPairIter = _testTable->find(action);
        auto trueValue = _trueActionValue->find(action);
        //获得对应奖励
        double reward = getRandom(trueValue->second, 1);
        //N++, Qa更新
        esPairIter->second.first++;
        esPairIter->second.second = _estimateMethods->sampleAverage(esPairIter->second.second, reward, esPairIter->second.first);
        //更新平均奖励
        averageRewards(timeStep, reward);
        /* std::cout << "at: " << timeStep << " get: " << reward << std::endl; */
        if (!_isStationary)
        {
            for (auto iter=_trueActionValue->begin(); iter!=_trueActionValue->end(); iter++)
            {
                iter->second += getRandom(0, 0.01);
            }
        }
    }
}

void KarmedBandit::start(bool isStationary, double epsilon, double alpha, double)
{
    _isStationary = isStationary;
    initialize(0);
    for (int timeStep=1; timeStep <= _timeStep; timeStep++)
    {
        //选择行动
        int action = _estimateMethods->epsilonGreedySelection(_testTable, epsilon);
        /* int action = _estimateMethods->greedySelection(_testTable); */
        /* std::cout << "select action:\t" << action << std::endl; */
        auto esPairIter = _testTable->find(action);
        auto trueValue = _trueActionValue->find(action);
        //获得对应奖励
        double reward = getRandom(trueValue->second, 1);
        //N++, Qa更新
        esPairIter->second.first++;
        esPairIter->second.second = _estimateMethods->constantStepSize(esPairIter->second.second, reward, alpha);
        //更新平均奖励
        averageRewards(timeStep, reward);
        /* std::cout << "at: " << timeStep << " get: " << reward << std::endl; */
        if (!_isStationary)
        {
            for (auto iter=_trueActionValue->begin(); iter!=_trueActionValue->end(); iter++)
            {
                iter->second += getRandom(0, 0.01);
            }
        }
    }
}

void KarmedBandit::start(bool isStationary, double confidence, std::string)
{
    _isStationary = isStationary;
    initialize(0);
    for (int timeStep=1; timeStep <= _timeStep; timeStep++)
    {
        //选择行动
        int action = _estimateMethods->ucbSelection(_testTable, confidence, timeStep);
        /* int action = _estimateMethods->greedySelection(_testTable); */
        /* std::cout << "select action:\t" << action << std::endl; */
        auto esPairIter = _testTable->find(action);
        auto trueValue = _trueActionValue->find(action);
        //获得对应奖励
        double reward = getRandom(trueValue->second, 1);
        //N++, Qa更新
        esPairIter->second.first++;
        esPairIter->second.second = _estimateMethods->sampleAverage(esPairIter->second.second, reward, esPairIter->second.first);
        //更新平均奖励
        averageRewards(timeStep, reward);
        /* std::cout << "at: " << timeStep << " get: " << reward << std::endl; */
        if (!_isStationary)
        {
            for (auto iter=_trueActionValue->begin(); iter!=_trueActionValue->end(); iter++)
            {
                iter->second += getRandom(0, 0.01);
            }
        }
    }
}

void KarmedBandit::start(bool isStationary, double alpha, bool, std::string)
{
    _isStationary = isStationary;
    initialize(0);
    for (int timeStep=1; timeStep <= _timeStep; timeStep++)
    {
        //选择行动
        int action = _estimateMethods->sGrandAscSelection(_gbaTable);
        /* int action = _estimateMethods->greedySelection(_testTable); */
        /* std::cout << "select action:\t" << action << std::endl; */
        /* auto esPairIter = _testTable->find(action); */
        auto trueValue = _trueActionValue->find(action);
        //获得对应奖励
        double reward = getRandom(trueValue->second, 1);
        //更新平均奖励
        averageRewards(timeStep, reward);
        //Ha更新
        /* _estimateMethods->numericalPreference(action, reward, _averageRewards->at(timeStep), alpha, _gbaTable); */
        _estimateMethods->numericalPreference(action, reward, 0, alpha, _gbaTable);
        /* std::cout << "at: " << timeStep << " get: " << reward << std::endl; */
        if (!_isStationary)
        {
            for (auto iter=_trueActionValue->begin(); iter!=_trueActionValue->end(); iter++)
            {
                iter->second += getRandom(0, 0.01);
            }
        }
    }
}
void KarmedBandit::showFigure()
{
    _sPlot->showFigure();
}
