#ifndef COMMON_FUNC
#define COMMON_FUNC

#include <math.h>
#include <random>

#include <map>

#include "rl_module/MyKey.h"

namespace cf
{
    //variables///////////////////
    //
    static std::random_device rd;
    static std::mt19937 gen(rd());
    //
    //////////////////////////////


    //function/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    /* 随机实数 */
    double randomRealNumber(double begin=-1, double end=1);

    /* 随机整数 */
    int randomIntNumber(int end);
    int randomIntNumber(int begin, int end);

    /* 依据给定概率触发 */
    bool randomTrigger(double probability);

    /* MyKey& maxArga(std::map<std::pair<MyKey, MyKey>, double> Q); */

    /* 将参数a修改为使函数值最大的参数值 */
    void maxArga(const std::map<std::pair<MyKey, MyKey>, double>& Q, const MyKey& state, const std::vector<MyKey>& actions, MyKey& action);

    /* 选择行动，函数提供给非绝对贪心策略 */
    const MyKey chooseAction(const std::map<std::pair<MyKey, MyKey>, double>& distribution, const MyKey& state, const std::vector<MyKey>& actions);
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
