#ifndef AAT_H
#define AAT_H

struct AAT_parameters {
	char* fontName;
	int isPaddingEnable; 
	int color;
	int outputAlignment;
	int isLikeAComment; 
	int isChangeSpace;
	int windowWidth;
	char replacedSymbol;

} aat_parameters = {"Big", 0, 0, 1, 0, 0, 120, '.'};

int printAsciiArtText(char* userStr, struct AAT_parameters aat_parameters);

#define aat aat_parameters

#endif  // AAT_H