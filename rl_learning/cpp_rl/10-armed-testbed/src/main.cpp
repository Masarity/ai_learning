#include <iostream>
#include "KarmedBandit.h"

int main(int argc, char** argv)
{
    std::cout << "10-armed-testbed start~" << std::endl;
    KarmedBandit my10ArmedTestbed(10, 1000); 
    do 
    {
        /* my10ArmedTestbed.start(true, 0, 1); */
        /* my10ArmedTestbed.start(false, 0.1, 0.1); */
        /* my10ArmedTestbed.start(true, 5.0, 0.1, 1); */
        /* my10ArmedTestbed.start(true, 2, "ucb"); */
        my10ArmedTestbed.start(true, 0.1, true, "gradient ascent");
    }while (my10ArmedTestbed.getGroup() < 2000);
    /* my10ArmedTestbed.returnAvgReward(true, "'greedySelection'", "13"); */
    /* my10ArmedTestbed.returnAvgReward(true, "'epsilonGreedySelection epsilon=0.1'", "13"); */
    /* my10ArmedTestbed.returnAvgReward(true, "'greedySelection with optimistic value 5'", "13"); */
    /* my10ArmedTestbed.returnAvgReward(true, "'ucb c=2'", "13"); */
    my10ArmedTestbed.returnAvgReward(true, "'gradient bandit withBaseLine alpha=0.1'", "13");
    my10ArmedTestbed.resetAvgRewards();
    do 
    {
        /* my10ArmedTestbed.start(true, 0.1, 0.1); */
        /* my10ArmedTestbed.start(false, 0.1, 0.1, 0.1); */
        /* my10ArmedTestbed.start(true, 0.1, 0.1, 0.1); */
        /* my10ArmedTestbed.start(true, 0.1, 0.1); */
        my10ArmedTestbed.start(true, 0.4, true, "gradient ascent");
    }while (my10ArmedTestbed.getGroup() < 2000);
    /* my10ArmedTestbed.returnAvgReward(false, "'epsilonGreedySelection epsilon=0.1'"); */
    /* my10ArmedTestbed.returnAvgReward(false, "'epsilonGreedySelection epsilon=0.1 alpha=0.1'"); */
    /* my10ArmedTestbed.returnAvgReward(false, "'epsilonGreedySelection epsilon=0.1'"); */
    my10ArmedTestbed.returnAvgReward(false, "'gradient bandit withBaseLine alpha=0.4'");
    my10ArmedTestbed.resetAvgRewards();
    /* my10ArmedTestbed.returnAvgReward(false, "'epsilonGreedySelection epsilon=0.1 alpha=0.1'"); */
    /* do */
    /* { */
    /*     my10ArmedTestbed.start(true, 0.01, 0.1); */
    /* }while (my10ArmedTestbed.getGroup() < 2000); */
    /* my10ArmedTestbed.returnAvgReward(false, "'epsilonGreedySelection epsilon=0.01'", "7"); */
    my10ArmedTestbed.showFigure();
    return 0;
}

