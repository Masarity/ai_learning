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
    /* _myGp << "set yrange [0.8:3]\n"; */
    _myGp << "plot ";
    /* _myGp << "plot '-'" << lineType << lineColor << withLine << std::endl; */
    /* _myGp.send1d(data); */
}

SimpleGnuplot::~SimpleGnuplot()
{
    std::cout << "SimpleGnuplot is deleted ~" << std::endl;
}

void SimpleGnuplot::sendPlotData(std::vector<std::pair<int, double>> data, bool isFirst, std::string name, std::string color, std::string with)
{
    if (isFirst)
        _myGp << "'-' tit " << name << " "<< lineType << lineColor << color << withLine << with;
    else 
        _myGp << ", '-' tit " << name << " " << lineType << lineColor << color << withLine << with;
    /* _myGp.send1d(data); */
    _dataSaver.emplace_back(data);
}

void SimpleGnuplot::showFigure()
{
    _myGp << std::endl;
    for (auto iter=_dataSaver.begin(); iter != _dataSaver.end(); iter++)
    {
        _myGp.send1d(*iter);
    }
}

void SimpleGnuplot::exportPNG(std::string name)
{
    _myGp << "set terminal png size 800,600\n" << "set output " << name << std::endl << "replot\n";
}
