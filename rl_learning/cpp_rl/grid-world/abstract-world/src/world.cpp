#include "world.h"

World::World(int dimension)
    :_dimension(dimension)
    ,_states(new std::set<int>)
{
    std::cout << "环境构造" << std::endl;
    for (int i=0; i<dimension; i++)
        for (int j=0; j<dimension; j++)
        {
            _states->insert(i+j*10);
        }
}

World::~World()
{
    std::cout << "网格世界析构" << std::endl;
    if (_states != nullptr)
    {
        delete _states;
        _states = nullptr;
        std::cout << "释放_states" << std::endl;
    }
}

