#include "debug_module/test.h"
 
 
void ts::testLog()
{
    ts::debugLog.infoLog("test module load~");
    /* std::map<std::pair<MyKey, MyKey>, double> q; */
    /* std::vector<MyKey> as; */
    /* MyKey a({1}), s({1}); */
    /* cf::maxArga(q, s, as, a); */
}

void ts::testState()
{
    std::stringstream ss;
    int a =10, b=20, c=30;
    State testState({a, b, c});
    testState.printKey();

    State large({10, 10, 10});

    ss << "large is bigger: " << (large < testState ? "false" : "true") << "\n\t";

    std::map<State, int> states;

    states[testState] = 1;
    states[large] = 2;

    ss << "states.at(large): " << states.at(large) << "\n\t";
    ss << "states.at(testState): " << states.at(testState) << "\n\t";
    ts::debugLog.infoLog(ss.str());
}
 
void ts::testAction()
{
    std::stringstream ss;
    int a =0, b=0, c=1;
    Action testAction({a, b, c});
    testAction.printKey();
    
    ss << "action = move UP with ACCEL: " << (testAction == Action({Action::UP, Action::ACCEL}) ? "true" : "false") << "\n\t";

    ss << "action < move UP with ACCEL: " << (testAction < Action({Action::UP, Action::ACCEL}) ? "true" : "false") << "\n\t";
    ts::debugLog.infoLog(ss.str());

}
 
void ts::testMyKey()
{
    std::stringstream ss;
    int a =10, b=20, c=30;
    MyKey testMyKey({a, b, c});
    testMyKey.printKey();

    MyKey large({10, 10, 10});

    ss << "large is bigger: " << (large < testMyKey ? "false" : "true") << "\n\t";

    std::map<MyKey, int> MyKeys;

    MyKeys[testMyKey] = 1;
    MyKeys[large] = 2;

    ss << "MyKeys.at(large): " << MyKeys.at(large) << "\n\t";
    ss << "MyKeys.at(testMyKey): " << MyKeys.at(testMyKey) << "\n\t";

    /* MyKey keke({large, testMyKey}); */
    auto keke = std::make_pair(large, testMyKey);

    std::map<std::pair<MyKey, MyKey>, int> kekes;

    kekes[keke] = 3;

    ss << "large == testMyKey: " << (large == MyKey({10, 10, 10})? "true" : "false") << "\n\t";

    ss << "kekes.at(keke): " << kekes.find(keke)->second;

    ts::debugLog.infoLog(ss.str());
}
 
void ts::testPolicy()
{
    std::stringstream ss;
    Policy testPolicy;

    State state1({1, 2});
    Action action1({Action::UP, Action::ACCEL});

    testPolicy.insertPolicy(action1, state1, 1);

    ss << "policy(1,2)'s probabilty: " << testPolicy.policy(action1, state1);
    ts::debugLog.infoLog(ss.str());
    testPolicy.policy(state1).printKey();

    testPolicy.eraseDistribution(action1, state1);

    testPolicy.policy(action1, state1);
    /* testPolicy.clearPolicy(); */
}
 
void ts::testCF()
{
    ts::testChooseAction();
    /* ts::testArgMaxa(); */
}
 
void ts::testArgMaxa()
{
    std::stringstream ss;
    Policy testPolicy;

    std::map<std::pair<MyKey, MyKey>, double> Q;

    State state1({1, 1});

    Action action1({Action::UP, Action::ACCEL});
    Action action2({Action::DOWN, Action::ACCEL});
    Action action3({Action::LEFT, Action::ACCEL});
    Action action4({Action::RIGHT, Action::ACCEL});


    Q.insert(std::make_pair(std::make_pair(state1, action1), 1));
    Q.insert(std::make_pair(std::make_pair(state1, action2), 5));
    Q.insert(std::make_pair(std::make_pair(state1, action3), 7));
    Q.insert(std::make_pair(std::make_pair(state1, action4), 9));

    std::vector<MyKey> actions;
    actions.push_back(action1);
    actions.push_back(action2);
    actions.push_back(action3);
    actions.push_back(action4);

    MyKey action = action1;
    cf::maxArga(Q, state1, actions, action);

    action.printKey();

    /* ts::debugLog.infoLog(ss.str()); */
}
 
void ts::testChooseAction()
{
    std::stringstream ss;
    Policy testPolicy;

    State state1({1, 1});
    Action action1({Action::UP, Action::ACCEL});
    Action action2({Action::DOWN, Action::ACCEL});
    Action action3({Action::LEFT, Action::ACCEL});
    Action action4({Action::RIGHT, Action::ACCEL});

    testPolicy.insertPolicy(action1, state1, 0.925);
    testPolicy.insertPolicy(action2, state1, 0.025);
    testPolicy.insertPolicy(action3, state1, 0.025);
    testPolicy.insertPolicy(action4, state1, 0.025);
    /* testPolicy.insertPolicy(action2, state1, 0.4); */
    /* testPolicy.insertPolicy(action3, state1, 0.1); */

    ss << "policy(0,1)'s probabilty: " << testPolicy.policy(action1, state1) << "\n\t";
    ss << "policy(1,1)'s probabilty: " << testPolicy.policy(action2, state1) << "\n\t";
    ss << "policy(2,1)'s probabilty: " << testPolicy.policy(action3, state1) << "\n\t";
    ss << "policy(3,1)'s probabilty: " << testPolicy.policy(action4, state1) << "\n\t";
    ts::debugLog.infoLog(ss.str());

    std::vector<MyKey> actions;
    actions.push_back(action1);
    actions.push_back(action2);
    actions.push_back(action3);
    actions.push_back(action4);

    int cnt0=0, cnt1=0, cnt2=0, cnt3=0;
    for (int i=0; i<10000; i++)
    {
        MyKey action = cf::chooseAction(testPolicy.getDistribution(), state1, actions);
        /* action.printKey(); */
        if (action == action1)
            cnt0++;
        else if (action == action2)
            cnt1++;
        else if (action == action3)
            cnt2++;
        else 
            cnt3++;
    }
    ss.clear();
    ss.str("");
    ss << "cnt0: " << cnt0 << " cnt1: " << cnt1 << " cnt2: " << cnt2 << " cnt3: " << cnt3;

    ts::debugLog.infoLog(ss.str());
}
 
void ts::testEnv()
{
    int times = 100000;
    PointMoveEnv testEnv;
    ts::debugLog.inputLog("训练片段任务次数");

    std::cin >> times;
    testEnv.episodesLoop(times);
}
 
void ts::testPloy()
{
    std::vector<MyKey*> m_states;

    /* std::map<MyKey*, std::vector<MyKey*>> m_actions; */
    /* std::vector<MyKey*> actions; */
    /* actions.push_back(new Action({2, -1})); */
    /* m_actions.insert(std::make_pair(new State({1}), actions)); */
    Action* action = new Action({3, 1});

    m_states.push_back(action);


    const MyKey& jinlun = *m_states.at(0);

    jinlun.printKey();

    /* delete action; */

    delete m_states.at(0);
}
 
void ts::testNew()
{
    ::system("mkdir -p ../res/training/data/testDir");
}
