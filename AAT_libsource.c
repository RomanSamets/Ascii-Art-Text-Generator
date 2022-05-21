#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>

#define MAXUSERSTRSIZE 20

char* fileToOpen;

struct AAT_parameters {
	char* fontName;
	int isPaddingEnable; 
	int color;
	int outputAlignment;
	int isLikeAComment; 
	int isChangeSpace;
	int windowWidth;
	char replacedSymbol;
};

const unsigned short symbolWidth = 30;
const unsigned short symbolHeight = 10;
const unsigned short symbols = 95;

void defineSymbols(unsigned short symbolCounts, short asciiUserIndexSymbol[MAXUSERSTRSIZE], char userStr[MAXUSERSTRSIZE]);
const char* setFont(const char* fontName);
void parseData(int symbols, int symbolHeight, int symbolWidth, FILE* sourceFile, char font[symbols][symbolHeight][symbolWidth]);


int printAsciiArtText(char* userStr, struct AAT_parameters aat_parameters) {
	FILE* sourceFile = NULL;
	
	char font[symbols][symbolHeight][symbolWidth];

	sourceFile = fopen(setFont(aat_parameters.fontName), "r");
    if (sourceFile == NULL) {printf("\nError: %25s", "Can't open file");return 1;}
    free(fileToOpen);

    parseData(symbols, symbolHeight, symbolWidth, sourceFile, font);
    fclose(sourceFile);

	if (userStr[0] == 1) {return 0;}

	short asciiUserIndexSymbol[MAXUSERSTRSIZE];
	unsigned short symbolCounts = strlen(userStr);

	char paddingSymbol;

	int totalAsciiStrWidth = 0;
	int savedSymbol = 0;
	int nextSymbol = 0;
	int nonAvaible = 0;
	int nextLine = 0;
	int spaces = 0;

	switch(aat_parameters.color) {
		case 1: printf("\033[0;31m"); break; // Red
		case 2: printf("\033[0;32m"); break; // Green
		case 3: printf("\033[0;33m"); break; // Yellow
		case 4: printf("\033[0;34m"); break; // Blue
		case 5: printf("\033[0;35m"); break; // Purple
		case 6: printf("\033[0;36m"); break; // Cyan
		case 7: printf("\033[0;30m"); break; // Black
		default: printf("\033[0m"); break;
	}

	if (aat_parameters.isLikeAComment == 1) {printf("/***\n");}

	if (aat_parameters.isChangeSpace == 1) {paddingSymbol = aat_parameters.replacedSymbol;} 
	else {paddingSymbol = ' ';}
 	
    defineSymbols(symbolCounts, asciiUserIndexSymbol, userStr);

	for (int i = 0; i < symbolCounts; ++i) {
		if (aat_parameters.isPaddingEnable == 1) {
			totalAsciiStrWidth += strlen(font[asciiUserIndexSymbol[i]][nextLine]) + 1;
			if (totalAsciiStrWidth > aat_parameters.windowWidth) {nonAvaible++;}
		} else {
			totalAsciiStrWidth += strlen(font[asciiUserIndexSymbol[i]][nextLine]);
			if (totalAsciiStrWidth > aat_parameters.windowWidth) {nonAvaible++;}
		}
	}

	for (int i = 0; i < symbolHeight; ++i) {
		
		if(aat_parameters.outputAlignment == 1) {for (int i = 0; i < (((round(aat_parameters.windowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
		if(aat_parameters.outputAlignment == 2) {for (int i = 0; i < ((round(aat_parameters.windowWidth - totalAsciiStrWidth))-3); ++i) {printf("%c", paddingSymbol);}}
		
		for (int i = 0; i < symbolCounts-nonAvaible; ++i) {

			for (int i = 0; i < strlen(font[asciiUserIndexSymbol[nextSymbol]][nextLine]); ++i) {
				if (aat_parameters.isChangeSpace == 1) {
					if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
						font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] = aat_parameters.replacedSymbol;
					}	
				}
				printf("%c", font[asciiUserIndexSymbol[nextSymbol]][nextLine][i]);	
			}
			
			if (aat_parameters.isPaddingEnable == 1) {printf("%c", paddingSymbol);} 

			++nextSymbol;
			savedSymbol = nextSymbol;
		} 

		printf("\n");
		++nextLine;
		nextSymbol=0;	
	}

	if (totalAsciiStrWidth > aat_parameters.windowWidth) {
		int nonAvaibleSymbol = savedSymbol;

		for (int i = 0; i < symbolHeight; ++i) {

			if (aat_parameters.outputAlignment == 1) {for (int i = 0; i < (((round(aat_parameters.windowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
			if (aat_parameters.outputAlignment == 2) {for (int i = 0; i < ((round(aat_parameters.windowWidth - totalAsciiStrWidth))); ++i) {printf("%c", paddingSymbol);}}

			for (int i = 0; i < nonAvaible; ++i) {

				for (int i = 0; i < strlen(font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine]); ++i) {

					if (aat_parameters.isChangeSpace == 1) {
						if (font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] == ' ') {
							font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] = aat_parameters.replacedSymbol;
						}	
					}
					printf("%c", font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i]);	
				}
				
				if (aat_parameters.isPaddingEnable == 1) {printf("%c", paddingSymbol);} 

				++nonAvaibleSymbol;
			}

			printf("\n");
			++nextLine;
			nonAvaibleSymbol=savedSymbol;	
		}
	}

	if (aat_parameters.isLikeAComment == 1) {printf("***/\n");}

	//Reset color Settings
	printf("\033[0m");	
}

const char* setFont(const char* fontName) {
    char fileName[16]; 

    strcpy(fileName, fontName);
    
    fileToOpen = malloc(sizeof(fileName)+4+6); // 4 it's a extenstion str len with nul symbol 6 it's a Fonts/ size
    
    strcpy(fileToOpen, "Fonts/");
    strcat(fileToOpen, fileName); 
    strcat(fileToOpen, ".af"); 

    return fileToOpen;
}

void parseData(int symbols, int symbolHeight, int symbolWidth, FILE* sourceFile, char font[symbols][symbolHeight][symbolWidth]) {
    char buf[symbolWidth];

    for (int s = 0; s < symbols; ++s) {
        for (int h = 0; h < symbolHeight; ++h) {
            fgets(buf, symbolWidth, sourceFile);
            strcpy(buf, strtok(buf, "%"));
            strcpy(font[s][h], buf);
        }
    }
}

void defineSymbols(unsigned short symbolCounts, short asciiUserIndexSymbol[MAXUSERSTRSIZE], char userStr[MAXUSERSTRSIZE]) {
    for (int csi = 0; csi < symbolCounts; ++csi) {
        switch(userStr[csi]) {
			case 'A':  asciiUserIndexSymbol[csi] = 0;  break;
			case 'a':  asciiUserIndexSymbol[csi] = 1;  break;
			case 'B':  asciiUserIndexSymbol[csi] = 2;  break;
			case 'b':  asciiUserIndexSymbol[csi] = 3;  break;
			case 'C':  asciiUserIndexSymbol[csi] = 4;  break;
			case 'c':  asciiUserIndexSymbol[csi] = 5;  break;
			case 'D':  asciiUserIndexSymbol[csi] = 6;  break;
			case 'd':  asciiUserIndexSymbol[csi] = 7;  break;
			case 'E':  asciiUserIndexSymbol[csi] = 8;  break;
			case 'e':  asciiUserIndexSymbol[csi] = 9;  break;
			case 'F':  asciiUserIndexSymbol[csi] = 10; break;
			case 'f':  asciiUserIndexSymbol[csi] = 11; break;
			case 'G':  asciiUserIndexSymbol[csi] = 12; break;
			case 'g':  asciiUserIndexSymbol[csi] = 13; break;
			case 'H':  asciiUserIndexSymbol[csi] = 14; break;
			case 'h':  asciiUserIndexSymbol[csi] = 15; break;
			case 'I':  asciiUserIndexSymbol[csi] = 16; break;
			case 'i':  asciiUserIndexSymbol[csi] = 17; break;
			case 'J':  asciiUserIndexSymbol[csi] = 18; break;
			case 'j':  asciiUserIndexSymbol[csi] = 19; break;
			case 'K':  asciiUserIndexSymbol[csi] = 20; break;
			case 'k':  asciiUserIndexSymbol[csi] = 21; break;
			case 'L':  asciiUserIndexSymbol[csi] = 22; break;
			case 'l':  asciiUserIndexSymbol[csi] = 23; break;
			case 'M':  asciiUserIndexSymbol[csi] = 24; break;
			case 'm':  asciiUserIndexSymbol[csi] = 25; break;
			case 'N':  asciiUserIndexSymbol[csi] = 26; break;
			case 'n':  asciiUserIndexSymbol[csi] = 27; break;
			case 'O':  asciiUserIndexSymbol[csi] = 28; break;
			case 'o':  asciiUserIndexSymbol[csi] = 29; break;
			case 'P':  asciiUserIndexSymbol[csi] = 30; break;
			case 'p':  asciiUserIndexSymbol[csi] = 31; break;
			case 'Q':  asciiUserIndexSymbol[csi] = 32; break;
			case 'q':  asciiUserIndexSymbol[csi] = 33; break;
			case 'R':  asciiUserIndexSymbol[csi] = 34; break;
			case 'r':  asciiUserIndexSymbol[csi] = 35; break;
			case 'S':  asciiUserIndexSymbol[csi] = 36; break;
			case 's':  asciiUserIndexSymbol[csi] = 37; break;
			case 'T':  asciiUserIndexSymbol[csi] = 38; break;
			case 't':  asciiUserIndexSymbol[csi] = 39; break;
			case 'U':  asciiUserIndexSymbol[csi] = 40; break;
			case 'u':  asciiUserIndexSymbol[csi] = 41; break;
			case 'V':  asciiUserIndexSymbol[csi] = 42; break;
			case 'v':  asciiUserIndexSymbol[csi] = 43; break;
			case 'W':  asciiUserIndexSymbol[csi] = 44; break;
			case 'w':  asciiUserIndexSymbol[csi] = 45; break;
			case 'X':  asciiUserIndexSymbol[csi] = 46; break;
			case 'x':  asciiUserIndexSymbol[csi] = 47; break;
			case 'Y':  asciiUserIndexSymbol[csi] = 48; break;
			case 'y':  asciiUserIndexSymbol[csi] = 49; break;
			case 'Z':  asciiUserIndexSymbol[csi] = 50; break;
			case 'z':  asciiUserIndexSymbol[csi] = 51; break;
			case '0':  asciiUserIndexSymbol[csi] = 52; break;
			case '1':  asciiUserIndexSymbol[csi] = 53; break;
			case '2':  asciiUserIndexSymbol[csi] = 54; break;
			case '3':  asciiUserIndexSymbol[csi] = 55; break;
			case '4':  asciiUserIndexSymbol[csi] = 56; break;
			case '5':  asciiUserIndexSymbol[csi] = 57; break;
			case '6':  asciiUserIndexSymbol[csi] = 58; break;
			case '7':  asciiUserIndexSymbol[csi] = 59; break;
			case '8':  asciiUserIndexSymbol[csi] = 60; break;
			case '9':  asciiUserIndexSymbol[csi] = 61; break;
			case '.':  asciiUserIndexSymbol[csi] = 62; break;
			case ',':  asciiUserIndexSymbol[csi] = 63; break;
			case ':':  asciiUserIndexSymbol[csi] = 64; break;
			case ';':  asciiUserIndexSymbol[csi] = 65; break;
			case '\'': asciiUserIndexSymbol[csi] = 66; break;
			case '"':  asciiUserIndexSymbol[csi] = 67; break;
			case '!':  asciiUserIndexSymbol[csi] = 68; break;
			case '?':  asciiUserIndexSymbol[csi] = 69; break;
			case '/':  asciiUserIndexSymbol[csi] = 70; break;
			case '|':  asciiUserIndexSymbol[csi] = 71; break;
			case '\\': asciiUserIndexSymbol[csi] = 72; break;
			case '(':  asciiUserIndexSymbol[csi] = 73; break;
			case ')':  asciiUserIndexSymbol[csi] = 74; break;
			case '[':  asciiUserIndexSymbol[csi] = 75; break;
			case ']':  asciiUserIndexSymbol[csi] = 76; break;
			case '{':  asciiUserIndexSymbol[csi] = 77; break;
			case '}':  asciiUserIndexSymbol[csi] = 78; break;
			case '<':  asciiUserIndexSymbol[csi] = 79; break;
			case '>':  asciiUserIndexSymbol[csi] = 80; break;
			case '+':  asciiUserIndexSymbol[csi] = 81; break;
			case '-':  asciiUserIndexSymbol[csi] = 82; break;
			case '*':  asciiUserIndexSymbol[csi] = 83; break;
			case '=':  asciiUserIndexSymbol[csi] = 84; break;
			case '&':  asciiUserIndexSymbol[csi] = 85; break;
			case '^':  asciiUserIndexSymbol[csi] = 86; break;
			case '%':  asciiUserIndexSymbol[csi] = 87; break;
			case '$':  asciiUserIndexSymbol[csi] = 88; break;
			case '#':  asciiUserIndexSymbol[csi] = 89; break;
			case '@':  asciiUserIndexSymbol[csi] = 90; break;
			case '_':  asciiUserIndexSymbol[csi] = 91; break;
			case '~':  asciiUserIndexSymbol[csi] = 92; break;
			case '`':  asciiUserIndexSymbol[csi] = 93; break;
			case ' ':  asciiUserIndexSymbol[csi] = 94; break;
		}
    }
}