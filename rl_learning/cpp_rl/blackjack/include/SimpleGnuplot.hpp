#pragma once
#include <iostream>
#include <map>
#include "gnuplot-iostream.h"

class SimpleGnuplot
{
public:
    //很烦
    //为什么这么骚的有不谈
    //武器不行干不过,还不错
    //感觉还不错
    //拆除,manman 视角
    //该出所有的操作
    //保存并推出
    SimpleGnuplot();
    ~SimpleGnuplot();
    void sendPlotData(std::vector<std::pair<int, double>> data, bool isFirst, std::string name, std::string color, std::string with);
    void showFigure();
    void exportPNG(std::string name);
    void setXLabel(std::string labelName);
    void setYLabel(std::string labelName);
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

