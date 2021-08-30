#include "Player.h"

Player::Player()
{
    /* std::cout << "Player constructor is called" << std::endl; */
}

bool Player::policy()
{
    if (getPoints() < 20)
    {
        return true;
    }
    return false;
}

void Player::initStateValues()
{
    for (int i=1; i<11; i++)
    {
        for (int o=12; o<22; o++)
        {
            std::get<0>(stateValue) = i;
            std::get<1>(stateValue) = o;
            std::get<2>(stateValue) = 0;
            _stateValues.push_back(stateValue);
            _uStateValues.push_back(stateValue);
            _n.push_back(stateValue);
            _nUsable.push_back(stateValue);
        }
    }


}

void Player::initPolicy()
{
    for (int i=1; i<11; i++)
    {
        for (int o=12; o<20; o++)
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
        for (int o=20; o<22; o++)
        {
            std::get<0>(_policy) = i;
            std::get<1>(_policy) = o;
            std::get<2>(_policy) = false;
            _policys.push_back(_policy);
            _uPolicys.push_back(_policy);
        }
    }
    //测试代码
    {
    /* std::cout << "----------No Usable Policy----------" << std::endl; */
    /* for (auto &iter : _policys) */
    /* { */
    /*     std::cout << std::get<0>(iter) << " "; */ 
    /*     std::cout << std::get<1>(iter) << " "; */ 
    /*     std::cout << std::get<2>(iter) << " "; */ 
    /*     std::cout << std::endl; */
    /* } */

    }

}

void Player::initActionValues()
{
    for (int i=1; i<11; i++)
    {
        for (int o=12; o<22; o++)
        {
            for (int p=0; p<2; p++)
            {
                std::get<0>(_actionValue) = i;
                std::get<1>(_actionValue) = o;
                std::get<2>(_actionValue) = static_cast<bool>(p);
                std::get<3>(_actionValue) = 0;
                _actionValues.push_back(_actionValue);
                _nAction.push_back(_actionValue);
                _uActionValues.push_back(_actionValue);
                _nActionUsable.push_back(_actionValue);
            }
        }
    }
    //测试代码
    {
        /* for (auto &iter : _actionValues) */
        /* { */
        /*     std::cout << std::get<0>(iter) << " "; */ 
        /*     std::cout << std::get<1>(iter) << " "; */ 
        /*     std::cout << std::get<2>(iter) << " "; */ 
        /*     std::cout << std::get<3>(iter) << " "; */ 
        /*     std::cout << std::endl; */
        /* } */
    }
}

void Player::initVirables()
{
    initStateValues();
    initPolicy();
    initActionValues();
}

void Player::updateStateValue(std::vector<std::tuple<int, int, double>>& stateValues, std::vector<std::tuple<int, int, double>>& n, std::pair<int, int> episodeState, int reward)
{
    /* std::cout << "eps: " << episodeState.first << " " << episodeState.second << std::endl; */
    auto iter = std::find_if(stateValues.begin(), stateValues.end(), [episodeState](std::tuple<int, int, double> state){
                             return (std::get<0>(state) == episodeState.first) && (std::get<1>(state) == episodeState.second);
                 });
    if (iter == stateValues.end())
        return;
    /* std::cout << "find Ace" << std::endl; */
    auto num = std::find_if(n.begin(), n.end(), [episodeState](std::tuple<int, int, double> state){
                             return (std::get<0>(state) == episodeState.first) && (std::get<1>(state) == episodeState.second);
                 });
    std::get<2>(*num) += 1;
    double oldValue = std::get<2>(*iter);
    std::get<2>(*iter) = oldValue + (reward - oldValue) / std::get<2>(*num);

}

void Player::updateActionValue(std::vector<std::tuple<int, int, bool, double>>& actionValues, std::vector<std::tuple<int, int, bool, double>>& nAction, std::tuple<int, int, bool> episodeActionState, int reward)
{
    auto iter = std::find_if(actionValues.begin(), actionValues.end(), [episodeActionState](std::tuple<int, int, bool, double> state){
                             return (std::get<0>(state) == std::get<0>(episodeActionState)) && (std::get<1>(state) == std::get<1>(episodeActionState) && (std::get<2>(state) == std::get<2>(episodeActionState)));
                 });
    if (iter == actionValues.end())
        return;
    /* std::cout << "find Ace" << std::endl; */
    auto num = std::find_if(nAction.begin(), nAction.end(), [episodeActionState](std::tuple<int, int, bool, double> state){
                             return (std::get<0>(state) == std::get<0>(episodeActionState)) && (std::get<1>(state) == std::get<1>(episodeActionState) && (std::get<2>(state) == std::get<2>(episodeActionState)));
                 });
    std::get<3>(*num) += 1;
    double oldValue = std::get<3>(*iter);
    std::get<3>(*iter) = oldValue + (reward - oldValue) / std::get<3>(*num);
}

int Player::randomSelection(int end, int begin)
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> u(begin, end);
    return u(gen);
}

bool Player::updatePolicy(std::vector<std::tuple<int, int, bool>>& policys, std::pair<int, int> state, std::vector<std::tuple<int, int, bool, double>>& actionValues)
{
    auto policy = std::find_if(policys.begin(), policys.end(), [state](std::tuple<int, int, bool>& p)
                               {
                               return (state.first == std::get<0>(p) && state.second == std::get<1>(p));
                               });
    auto actionValue0 = std::find_if(actionValues.begin(), actionValues.end(), [state](std::tuple<int, int, bool, double>& p)
                               {
                               return (state.first == std::get<0>(p) && state.second == std::get<1>(p) && !std::get<2>(p));
                               });
    auto actionValue1 = std::find_if(actionValues.begin(), actionValues.end(), [state](std::tuple<int, int, bool, double>& p)
                               {
                               return (state.first == std::get<0>(p) && state.second == std::get<1>(p) && std::get<2>(p));
                               });
    bool oldAcion = std::get<2>(*policy);
    if (std::get<3>(*actionValue0) > std::get<3>(*actionValue1))
        std::get<2>(*policy) = false;
    else if (std::get<3>(*actionValue0) == std::get<3>(*actionValue1))
        std::get<2>(*policy) = static_cast<bool>(randomSelection(1));
    else 
        std::get<2>(*policy) = true;

    return oldAcion == std::get<2>(*policy);

}

void Player::policyEvaluation(int reward, std::stack<std::tuple<int, int, bool>> episodeStates)
{
    //遍历片段状态栈里全部的状态
    while (!episodeStates.empty())
    {
        auto episodeState = episodeStates.top();
        //true表示Ace使用值为11，即usable
        if (std::get<2>(episodeState))
        {
            updateStateValue(_uStateValues, _nUsable,
                             std::make_pair(
                                std::get<0>(episodeState),
                                std::get<1>(episodeState)
                                ), reward);
        }
        else
        {
            updateStateValue(_stateValues, _n,
                             std::make_pair(
                                std::get<0>(episodeState),
                                std::get<1>(episodeState)
                                ), reward);
        }
        episodeStates.pop();
    }
}

void Player::policyEvaluation(int reward, std::stack<std::tuple<int, int, bool, bool>> episodeActionStates)
{
    //遍历片段状态栈里全部的状态
    while (!episodeActionStates.empty())
    {
        auto episodeState = episodeActionStates.top();
        //true表示Ace使用值为11，即usable
        if (std::get<3>(episodeState))
        {
            updateActionValue(_uActionValues, _nActionUsable,
                             std::make_tuple(
                                std::get<0>(episodeActionStates.top()),
                                std::get<1>(episodeActionStates.top()),
                                std::get<2>(episodeActionStates.top())
                                ), reward);
        }
        else
        {
            updateActionValue(_actionValues, _nAction,
                             std::make_tuple(
                                std::get<0>(episodeActionStates.top()),
                                std::get<1>(episodeActionStates.top()),
                                std::get<2>(episodeActionStates.top())
                                ), reward);
        }
        episodeActionStates.pop();
    }
}

bool Player::policyImprovement(std::stack<std::tuple<int, int, bool, bool>> episodeActionStates)
{
    bool stable = true;
    //遍历片段状态栈里全部的状态
    while (!episodeActionStates.empty())
    {
        auto episodeState = episodeActionStates.top();
        //true表示Ace使用值为11，即usable
        if (std::get<3>(episodeState))
        {
            if (!updatePolicy(_uPolicys, 
                              std::make_pair(std::get<0>(episodeActionStates.top()),
                                             std::get<1>(episodeActionStates.top())),
                              _uActionValues))
                stable = false;
        }
        else
        {
            if (!updatePolicy(_policys,
                              std::make_pair(std::get<0>(episodeActionStates.top()),
                                             std::get<1>(episodeActionStates.top())),
                              _actionValues))
                stable = false;
        }
        episodeActionStates.pop();
    }
    /* for (int i=1; i<11; i++) */
    /* { */
    /*     for (int o=12; o<22; o++) */
    /*     { */
    /*     } */
    /* } */
    return stable;
}

void Player::printPolicy()
{
    std::cout << "----------Usable----------" << std::endl;
    for (auto &iter : _uPolicys)
    {
        std::cout << std::get<0>(iter) << " "; 
        std::cout << std::get<1>(iter) << " "; 
        std::cout << std::get<2>(iter) << " "; 
        std::cout << std::endl;
    }
    std::cout << "----------Usable----------" << std::endl;
    std::cout << "----------No Usable----------" << std::endl;
    for (auto &iter : _policys)
    {
        std::cout << std::get<0>(iter) << " "; 
        std::cout << std::get<1>(iter) << " "; 
        std::cout << std::get<2>(iter) << " "; 
        std::cout << std::endl;
    }
    std::cout << "----------No Usable----------" << std::endl;

}

void Player::printStateValues()
{
    std::cout << "----------Usable----------" << std::endl;
    for (auto &iter : _uStateValues)
    {
        std::cout << std::get<0>(iter) << " "; 
        std::cout << std::get<1>(iter) << " "; 
        std::cout << std::get<2>(iter) << " "; 
        std::cout << std::endl;
    }
    std::cout << "----------Usable----------" << std::endl;
    std::cout << "----------No Usable----------" << std::endl;
    for (auto &iter : _stateValues)
    {
        std::cout << std::get<0>(iter) << " "; 
        std::cout << std::get<1>(iter) << " "; 
        std::cout << std::get<2>(iter) << " "; 
        std::cout << std::endl;
    }
    std::cout << "----------No Usable----------" << std::endl;
}

void Player::printActionValues()
{
    std::cout << "----------Usable----------" << std::endl;
    for (auto &iter : _uActionValues)
    {
        std::cout << std::get<0>(iter) << " "; 
        std::cout << std::get<1>(iter) << " "; 
        std::cout << std::get<2>(iter) << " "; 
        std::cout << std::get<3>(iter) << " "; 
        std::cout << std::endl;
    }
    std::cout << "----------Usable----------" << std::endl;
    std::cout << "----------No Usable----------" << std::endl;
    for (auto &iter : _actionValues)
    {
        std::cout << std::get<0>(iter) << " "; 
        std::cout << std::get<1>(iter) << " "; 
        std::cout << std::get<2>(iter) << " "; 
        std::cout << std::get<3>(iter) << " "; 
        std::cout << std::endl;
    }
    std::cout << "----------No Usable----------" << std::endl;
}

const std::vector<std::tuple<int, int, double>>& Player::getStateValues(bool usable)
{
    if (usable)
        return _uStateValues;
    return _stateValues;
}

const std::vector<std::tuple<int, int, bool, double>>& Player::getActionValues(bool usable)
{
    if (usable)
        return _uActionValues;
    return _actionValues;
}

void Player::saveStateValues(std::string fileName, const std::vector<std::tuple<int, int, double>>& stateValues, std::vector<std::tuple<int, int, double>>& n)
{
    std::ofstream ofs;
    std::stringstream ss;

    ss << "../trainData/stateValue/";
    ss << fileName;

    ofs.open(ss.str(), std::ios_base::out);

    if (ofs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        for (auto &iter : stateValues)
        {
            ofs << std::get<0>(iter) << " "; 
            ofs << std::get<1>(iter) << " "; 
            ofs << std::get<2>(iter) << " "; 
            auto state = std::make_tuple(std::get<0>(iter), std::get<1>(iter));
            auto N = std::find_if(n.begin(), n.end(), [state](std::tuple<int, int, double>& num)
                                  {
                                  return (std::get<0>(state) == std::get<0>(num) && std::get<1>(state) == std::get<1>(num));
                                  });
            ofs << std::get<2>(*N);
            if (!(std::get<0>(iter) == 10 && std::get<1>(iter) == 21))
                ofs << std::endl;
            else
                break;
        }
    }
    ofs.close();
}

void Player::saveActionValues(std::string fileName, const std::vector<std::tuple<int, int, bool, double>>& actionValues, std::vector<std::tuple<int, int, bool, double>>& n)
{
    std::ofstream ofs;
    std::stringstream ss;

    ss << "../trainData/actionValue/";
    ss << fileName;

    ofs.open(ss.str(), std::ios_base::out);

    if (ofs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        for (auto &iter : actionValues)
        {
            ofs << std::get<0>(iter) << " "; 
            ofs << std::get<1>(iter) << " "; 
            ofs << std::get<2>(iter) << " "; 
            ofs << std::get<3>(iter) << " "; 
            auto actionState = std::make_tuple(std::get<0>(iter), std::get<1>(iter), std::get<2>(iter));
            auto N = std::find_if(n.begin(), n.end(), [actionState](std::tuple<int, int, bool, double>& num)
                                  {
                                  return (std::get<0>(actionState) == std::get<0>(num) && std::get<1>(actionState) == std::get<1>(num) && std::get<2>(actionState) == std::get<2>(num));
                                  });
            ofs << std::get<3>(*N);
            if (!(std::get<0>(iter) == 10 && std::get<1>(iter) == 21 && std::get<2>(iter) == 1))
                ofs << std::endl;
            else
                break;
        }
    }
    ofs.close();
}

void Player::savePolicys(std::string fileName, const std::vector<std::tuple<int, int,bool>>& policys)
{
    std::ofstream ofs;
    std::stringstream ss;

    ss << "../trainData/policy/";
    ss << fileName;

    ofs.open(ss.str(), std::ios_base::out);

    if (ofs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        for (auto &iter : policys)
        {
            ofs << std::get<0>(iter) << " "; 
            ofs << std::get<1>(iter) << " "; 
            ofs << std::get<2>(iter) << " "; 
            if (!(std::get<0>(iter) == 10 && std::get<1>(iter) == 21))
                ofs << std::endl;
            else
                break;
        }
    }
    ofs.close();
}

bool Player::saveData()
{
    //To do::保存数据
    saveStateValues("stateValues_with_no_usable_Ace", _stateValues, _n);
    saveStateValues("stateValues_with_usable_Ace", _uStateValues, _nUsable);
    
    saveActionValues("actionValues_with_no_usable_Ace", _actionValues, _nAction);
    saveActionValues("actionValues_with_usable_Ace", _uActionValues, _nActionUsable);

    savePolicys("policy_with_no_usable_Ace", _policys);
    savePolicys("policy_with_usable_Ace", _uPolicys);
    
    return true;
}

bool Player::loadStateValues(std::string fileName, std::vector<std::tuple<int, int, double>>& stateValues, std::vector<std::tuple<int, int, double>>& n)
{
    std::ifstream ifs;

    std::stringstream ss;

    ss << "../trainData/stateValue/";
    ss << fileName;

    ifs.open(ss.str(), std::ios_base::in);

    if (ifs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        std::tuple<int, int, double> stateValue;
        while (!ifs.eof())
        {
            ifs >> std::get<0>(stateValue); 
            ifs >> std::get<1>(stateValue); 
            ifs >> std::get<2>(stateValue); 
            stateValues.push_back(stateValue);
            ifs >> std::get<2>(stateValue); 
            n.push_back(stateValue);
        }
        /* stateValues.pop_back(); */
        /* n.pop_back(); */
        ifs.close();
        return true;
    }
    ifs.close();
    return false;
}

bool Player::loadActionValues(std::string fileName, std::vector<std::tuple<int, int, bool, double>>& actionValues, std::vector<std::tuple<int, int, bool, double>>& n)
{
    std::ifstream ifs;

    std::stringstream ss;

    ss << "../trainData/actionValue/";
    ss << fileName;

    ifs.open(ss.str(), std::ios_base::in);

    if (ifs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        std::tuple<int, int, bool, double> actionValue;
        while (!ifs.eof())
        {
            ifs >> std::get<0>(actionValue); 
            ifs >> std::get<1>(actionValue); 
            ifs >> std::get<2>(actionValue); 
            ifs >> std::get<3>(actionValue); 
            actionValues.push_back(actionValue);
            ifs >> std::get<3>(actionValue); 
            n.push_back(actionValue);
        }
        /* actionValues.pop_back(); */
        /* n.pop_back(); */
        ifs.close();
        return true;
    }

    ifs.close();
    return false;
}

bool Player::loadPolicys(std::string fileName, std::vector<std::tuple<int, int, bool>>& policys)
{
    std::ifstream ifs;

    std::stringstream ss;

    ss << "../trainData/policy/";
    ss << fileName;

    ifs.open(ss.str(), std::ios_base::in);

    if (ifs.is_open())
    {
        std::cout << ss.str() << " is opened" << std::endl;
        std::tuple<int, int, bool> policy;
        while (!ifs.eof())
        {
            ifs >> std::get<0>(policy); 
            ifs >> std::get<1>(policy); 
            ifs >> std::get<2>(policy); 
            policys.push_back(policy);
        }
        /* policys.pop_back(); */
        /* ifs.close(); */
        return true;
    }
    ifs.close();
    return false;
}

bool Player::loadData()
{
    //to do::载入训练数据
    bool loadSuccess = true;
    if (!loadStateValues("stateValues_with_no_usable_Ace", _stateValues, _n))
        loadSuccess = false;
    if (!loadStateValues("stateValues_with_usable_Ace", _uStateValues, _nUsable))
        loadSuccess = false;
    
    if (!loadActionValues("actionValues_with_no_usable_Ace", _actionValues, _nAction))
        loadSuccess = false;
    if (!loadActionValues("actionValues_with_usable_Ace", _uActionValues, _nActionUsable))
        loadSuccess = false;

    if (!loadPolicys("policy_with_no_usable_Ace", _policys))
        loadSuccess = false;
    if (!loadPolicys("policy_with_usable_Ace", _uPolicys))
        loadSuccess = false;

    return true;
}
