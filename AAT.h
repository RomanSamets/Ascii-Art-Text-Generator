#ifndef AAT_H
#define AAT_H

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
};

extern struct AAT_parameters aatParameters;

int printAsciiArtText(char* userStr, struct AAT_parameters aatParameters);

#define aat aatParameters

#endif  // AAT_H