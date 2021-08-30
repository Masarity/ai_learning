#include "rl_module/MyKey.h"

MyKey::MyKey()
{
    initVariables();
    /* m_myKey.push_back(0); */
    /* m_size++; */
}

MyKey::MyKey(std::initializer_list<int> describes)
{
    initVariables();
    for (auto &iter : describes)
    {
        m_myKey.push_back(iter);
        m_size++;
    }
}
 
MyKey::~MyKey()
{
}
 
void MyKey::printKey() const
{
    std::stringstream ss;
    ss << "size: " << m_size << std::endl << "\t" << "myKey: ";
    for (auto &iter : m_myKey)
    {
        ss << iter << " "; 
    }
    m_log.infoLog(ss.str());
}
 
int MyKey::getSize() const
{
    return m_size;
}
 
int MyKey::at(int pos) const
{
    return m_myKey.at(pos);
}
 
bool MyKey::operator<(const MyKey& myKey) const
{
    int size = myKey.getSize();
    if (size != m_size)
    {
        m_log.warningLog("compare with different size!");
        if (size > m_size)
            size = m_size;
    }
    for (int i=0; i<size; i++)
    {
        if (m_myKey.at(i) < myKey.at(i))
            return true;
        else if (!(m_myKey.at(i) == myKey.at(i)))
            return false;
    }
    return false;
}
 
bool MyKey::operator==(const MyKey& myKey) const
{
    int size = myKey.getSize();
    if (size != m_size)
    {
        m_log.warningLog("compare with different size!");
        if (size > m_size)
            size = m_size;
    }
    for (int i=0; i<size; i++)
    {
        if (!(m_myKey.at(i) == myKey.at(i)))
            return false;
    }
    return true;
}
 
void MyKey::initVariables()
{
    m_size = 0;
    m_myKey.clear();
}
