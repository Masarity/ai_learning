#pragma once

#include "rl_module/commonFunc.h"
#include "learning_instance/moveToPoint/State.h"
#include "learning_instance/moveToPoint/Action.h"
#include "learning_instance/moveToPoint/PointMoveEnv.h"
#include "rl_module/Policy.h"

#include <map>

#include <sys/stat.h>

namespace ts
{
//Variables
//
    static Log debugLog;

//Functions
//
    /* 测试调试输出 */
    void testLog();
    /* 测试状态类 */
    void testState();
    /* 测试行动类 */
    void testAction();
    /* 测试整合key值类 */
    void testMyKey();
    /* 测试Policy类 */
    void testPolicy();

    /* 测试commonfunction */
    void testCF();
    void testArgMaxa();
    void testChooseAction();

    /* 测试环境类 */
    void testEnv();

    void testPloy();

    void testNew();
}

