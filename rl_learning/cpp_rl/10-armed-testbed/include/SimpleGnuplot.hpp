#pragma once
#include <iostream>
#include <map>
#include "gnuplot-iostream.h"

class SimpleGnuplot
{
public:
    SimpleGnuplot();
    ~SimpleGnuplot();
    void sendPlotData(std::vector<std::pair<int, double>> data, bool isFirst, std::string name, std::string color, std::string with);
    void showFigure();
    void exportPNG(std::string name);
    //line style
    //set style line ${n} lt lc lw dt pt ps pi rgb 

private:
    Gnuplot _myGp;
    //默认参数
    std::string lineType = " lt 13";
    std::string lineColor = " lc ";
    std::string withLine = " w ";
    //保存数据
    std::vector<std::vector<std::pair<int, double>>> _dataSaver;

};

