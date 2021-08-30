#ifndef CONSOLE_OUT_PUT_STYLE
#define CONSOLE_OUT_PUT_STYLE

#define STYLE_BEGIN "\033["
#define SPLIT ";"
#define STYLE_END "m"

#define CLS "\033[2J"

enum textStyle
{
    END = 0,
    HIGHLIGHT,
    HALFLIGHT,
    ITALIC,
    UNDERLINE,
    BLINK,
    FLASH,
    REVERSE,
    REMOVE,
    ERASE,
};

enum foreColor
{
    FORE_BLACK = 30,
    FORE_RED,
    FORE_GREEN,
    FORE_YELLOW,
    FORE_BLUE,
    FORE_PURPLE,
    FORE_DARKGREEN,
    FORE_WHITE,
};

enum backColor
{
    BACK_BLACK = 40,
    BACK_RED,
    BACK_GREEN,
    BACK_BROWN,
    BACK_BLUE,
    BACK_FUCHSIN,
    BACK_GREENY_BULE,
    BACK_WHITE,
};

#endif
