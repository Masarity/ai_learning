#include <Eigen/Core>
#include <iostream>
#include "GridWorld1.h"
#include "Agent1.h"

int main(int argc, char** argv)
{
    std::cout << "ok~" << std::endl;
    GridWorld1 gw1(4);
    Agent1 ag1(4);
    ag1.setDiscount(0.9);
    ag1.policyImprovement(gw1);

    return 0;
}

