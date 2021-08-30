#include "world.h"

World::World()
{
    _agent = new Agent;
}

World::~World()
{
    /* std::cout << "网格世界析构" << std::endl; */
    /* if (_states != nullptr) */
    /* { */
    /*     delete _states; */
    /*     _states = nullptr; */
    /*     std::cout << "释放_states" << std::endl; */
    /* } */
    if (_agent != nullptr)
    {
        delete _agent;
        _agent = nullptr;
        std::cout << "释放_agent" << std::endl;
    }
}

