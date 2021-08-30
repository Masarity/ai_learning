#include "Environment.h"
#include "SimpleGnuplot.hpp"


/* //第一次创建的崭新的一副牌 */
/* std::vector<Card> newCardLibrary; */
/* //栈作为牌库 */
/* std::stack<Card> cardLibrary; */
/* //状态值 */
/* std::vector<std::tuple<int, int, double>> stateValues; */
/* std::vector<std::tuple<int, int, double>> svUsable; */
/* //记录遇到状态的次数 */
/* std::vector<std::tuple<int, int, double>> n; */
/* std::vector<std::tuple<int, int, double>> nUsable; */
/* std::stack<std::pair<int, int>> episodeStates; */

/* std::tuple<int, int, double> stateValue; */
/* double returns; */
/* //创建牌库 */
/* void createLibray(); */
/* //输出牌库测试 */
/* void printLibrary(); */
/* //初始化牌库 */
/* int randomSelection(int end, int begin = 0); */
/* void initLibrary(); */
/* void test1(); */
/* void test2(); */

/* void initStateValues(); */

/* void dealtCard(Agent& agent); */
/* void episode(); */

/* //叫牌 */
/* void hits(Agent& agent, bool isMasa = false); */
/* //返回奖励 */
/* int reward(); */
/* void averageReturns(int reward); */

/* //玩家&庄家 */
/* Player masa; */
/* Dealer monika; */

/* std::random_device rd; */
/* std::mt19937 gen(rd()); */



int main(int argc, char** argv)
{
    std::cout << "Blackjack game start~" << std::endl;
    Environment env;

    env.simulate();
    /* /1* test1(); *1/ */
    /* /1* test2(); *1/ */
    /* createLibray(); */
    /* initStateValues(); */
    
    /* for (int i=0; i<10000; i++) */
    /* { */
    /*     episode(); */
    /*     hits(masa, true); */
    /*     hits(monika); */
    /*     /1* test2(); *1/ */
    /*     averageReturns(reward()); */
    /* } */

    /* std::ofstream ofs; */
    /* ofs.open("./data.dat", std::ios_base::out); */

    /* int cnt = 1; */
    /* if (ofs.is_open()) */
    /* { */
    /*     std::cout << "file open" << std::endl; */
    /*     for (auto &iter : stateValues) */
    /*     { */
    /*         ofs << std::get<0>(iter) << " "; */ 
    /*         ofs << std::get<1>(iter) << " "; */ 
    /*         ofs << std::get<2>(iter) << " "; */ 
    /*         ofs << std::endl; */
    /*         if (cnt < 10) */
    /*             cnt++; */
    /*         else */
    /*         { */
    /*             ofs << std::endl; */
    /*             cnt = 1; */
    /*         } */
    /*     } */

    /* } */
    /* ofs.close(); */
    

    return 0;
}

/* void createLibray() */
/* { */
/*     //4张Ace、2、3、4、5、6、7、8、9牌 */
/*     for (int i=0; i<4; i++) */
/*     { */
/*         newCardLibrary.push_back(Card(11)); */
/*         newCardLibrary.push_back(Card(2)); */
/*         newCardLibrary.push_back(Card(3)); */
/*         newCardLibrary.push_back(Card(4)); */
/*         newCardLibrary.push_back(Card(5)); */
/*         newCardLibrary.push_back(Card(6)); */
/*         newCardLibrary.push_back(Card(7)); */
/*         newCardLibrary.push_back(Card(8)); */
/*         newCardLibrary.push_back(Card(9)); */
/*     } */

/*     //18张10 */
/*     for (int i=0; i<18; i++) */
/*     { */
/*         newCardLibrary.push_back(Card(10)); */
/*     } */
/* } */

/* void printLibrary() */
/* { */
/*     int cnt = 1; */

/*     while (!cardLibrary.empty()) */
/*     { */
/*         std::cout << cardLibrary.top().getValue() << "\t"; */
/*         cardLibrary.pop(); */
/*         if (cnt < 13) */
/*             cnt++; */
/*         else */
/*         { */
/*             cnt = 1; */
/*             std::cout << std::endl; */
/*         } */
        
/*     } */
/*     for (auto &iter : newCardLibrary) */
/*     { */
/*         std::cout << iter.getValue() << "\t"; */
/*         if (cnt < 13) */
/*             cnt++; */
/*         else */
/*         { */
/*             cnt = 1; */
/*             std::cout << std::endl; */
/*         } */
/*     } */
/* } */

/* int randomSelection(int end, int begin) */
/* { */
/*     std::uniform_int_distribution<int> u(begin, end); */
/*     return u(gen); */
/* } */

/* void initLibrary() */
/* { */
/*     /1* //打乱牌序 *1/ */
/*     /1* std::random_shuffle(newCardLibrary.begin(), newCardLibrary.end()); *1/ */

/*     //每次初始化将牌库清理一波 */
/*     std::stack<Card> emptyLibrary; */
/*     std::stack<std::pair<int, int>> emptyStates; */

/*     cardLibrary.swap(emptyLibrary); */
/*     episodeStates.swap(emptyStates); */

/*     for (int i=0; i<15; i++) */
/*     { */
/*         cardLibrary.push(newCardLibrary.at(randomSelection(53))); */
/*     } */
    
/*     /1* for (auto &iter : newCardLibrary) *1/ */
/*     /1* { *1/ */
/*     /1*     cardLibrary.push(iter); *1/ */
/*     /1* } *1/ */

/*     masa.clearCards(); */
/*     monika.clearCards(); */
/* } */

/* void test1() */
/* { */
/*     createLibray(); */
/*     /1* initLibrary(); *1/ */
/*     /1* printLibrary(); *1/ */

/*     for (int i=0; i<30; i++) */
/*     { */
/*         initLibrary(); */
/*         masa.getCard(cardLibrary.top()); */
/*         cardLibrary.pop(); */
/*         masa.getCard(cardLibrary.top()); */
/*         cardLibrary.pop(); */
/*         monika.getCard(cardLibrary.top()); */
/*         cardLibrary.pop(); */
/*         monika.getCard(cardLibrary.top()); */
/*         cardLibrary.pop(); */

/*         std::cout << "masa's card : " << masa.getPoints() << std::endl; */
/*         std::cout << "monika's card : " << monika.getPoints() << std::endl; */

/*     } */

/* } */

/* void test2() */
/* { */
/*     /1* Card Ace(11); *1/ */
/*     /1* monika.getCard(Ace); *1/ */
/*     /1* monika.getCard(Ace); *1/ */

/*     std::cout << "masa's card : " << masa.getPoints() << std::endl; */
/*     std::cout << "monika's card : " << monika.getPoints() << std::endl; */
/*     std::cout << "monika's show one card : " << monika.showOneCard() << std::endl; */

/* } */

/* void initStateValues() */
/* { */
/*     for (int i=1; i<11; i++) */
/*     { */
/*         for (int o=12; o<22; o++) */
/*         { */
/*             std::get<0>(stateValue) = i; */
/*             std::get<1>(stateValue) = o; */
/*             std::get<2>(stateValue) = 0; */
/*             stateValues.push_back(stateValue); */
/*             svUsable.push_back(stateValue); */
/*             n.push_back(stateValue); */
/*             nUsable.push_back(stateValue); */
/*         } */
/*     } */

/*     /1* for (auto &iter : n) *1/ */
/*     /1* { *1/ */
/*     /1*     std::cout << std::get<0>(iter) << " "; *1/ */ 
/*     /1*     std::cout << std::get<1>(iter) << " "; *1/ */ 
/*     /1*     std::cout << std::get<2>(iter) << " "; *1/ */ 
/*     /1*     std::cout << std::endl; *1/ */
/*     /1* } *1/ */

/* } */

/* void dealtCard(Agent& agent) */
/* { */
/*     agent.getCard(cardLibrary.top()); */
/*     cardLibrary.pop(); */
/* } */

/* void episode() */
/* { */
/*     initLibrary(); */
/*     for (int i=0; i<2; i++) */
/*     { */
/*         dealtCard(masa); */
/*         dealtCard(monika); */
/*     } */

/*     episodeStates.push(std::make_pair(monika.showOneCard() == 11? 1 : monika.showOneCard(), masa.getPoints())); */
/* } */

/* void hits(Agent& agent, bool isMasa) */
/* { */
/*     while (agent.policy()) */
/*     { */
/*         dealtCard(agent); */
/*         if (isMasa && masa.getPoints() < 22) */
/*             episodeStates.push(std::make_pair(monika.showOneCard() == 11? 1 : monika.showOneCard(), masa.getPoints())); */
/*     } */
/* } */

/* int reward() */
/* { */
/*     int r = 0; */
/*     if (masa.getPoints() > 21) */
/*         r = -1; */
/*     else */
/*     { */
/*         if (monika.getPoints() > 21 || masa.getPoints() > monika.getPoints()) */
/*             r = 1; */
/*         else if (masa.getPoints() < monika.getPoints()) */
/*             r = -1; */
/*     } */

/*     return r; */
/* } */

/* void averageReturns(int reward) */
/* { */
/*     while (!episodeStates.empty()) */
/*     { */
/*         auto episodeState = episodeStates.top(); */
/*         /1* std::cout << "eps: " << episodeState.first << " " << episodeState.second << std::endl; *1/ */
/*         auto iter = std::find_if(stateValues.begin(), stateValues.end(), [episodeState](std::tuple<int, int, double> state){ */
/*                                  return (std::get<0>(state) == episodeState.first) && (std::get<1>(state) == episodeState.second); */
/*                      }); */
/*         if (iter == stateValues.end()) */
/*             return; */
/*         if (!masa.findAce()) */
/*             return; */
/*         /1* std::cout << "find Ace" << std::endl; *1/ */
/*         auto num = std::find_if(n.begin(), n.end(), [episodeState](std::tuple<int, int, double> state){ */
/*                                  return (std::get<0>(state) == episodeState.first) && (std::get<1>(state) == episodeState.second); */
/*                      }); */
/*         std::get<2>(*num) += 1; */
/*         double oldValue = std::get<2>(*iter); */
/*         std::get<2>(*iter) = oldValue + (reward - oldValue) / std::get<2>(*num); */


/*         /1* std::cout << "reward = " << reward << std::endl; *1/ */
/*         /1* std::cout << std::get<0>(*iter) << " "; *1/ */ 
/*         /1* std::cout << std::get<1>(*iter) << " "; *1/ */ 
/*         /1* std::cout << std::get<2>(*iter) << " "; *1/ */ 
/*         /1* std::cout << std::get<2>(*num) << " "; *1/ */ 
/*         /1* std::cout << std::endl; *1/ */
/*         episodeStates.pop(); */
/*     } */
/* } */
