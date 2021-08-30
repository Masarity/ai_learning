#include "Environment.h"
#include "SimpleGnuplot.hpp"

int main(int argc, char** argv)
{
    std::cout << "Blackjack game start~" << std::endl;
    Environment env;

    env.simulate();

    return 0;
}

