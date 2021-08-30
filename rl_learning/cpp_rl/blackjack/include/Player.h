#pragma once

#include "Agent.h"


class Player
    :public Agent
{
public:
    Player();

    bool policy() override;

    void initVirables();

    //更新状态值
    void updateStateValue(std::vector<std::tuple<int, int, double>>& stateValues, std::vector<std::tuple<int, int, double>>& n, std::pair<int, int> episodeState, int reward);
    //更新行动值
    void updateActionValue(std::vector<std::tuple<int, int, bool, double>>& actionValues, std::vector<std::tuple<int, int, bool, double>>& nAction, std::tuple<int, int, bool> episodeActionState, int reward);
    //更新策略
    bool updatePolicy(std::vector<std::tuple<int, int, bool>>& policys, std::pair<int, int> state, std::vector<std::tuple<int, int, bool, double>>& actionValues);

    //进行策略评估
    void policyEvaluation(int reward, std::stack<std::tuple<int, int, bool>> episodeStates);
    void policyEvaluation(int reward, std::stack<std::tuple<int, int, bool, bool>> episodeActionStates);

    //进行策略优化
    bool policyImprovement(std::stack<std::tuple<int, int, bool, bool>> episodeActionStates);

    //调试用
    void printStateValues();
    void printActionValues();
    void printPolicy();

    //返回状态值函数
    const std::vector<std::tuple<int, int, double>>& getStateValues(bool usable=false);
    //返回行动值函数
    const std::vector<std::tuple<int, int, bool, double>>& getActionValues(bool usable=false);


    //将训练数据保存到文件中，下次再练
    void saveStateValues(std::string fileName, const std::vector<std::tuple<int, int, double>>& stateValues, std::vector<std::tuple<int, int, double>>& n);
    void saveActionValues(std::string fileName, const std::vector<std::tuple<int, int, bool, double>>& actionValues, std::vector<std::tuple<int, int, bool, double>>& n);
    void savePolicys(std::string fileName, const std::vector<std::tuple<int, int, bool>>& policys);
    bool saveData();
    //从文件中读取行动值函数，状态值函数，策略集
    bool loadStateValues(std::string fileName, std::vector<std::tuple<int, int, double>>& stateValues, std::vector<std::tuple<int, int, double>>& n);
    bool loadActionValues(std::string fileName, std::vector<std::tuple<int, int, bool, double>>& actionValues, std::vector<std::tuple<int, int, bool, double>>& n);
    bool loadPolicys(std::string fileName, std::vector<std::tuple<int, int, bool>>& policys);
    bool loadData();


private:
    //用来生成随机数
    std::random_device rd;

    //行动值
    std::vector<std::tuple<int, int, bool, double>> _actionValues;
    std::vector<std::tuple<int, int, bool, double>> _uActionValues;
    //记录行动值遇到的次数
    std::vector<std::tuple<int, int, bool, double>> _nAction;
    std::vector<std::tuple<int, int, bool, double>> _nActionUsable;
    std::tuple<int, int, bool, double> _actionValue;

    //状态值
    std::vector<std::tuple<int, int, double>> _stateValues;
    std::vector<std::tuple<int, int, double>> _uStateValues;
    //记录遇到状态的次数
    std::vector<std::tuple<int, int, double>> _n;
    std::vector<std::tuple<int, int, double>> _nUsable;
    std::tuple<int, int, double> stateValue;

    //初始化状态值
    void initStateValues();

    //初始化策略
    void initPolicy();
    //初始化行动值
    void initActionValues();


    //随机选择行动
    int randomSelection(int end, int begin=0);


};
