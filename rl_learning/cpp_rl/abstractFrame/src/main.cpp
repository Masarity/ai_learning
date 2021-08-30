#include <Eigen/Core>
#include <iostream>
#include "gridWorld.h"

int main(int argc, char** argv)
{
    /* Eigen::Vector2d v2d(10, 10); */
    /* std::cout << v2d << std::endl; */
    GridWorld gridWorld;
    gridWorld.simulate();
    return 0;
}

