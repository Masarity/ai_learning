#pragma once
#include <iostream>
#include <map>
#include "gnuplot-iostream.h"

class SimpleGnuplot
{
public:
    SimpleGnuplot();
    ~SimpleGnuplot();
    void sendPlotData(std::vector<std::pair<double, double>>& data);
    //line style
    //set style line ${n} lt lc lw dt pt ps pi rgb 

private:
    Gnuplot _myGp;
    //默认参数
    std::string lineType = " lt 13";
    std::string lineColor = " lc 13";
    std::string withLine = "w lp";

};

