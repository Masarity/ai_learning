#include "learning_instance/moveToPoint/Point.h"
 
Point::Point(std::vector<MyKey>& states, std::map<MyKey, std::vector<MyKey>>& actions)
    :Agent(states, actions)
{
    /* m_log.classLog("Point constructored data saved in moveToPoint~"); */
    setName("moveToPoint");
    m_log.infoLog("default data fold: " + m_name);
    /* 调试代码 */
    {
        /* for (auto &Q : m_Q) */
        /* { */
        /*     std::cout << Q.second << std::endl; */
        /* } */
        /* std::cout << m_Q.size() << std::endl; */
        /* /1* for (auto &state : m_states) *1/ */
        /* /1* { *1/ */
        /* /1*     /2* p_targetPolicy->policy(state).printKey(); *2/ *1/ */
        /* /1* } *1/ */
        /* std::stringstream ss; */
        /* ss << "size of p_targetPolicy's distribution: " << p_targetPolicy->getDistributionSize() << "\n\t"; */ 
        /* ss << "size of p_targetPolicy's policy: " << p_targetPolicy->getPolicySize() << "\n\t"; */ 
        /* ss << "size of p_behaviorPolicy's distribution: " << p_behaviorPolicy->getDistributionSize() << "\n\t"; */ 
        /* ss << "size of p_targetPolicy's policy: " << p_behaviorPolicy->getPolicySize() << "\n\t"; */ 
        /* m_log.infoLog(ss.str()); */
    }
}
 
Point::~Point()
{
    /* m_log.classLog("Point deconstructored~"); */
}

void Point::loadData(std::string foldName) 
{
    if (foldName == "")
        foldName = m_name;

    loadActionValue(foldName);
    loadTargetPolicy(foldName);
    loadBehaviorPolicy(foldName);
}

void Point::loadActionValue(std::string foldName)
{
    std::ifstream ifs;
    ifs.open(getDataFilePath(foldName, "actionValue"), std::ios_base::in);

    if (!ifs.is_open())
        m_log.errorLog("failed to open: " + foldName + "/actionValue.txt" + "!");

    int n, m, a, b;
    double value;
    while (!ifs.eof())
    {
        ifs >> n >> m;
        /* std::cout << n << " " << m; */
        /* std::cout << std::endl; */
        ifs >> a >> b;
        /* std::cout << n << " " << m; */
        /* std::cout << std::endl; */
        ifs >> value;

        m_Q.find(std::make_pair(MyKey({n, m}), MyKey({a, b})))->second = value;
        /* std::cout << value << "\n"; */
    }

    /* 调试代码 */
    {
        /* for (auto &item : m_Q) */
        /* { */
        /*     std::cout << item.first.first.at(0) << " " << item.first.first.at(1) << std::endl; */
        /*     std::cout << item.first.second.at(0) << " " << item.first.second.at(1) << std::endl; */
        /*     std::cout << item.second << std::endl; */
        /* } */
    }
}
 
void Point::loadTargetPolicy(std::string foldName)
{
    std::ifstream ifs;
    ifs.open(getDataFilePath(foldName, "targetPolicy"), std::ios_base::in);

    if (!ifs.is_open())
        m_log.errorLog("failed to open: " + foldName + "/targetPolicy.txt" + "!");

    int n, m, a, b;
    while (!ifs.eof())
    {
        ifs >> n >> m;
        /* std::cout << n << " " << m; */
        /* std::cout << std::endl; */
        ifs >> a >> b;
        /* std::cout << n << " " << m; */
        /* std::cout << std::endl; */

        p_targetPolicy->modifyAction(MyKey({n, m}), MyKey({a, b}));
        /* std::cout << value << "\n"; */
    }

    /* 调试代码 */
    {
        /* for (auto &item : p_targetPolicy->getPolicy()) */
        /* { */
        /*     std::cout << item.first.at(0) << " " << item.first.at(1) << std::endl; */
        /*     std::cout << item.second.at(0) << " " << item.second.at(1) << std::endl; */
        /* } */
    }
}
 
void Point::loadBehaviorPolicy(std::string foldName)
{
    std::ifstream ifs;
    ifs.open(getDataFilePath(foldName, "behaviorPolicy"), std::ios_base::in);

    if (!ifs.is_open())
        m_log.errorLog("failed to open: " + foldName + "/behaviorPolicy.txt" + "!");

    int n, m, a, b;
    double value;
    while (!ifs.eof())
    {
        ifs >> n >> m;
        /* std::cout << n << " " << m; */
        /* std::cout << std::endl; */
        ifs >> a >> b;
        /* std::cout << n << " " << m; */
        /* std::cout << std::endl; */
        ifs >> value;

        p_behaviorPolicy->modifyDistribution(MyKey({n, m}), MyKey({a, b}), value);
        /* std::cout << value << "\n"; */
    }

    /* 调试代码 */
    {
        /* for (auto &item : p_behaviorPolicy->getDistribution()) */
        /* { */
        /*     std::cout << item.first.first.at(0) << " " << item.first.first.at(1) << std::endl; */
        /*     std::cout << item.first.second.at(0) << " " << item.first.second.at(1) << std::endl; */
        /*     std::cout << item.second << std::endl; */
        /* } */
    }
}

/* void Point::loadData() */
/* { */
/*     loadActionValue(); */
/*     loadTargetPolicy(); */
/*     loadBehaviorPolicy(); */
/* } */
 
/* void Point::saveData() */ 
/* { */
/*     saveActionValue(); */
/*     saveTargetPolicy(); */
/*     saveBehaviorPolicy(); */
/* } */
 
/* void Point::saveActionValue() */
/* { */
/*     std::ofstream ofs; */
/*     ofs.open("../res/training/data/moveToPoint/actionValue.txt", std::ios_base::out); */

/*     if (!ofs.is_open()) */
/*         m_log.errorLog("failed to open file!"); */

/*     auto endIter = m_Q.end(); */
/*     endIter--; */

/*     for (auto &items : m_Q) */
/*     { */
/*         for (int i=0; i<items.first.first.getSize(); i++) */
/*         { */
/*             if (i != items.first.first.getSize() - 1) */
/*                 ofs << items.first.first.at(i) << " "; */
/*             else */
/*                 ofs << items.first.first.at(i) << std::endl; */
/*         } */
/*         for (int i=0; i<items.first.second.getSize(); i++) */
/*         { */
/*             if (i != items.first.second.getSize() - 1) */
/*                 ofs << items.first.second.at(i) << " "; */
/*             else */
/*                 ofs << items.first.second.at(i) << std::endl; */
/*         } */
/*         if (items != *endIter) */
/*             ofs << items.second << std::endl; */
/*         else */
/*             ofs << items.second; */
/*     } */
/*     ofs.close(); */
/* } */
 
/* void Point::saveTargetPolicy() */
/* { */
/*     std::ofstream ofs; */
/*     ofs.open("../res/training/data/moveToPoint/targetPolicy.txt", std::ios_base::out); */

/*     if (!ofs.is_open()) */
/*         m_log.errorLog("failed to open file!"); */

/*     auto endIter = p_targetPolicy->getPolicy().end(); */
/*     endIter--; */

/*     for (auto &items : p_targetPolicy->getPolicy()) */
/*     { */
/*         for (int i=0; i<items.first.getSize(); i++) */
/*         { */
/*             if (i != items.first.getSize() - 1) */
/*                 ofs << items.first.at(i) << " "; */
/*             else */
/*                 ofs << items.first.at(i) << std::endl; */
/*         } */
/*         for (int i=0; i<items.second.getSize(); i++) */
/*         { */
/*             if (i != items.second.getSize() - 1) */
/*                 ofs << items.second.at(i) << " "; */
/*             else */
/*             { */
/*                 if (items != *endIter) */
/*                     ofs << items.second.at(i) << std::endl; */
/*                 else */
/*                     ofs << items.second.at(i); */
/*             } */
/*         } */
/*     } */
/*     ofs.close(); */
/* } */
 
/* void Point::saveBehaviorPolicy() */
/* { */
/*     std::ofstream ofs; */
/*     ofs.open("../res/training/data/moveToPoint/behaviorPolicy.txt", std::ios_base::out); */

/*     if (!ofs.is_open()) */
/*         m_log.errorLog("failed to open file!"); */

/*     auto endIter = p_behaviorPolicy->getDistribution().end(); */
/*     endIter--; */

/*     for (auto &items : p_behaviorPolicy->getDistribution()) */
/*     { */
/*         for (int i=0; i<items.first.first.getSize(); i++) */
/*         { */
/*             if (i != items.first.first.getSize() - 1) */
/*                 ofs << items.first.first.at(i) << " "; */
/*             else */
/*                 ofs << items.first.first.at(i) << std::endl; */
/*         } */
/*         for (int i=0; i<items.first.second.getSize(); i++) */
/*         { */
/*             if (i != items.first.second.getSize() - 1) */
/*                 ofs << items.first.second.at(i) << " "; */
/*             else */
/*                 ofs << items.first.second.at(i) << std::endl; */
/*         } */
/*         if (items != *endIter) */
/*             ofs << items.second << std::endl; */
/*         else */
/*             ofs << items.second; */
/*     } */
/*     ofs.close(); */
/* } */
