#include "SimpleGnuplot.hpp"


SimpleGnuplot::SimpleGnuplot()
{
    std::cout << "SimpleGnuplot is created ~" << std::endl;
    /* _myGp << "plot '../res/data/test.dat'" << lineType << lineColor << withLine << std::endl; */
    /* std::map<int, std::pair<double,double>> data; */ 
    /* data.insert(std::pair<int, std::pair<double, double>>(1, std::pair<double, double>(1, 0.0147622))); */ 
    /* data.insert(std::pair<int, std::pair<double, double>>(2, std::pair<double, double>(2, 0.405762))); */ 
    /* data.insert(std::pair<int, std::pair<double, double>>(3, std::pair<double, double>(3, 0.629756))); */ 
    /* data.insert(std::pair<int, std::pair<double, double>>(4, std::pair<double, double>(4, 0.740506))); */ 
    /* data.insert(std::pair<int, std::pair<double, double>>(5, std::pair<double, double>(5, 0.856143))); */ 
    /* std::vector<std::pair<double, double>> da; */
    /* for (int i=1; i<=5; i++) */
    /*     da.emplace_back(data.at(i)); */

    /* _myGp << "plot '-'" << lineType << lineColor << withLine << std::endl; */
    /* _myGp.send1d(data); */
}

SimpleGnuplot::~SimpleGnuplot()
{
    std::cout << "SimpleGnuplot is deleted ~" << std::endl;
}

void SimpleGnuplot::sendPlotData(std::vector<std::pair<double, double>>& data)
{
    _myGp << "plot '-'" << lineType << lineColor << withLine << std::endl;
    _myGp.send1d(data);
}
