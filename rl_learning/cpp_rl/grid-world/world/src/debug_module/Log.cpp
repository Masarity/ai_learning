#include "debug_module/Log.h"


Log::Log()
{
}

Log::~Log()
{
}

std::string Log::addAttrib(std::string msg, std::initializer_list<int> attribs) const
{
    std::stringstream ss;
    int cnt = 0;

    ss << STYLE_BEGIN;

    for (auto &iter : attribs)
    {
        if (cnt > 0)
            ss << ";";
        else 
            cnt++;
        ss << iter;
    }

    ss << STYLE_END;

    ss << msg;

    ss << STYLE_BEGIN << END << STYLE_END;

    return ss.str();
}

void Log::errorLog(std::string errorMsg) const
{
    std::stringstream ss;

    ss << addAttrib("[ERROR]", {BLINK, FORE_RED, BACK_BROWN});

    ss << "\t" << addAttrib("||", {ERASE}) << " ";

    ss << addAttrib(errorMsg, {FORE_RED, HALFLIGHT, BACK_WHITE});

    std::cout << ss.str() << std::endl;
}

void Log::warningLog(std::string warningMsg) const
{
    std::stringstream ss;

    ss << addAttrib("[WARNING]", {HIGHLIGHT, FORE_YELLOW, BACK_BLUE});

    ss << "\t" << addAttrib("||", {ERASE}) << " ";

    ss << addAttrib(warningMsg, {FORE_YELLOW, HIGHLIGHT});

    std::cout << ss.str() << std::endl;

}

void Log::infoLog(std::string infoMsg) const
{
    std::stringstream ss;

    ss << addAttrib("[INFO]", {HIGHLIGHT, FORE_BLACK, BACK_WHITE});

    ss << "\t" << addAttrib("||", {ERASE}) << " ";

    ss << addAttrib(infoMsg, {FORE_GREEN, HIGHLIGHT});

    std::cout << ss.str() << std::endl;
}

void Log::classLog(std::string classMsg) const
{
    std::stringstream ss;

    ss << addAttrib("[CLASS]", {HIGHLIGHT, FORE_WHITE, BACK_BLACK});

    ss << "\t" << addAttrib("||", {ERASE}) << " ";

    ss << addAttrib(classMsg, {FORE_WHITE, HIGHLIGHT});

    std::cout << ss.str() << std::endl;
}
 
void Log::inputLog(const std::string inputMsg) const
{
    std::stringstream ss;

    ss << addAttrib("[INPUT]", {HIGHLIGHT, FORE_WHITE, BACK_BLUE});

    ss << "\t" << addAttrib("||", {ERASE}) << " ";

    ss << addAttrib(inputMsg, {FORE_BLUE, HIGHLIGHT});

    std::cout << ss.str() << ": ";
}
