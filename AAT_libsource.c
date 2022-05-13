#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>
#include "AAT.h"

int SIZE = 20;
int TerminalWidth = 130;

int NextValue = 0;

#include "Fonts.dat"

int printAsciiLogo(char* userStr, int PaddingEnable, int Color, int Outputview, int LikeAComment, int ReplaceSpace, int usedFont, int WindowWidth) {
if (userStr[0] == 1 ) {return 0;}

	const unsigned short symbolWidth = 30;
	const unsigned short symbolHeight = 10;

	char replacedSymbol = '.';

	int nextSymbol = 0;
	int nextLine = 0;
	int spaces=0;
	int nonAvaible = 0;
	int savedSymbol = 0;
	int totalAsciiStrWidth = 0;

	unsigned short countOfSymbols = strlen(userStr);
	char paddingSymbol;

	short asciiUserIndexSymbol[SIZE];

	// Set Color for output
	switch(Color) {
		case 1: printf("\033[0;31m"); break; // Red
		case 2: printf("\033[0;32m"); break; // Green
		case 3: printf("\033[0;33m"); break; // Yellow
		case 4: printf("\033[0;34m"); break; // Blue
		case 5: printf("\033[0;35m"); break; // Purple
		case 6: printf("\033[0;36m"); break; // Cyan
		case 7: printf("\033[0;30m"); break; // Black
		default: printf("\033[0m"); break;
	}

	if (LikeAComment == 1) {printf("/***\n");}

	if (ReplaceSpace == 1) {paddingSymbol = replacedSymbol;} 
	else {paddingSymbol = ' ';}
 	
 	for (int csi = 0; csi < countOfSymbols; ++csi) {
		#include "symbolsDefinition.ini"
	}

	for (int i = 0; i < countOfSymbols; ++i) {
		if ( PaddingEnable == 1) {
			totalAsciiStrWidth += strlen( data[usedFont][asciiUserIndexSymbol[i]][nextLine]) + 1 + 1;
			if (totalAsciiStrWidth > WindowWidth) {nonAvaible++;}
		} else {
			totalAsciiStrWidth += strlen( data[usedFont][asciiUserIndexSymbol[i]][nextLine]);
			if (totalAsciiStrWidth > WindowWidth) {nonAvaible++;}
		}
	}

	// Print Function
	for (int i = 0; i < symbolHeight; ++i) {
		
		if(Outputview==1) {for (int i = 0; i < (((round(WindowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
		if(Outputview==2) {for (int i = 0; i < ((round(WindowWidth - totalAsciiStrWidth))-3); ++i) {printf("%c", paddingSymbol);}}
		
		for (int i = 0; i < countOfSymbols-nonAvaible; ++i) {
			for (int i = 0; i < strlen( data[usedFont][asciiUserIndexSymbol[nextSymbol]][nextLine]); ++i) {
				if (ReplaceSpace == 1) {
					if ( data[usedFont][asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
						data[usedFont][asciiUserIndexSymbol[nextSymbol]][nextLine][i] = replacedSymbol;
					}	
				}
				printf("%c", data[usedFont][asciiUserIndexSymbol[nextSymbol]][nextLine][i]);	
			}
			
			if ( PaddingEnable == 1) {printf("%c", paddingSymbol);} 
			else {}

			++nextSymbol;
			savedSymbol = nextSymbol;
		} 
		printf("\n");
		++nextLine;
		nextSymbol=0;	
	}

	if (totalAsciiStrWidth > WindowWidth) {
		int nonAvaibleSymbol = savedSymbol;

		for (int i = 0; i < symbolHeight; ++i) {
			if(Outputview==1) {for (int i = 0; i < (((round(WindowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
			if(Outputview==2) {for (int i = 0; i < ((round(WindowWidth - totalAsciiStrWidth))-3); ++i) {printf("%c", paddingSymbol);}}

			for (int i = 0; i < nonAvaible; ++i) {
				for (int i = 0; i < strlen( data[usedFont][asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine]); ++i) {
					if (ReplaceSpace == 1) {
						if ( data[usedFont][asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] == ' ') {
							data[usedFont][asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] = replacedSymbol;
						}	
					}
					printf("%c", data[usedFont][asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i]);	
				}
				
				if ( PaddingEnable == 1) {printf("%c", paddingSymbol);} 
				else {}

				++nonAvaibleSymbol;
			}
			printf("\n");
			++nextLine;
			nonAvaibleSymbol=savedSymbol;	
		}

		if (LikeAComment == 1) {printf("***/\n");}

		//Reset color Settings
		printf("\033[0m");
	}
		
}