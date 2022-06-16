#ifndef main_H_
#define main_H_

#include <stdbool.h>

#define MAX_USER_STR_SIZE (25+1)
#define FONT_NAME_STR_SIZE 16

#define DEFAULT_FONTS_DIRECTORY "Fonts/"
#define DEFAULT_FONT_EXTENSION ".af"

#define FONT_EXTENSION_LEN 3
#define FONTS_DIRECTION_LEN 6

#define _SYMBOL_WIDTH 30
#define _SYMBOL_HEIGHT 10
#define _SYMBOLS 95
#define TERMINAL_WINDOW_DEFAULT_WIDTH 120
#define DEFAULT_FONT "Big"

#define on true
#define off false
#define ON on
#define OFF off

#define CSI "\033["

enum alignmentModes {
    LEFT,
    CENTER,
    RIGHT,

    left=0,
    center,
    right
};

enum colors {
    DEFAULT,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    BLACK
};

char* reducedDocumentation = 
            "AAT - Ascii Art Text Generator\n"
            "\tThis utility create a cool visual ascii symbols\n"
            "Syntax: aat -option -option OR aat: --option --option\"str\"\n\n"
            "1.ALL ARGUMENTS MUST BE SEPARATED BY SPACE\n"
            "2.RECOMENDED USE \"\" FOR YOUR STRING ARGUMENT BUT YOU CAN USE JUST A SYMBOLS BUT WITHOUT SPACE\n\n"
            "Options:\n"
            "\t--help print a reduced documentation for you\n"
            "\t--font \"fontName\" set font for output string. Font name must be without .af extension. For example: --font test\n"
            "\t-p0 put Off space between symbols\n"
            "\t-p1 put On space between symbols\n"
            "\t--Red change output text color\n"
            "\t--Blue change output text color\n"
            "\t--Yellow change output text color\n"
            "\t--Cyan change output text color\n"
            "\t--Purple change output text color\n"
            "\t--Black change output text color\n"
            "\t--Green change output text color\n"
            "\t--left print output by left side\n"
            "\t--right print output by right side\n"
            "\t--center print output by center\n"
            "\tFor more information check a Documentaion file";

struct AAT_parameters { 
	const unsigned short SYMBOL_WIDTH;
	const unsigned short SYMBOL_HEIGHT;
	const unsigned short SYMBOLS;
	int color;
	int outputAlignment;
	int windowWidth;
	bool isLikeAComment; 
	bool isPaddingEnable;
	bool isChangeSpace;
	bool isSmashing;
	char replacedSymbol;
	char* font;
} aatParameters = {
	_SYMBOL_WIDTH, 
	_SYMBOL_HEIGHT, 
	_SYMBOLS, 
	DEFAULT, 
	CENTER, 
	TERMINAL_WINDOW_DEFAULT_WIDTH, 
	OFF, 
	OFF, 
	OFF, 
	OFF,
	' ', 
	DEFAULT_FONT
};

int printAsciiArtText(char* userStr, char font[aatParameters.SYMBOLS][aatParameters.SYMBOL_HEIGHT][aatParameters.SYMBOL_WIDTH]);
void defineSymbols(unsigned short userStrSymbolCounts, short asciiUserIndexSymbol[MAX_USER_STR_SIZE], char userStr[MAX_USER_STR_SIZE]);
void parseData(FILE* sourceFile, char font[aatParameters.SYMBOLS][aatParameters.SYMBOL_HEIGHT][aatParameters.SYMBOL_WIDTH]); 
const char* setFont(const char* argv);

#endif // main_H_