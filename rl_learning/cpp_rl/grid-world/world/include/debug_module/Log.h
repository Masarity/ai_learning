#pragma once
#include <iostream>
#include <sstream>
#include <initializer_list>
#include <stdio.h>

#include "debug_module/consoleOutStyle.h"

class Log
{
public:
    Log();
    ~Log();

    std::string addAttrib(std::string msg, std::initializer_list<int> attribs) const;

    void errorLog(std::string errorMsg) const;
    void warningLog(std::string warningMsg) const;
    void infoLog(std::string infoMsg) const;
    void classLog(std::string classMsg) const;

    void inputLog(const std::string inputMsg) const;

private:

};

