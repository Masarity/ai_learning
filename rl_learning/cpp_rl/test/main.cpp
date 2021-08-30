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
    
    //台球无需地面
/*     b2BodyDef groundBodyDef; */
/*     groundBodyDef.position.Set(0.0f, -10.0f); */
/*     b2Body* groundBody = world.CreateBody(&groundBodyDef); */
/*     b2PolygonShape groundBox; */
/*     groundBox.SetAsBox(50.0f, 10.0f); */
/*     groundBody->CreateFixture(&groundBox, 0.0f); */

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 270.0f);

    b2Body* body = world.CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 7.0f;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.f;
    body->CreateFixture(&fixtureDef);
    body->ApplyLinearImpulse(b2Vec2(0.0f, 270.0f), b2Vec2(0.0f, 9.5f), true);

    //台球桌边缘
    b2BodyDef bodyDef2;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(-500.f, 278.f);
    b2Body* topBody = world.CreateBody(&bodyDef);

    b2Vec2 leftTop(-500, 278);
    b2Vec2 rightTop(500, 278);
    /* b2Vec2 rightBottom(500, -278); */
    /* b2Vec2 leftBottom(-500, -278); */

    b2EdgeShape topEdge;
    topEdge.SetTwoSided(leftTop, rightTop);
    /* b2EdgeShape rightEdge; */
    /* rightEdge.SetTwoSided(rightTop, rightBottom); */
    /* b2EdgeShape downEdge; */
    /* downEdge.SetTwoSided(rightBottom, leftBottom); */
    /* b2EdgeShape leftEdge; */
    /* leftEdge.SetTwoSided(leftBottom, leftTop); */

    topBody->CreateFixture(&topEdge, 0.0f);



    float timeStep = 1.0f / 60.0f;
    int32 velocityIter = 6;
    int32 positionIter = 2;

    for (int32 i=0; i < 120; i++)
    {
        world.Step(timeStep, velocityIter, positionIter);
        std::cout << "test : " << world.GetContactCount() << std::endl;
        /* for (b2ContactEdge* c= body->GetContactList(); c; c = c->next) */
        /* { */
        /*     std::cout << "tset: " << c->contact << std::endl; */
        /* } */
        /* b2Vec2 position = body->GetPosition(); */
        /* float angle = body->GetAngle(); */
        /* std::cout << "position: " << position.x << ", " << position.y */ 
        /*     << " angle: " << angle << std::endl; */
    }

    
    b2Log("hai\n");
    return 0;
}

void test01()
{

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
}
