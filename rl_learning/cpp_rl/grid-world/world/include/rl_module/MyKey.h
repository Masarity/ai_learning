#pragma once

#include "debug_module/Log.h"
#include <vector>

class MyKey
{
public:
    explicit MyKey();
    explicit MyKey(std::initializer_list<int> describes);

    virtual ~MyKey();

    /* 调试用 */
    virtual void printKey() const;

    /* 获取行动大小 */
    int getSize() const;

    /* 取行动描述的值 */
    int at(int pos) const;

    /* 重载<可以做map的key */
    bool operator<(const MyKey& myKey) const;

    /* 重载==可以进行比较 */
    bool operator==(const MyKey& myKey) const;

private:
    /* 初始化变量 */
    void initVariables();

public:
    Log m_log;

protected:
    /* 保存储存key值的长度 */
    int m_size;
    std::vector<int> m_myKey;

};

