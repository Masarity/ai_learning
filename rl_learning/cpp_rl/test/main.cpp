#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <map>
#include <box2d.h>
using namespace std;
class sortNumber
{
public:
    vector<int> operator()(map<int, pair<int, double>>& a)
    {
        vector<int> ret;
        double max=0;
        for (auto iter=a.begin(); iter != a.end(); iter++)
        {
            cout << fabs(max - iter->second.second) << endl;
            if (fabs(max - iter->second.second) < 1e-5)
            {
                ret.emplace_back(iter->first);
            }
            else if (max < iter->second.second)
            {
                ret.clear();
                max = iter->second.second;
                ret.emplace_back(max);
            }
        }
        return ret;
    }
};
int main(int argc, char** argv)
{
    b2Vec2 gravity(0.0f, -0.0f); //无重力，若要设置自然重力为(0.0f, -9.8f)
    b2World world(gravity);
    map<int, pair<int, double>> k;
    k.insert(pair<int, pair<int, double>>(1, pair<int, double>(0, 0)));
    k.insert(pair<int, pair<int, double>>(2, pair<int, double>(0, 1.1)));
    k.insert(pair<int, pair<int, double>>(3, pair<int, double>(0, 1.099999999)));
    k.insert(pair<int, pair<int, double>>(4, pair<int, double>(0, 1.1000000001)));
    k.insert(pair<int, pair<int, double>>(5, pair<int, double>(0, 0)));
    k.insert(pair<int, pair<int, double>>(6, pair<int, double>(0, 0)));
    k.insert(pair<int, pair<int, double>>(7, pair<int, double>(0, 0)));
    k.insert(pair<int, pair<int, double>>(8, pair<int, double>(0, 0)));
    k.insert(pair<int, pair<int, double>>(9, pair<int, double>(0, 0)));
    k.insert(pair<int, pair<int, double>>(10, pair<int, double>(0, 0)));
    vector<int> myFilter;
    myFilter = sortNumber()(k);
    cout << (int)myFilter.size() << endl;
        std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<double> average(0, 1);
    double probability = 0.1;
    for (int i=0; i<10; i++)
    {
        if (probability >= average(eng))
            cout << "ok" << endl;
        else
            cout << "no" << endl;
    }
    std::cout << "Hello, world!" << std::endl;
    b2Log("hai\n");
    return 0;
}

