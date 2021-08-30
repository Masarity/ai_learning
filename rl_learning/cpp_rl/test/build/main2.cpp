#include <box2d.h>
#include <iostream>

class Body
{
public:
    Body()
    {
        _fixtureDef = new b2FixtureDef;
        ballShape = new b2CircleShape;
        _fixtureDef->density = 1.0f;
        _fixtureDef->friction = 0.2f;
        _fixtureDef->restitution = 0.8f;
        ballShape->m_radius = 3.f;
        _fixtureDef->shape = ballShape;

    }  
    ~Body()
    {
        if (_fixtureDef != nullptr)
        {
            std::cout << "delete fixtureDef" << std::endl;
            delete _fixtureDef;
            _fixtureDef = nullptr;
        }

    }

public:
    b2Body* myBody;
    b2CircleShape* ballShape;
    b2FixtureDef* _fixtureDef;
};

class World2d
{
public:
    World2d()
    {
        //创建世界
        _myWorld = new b2World(_gravity);
        _bodyDef = new b2BodyDef;
        _bodyDef->type = b2_dynamicBody;
        _bodyDef->linearDamping = 0.3f;
        _bodyDef->angularDamping = 0.2f;
        _bodyDef->allowSleep = true;

    }
    ~World2d()
    {
        if (_myWorld != nullptr)
        {
            std::cout << "delete world" << std::endl;
            delete _myWorld;
            _myWorld = nullptr;
        }
        if (_bodyDef != nullptr)
        {
            std::cout << "delete bodyDef" << std::endl;
            delete _bodyDef;
            _bodyDef = nullptr;
        }
    }

    void addBodies(b2Vec2 pos, Body& body)
    {
        _bodyDef->position = pos;
        body.myBody = _myWorld->CreateBody(_bodyDef);    
        body.myBody->CreateFixture(body._fixtureDef);
    }

    void simulation()
    {
        _myWorld->Step(_timeStep, _viter, _piter);
        std::cout << "world simulate once" << std::endl;
        for (b2Contact* c=_myWorld->GetContactList(); c; c=c->GetNext())
        {
            std::cout << c->GetChildIndexA() << std::endl;
        }
    }

    virtual void test(int a);

private:
    b2Vec2 _gravity = b2Vec2(0.0f, -0.0f);
    b2World* _myWorld;
    float _timeStep = 1.0f / 30.f;
    int32 _viter = 10;
    int32 _piter = 8;
    b2BodyDef* _bodyDef;
};


int main(int argc, char** argv)
{
    World2d w2d;
    Body ball1;
    Body ball2;
    w2d.addBodies(b2Vec2(0.f, 0.f), ball1);
    w2d.addBodies(b2Vec2(10.f, 0.f), ball2);
    ball1.myBody->ApplyLinearImpulseToCenter(b2Vec2(100.f, 0.f), true);
    for (int i=0; i<120; i++)
    {

        w2d.simulation();
        std::cout << ball1.myBody->GetLinearVelocity().x << "world center: " << ball1.myBody->GetLinearVelocityFromWorldPoint(ball1.myBody->GetWorldCenter()).x << std::endl;
        std::cout << ball2.myBody->GetLinearVelocity().x << std::endl;
    }
    return 0;
}

