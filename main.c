#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>

int printAsciiLogo(char* userStr);

#define SIZE 20
int TerminalWidth = 130;

int NextValue = 0;

char* ReducedDocumentation = "AAT - Ascii Art Text Generator\n\tThis utility create a cool visual ascii symbols\nSyntax: aat --option --option\"str\"\n\n1.ALL ARGUMENTS MUST BE SEPARATED BY SPACE --opt1 --opt2\n2.RECOMENDED USE \"\" FOR YOUR STRING ARGUMENT BUT YOU CAN USE JUST A SYMBOLS BUT WITHOUT SPACE\n\nAll Options:\n\t--help print a reduced documentation for you\n\t--f \"fontName\" set a font for output string\n\t--p0 put Off space between symbols\n\t--p1 put On space between symbols\n\t--Red change output text color\n\t--Blue change output text color\n\t--Yellow change output text color\n\t--Cyan change output text color\n\t--Purple change output text color\n\t--Black change output text color\n\t--Green change output text color\n\t--l print output by left side\n\t--r print output by right side\n\t--c print output by center\n\tFor more information check a Documentaion file";

int PaddingEnable = 1;
int Color = 0;
int Outputview = 1;
int LikeAComment = 0;
int ReplaceSpace = 0;
int usedFont = 0;
int WindowWidth = 130;

#include "Fonts.dat"

// int countsOfFonts = 2;
// char Fonts[countsOfFonts][95][10][30];

// void inicializeFonts(char Fonts[countsOfFonts][95][10][30]) {
// 	for (int i = 0; i < countsOfFonts; ++i) {
// 		for (int i = 0; i < 95; ++i) {
// 			for (int i = 0; i < 10; ++i) {
// 				for (int i = 0; i < ; ++i) {
					
// 				}
// 			}
// 		}
// 	}
// }

int main(int argc, char const *argv[]) {
	char userStr[SIZE];
	
	for (int i = 1; i < argc; ++i) {
		if (NextValue == 1) {
			if ( isalpha(argv[i][0]) ) {
				size_t size = strlen(argv[i]);
				char userInput[size];
				memccpy(userInput, argv[i], '\0', size);

				if ((strncmp(userInput, "roman", size)) == 0) {
					usedFont=0;
				}
				if ((strncmp(userInput, "roman", size)) == 0) {
					usedFont=1;
				}  

            } else if (isdigit(argv[i][0]) && atoi(argv[i]) < 9) {
            	usedFont=atoi(argv[i]);
            } else if (isdigit(argv[i][0]) && atoi(argv[i]) > 29) {
				size_t size = strlen(argv[i]);
				char buf[size];
				memccpy(buf, argv[i], '\0', size);
	            WindowWidth = atoi(buf);  
			}

			NextValue = 0;
			continue;
		}	

		if (   strcmp(argv[i], "--c")      !=0 
			&& strcmp(argv[i], "--l")      !=0 
			&& strcmp(argv[i], "--r")      !=0
			&& strcmp(argv[i], "--p0")     !=0
			&& strcmp(argv[i], "--p1")     !=0 
			&& strcmp(argv[i], "--help")   !=0
			&& strcmp(argv[i], "--lk0")    !=0
			&& strcmp(argv[i], "--lk1")    !=0
			&& strcmp(argv[i], "--Red")    !=0
			&& strcmp(argv[i], "--Green")  !=0
		    && strcmp(argv[i], "--Yellow") !=0
		    && strcmp(argv[i], "--Blue")   !=0
		    && strcmp(argv[i], "--Purple") !=0
		    && strcmp(argv[i], "--Cyan")   !=0
		    && strcmp(argv[i], "--Black")  !=0
		    && strcmp(argv[i], "--f")      !=0
		    && strcmp(argv[i], "--rp0")    !=0
		    && strcmp(argv[i], "--rp1")    !=0
		    && strcmp(argv[i], "--wt")    !=0
		    && strcmp(argv[i], "--w")    !=0
		    && NextValue                   != 1 ) {
			
			for (int j = 0; j < strlen(argv[i]); ++j) {
				if (argc > 1 ) {
					userStr[j] = argv[i][j];
					userStr[strlen(argv[i])] = '\0';
				}
			}
		}

		if (strcmp(argv[i], "--c")==0) {Outputview = 1;}
		if (strcmp(argv[i], "--l")==0) {Outputview = 0;}
		if (strcmp(argv[i], "--r")==0) {Outputview = 2;}
		if (strcmp(argv[i], "--p0")==0) {PaddingEnable = 0;}
		if (strcmp(argv[i], "--p1")==0) {PaddingEnable = 1;}
		if (strcmp(argv[i], "--help")==0) {printf("%s",ReducedDocumentation);return 0;}
		if (strcmp(argv[i], "--lk0")==0) {LikeAComment = 0;}
		if (strcmp(argv[i], "--lk1")==0) {LikeAComment = 1;}
		if (strcmp(argv[i], "--Red")==0) {Color=1;}
		if (strcmp(argv[i], "--Green")==0) {Color=2;}
		if (strcmp(argv[i], "--Yellow")==0) {Color=3;}
		if (strcmp(argv[i], "--Blue")==0) {Color=4;}
		if (strcmp(argv[i], "--Purple")==0) {Color=5;}
		if (strcmp(argv[i], "--Cyan")==0) {Color=6;}
		if (strcmp(argv[i], "--Black")==0) {Color=7;}
		if (strcmp(argv[i], "--rp1")==0) {ReplaceSpace=1;}
		if (strcmp(argv[i], "--rp0")==0) {ReplaceSpace=0;}
		if (strcmp(argv[i], "--wt")==0) {WindowWidth=TerminalWidth;}
		if (strcmp(argv[i], "--w")==0) {
			NextValue = 1;
			continue;
		}
		if (strcmp(argv[i], "--f")==0) {
			NextValue = 1;
			continue;
		}
	}

	if (argc == 1) {
		printf("Enter a string: ");
		scanf("%20[^\n]s", userStr);
	} 

	printAsciiLogo(userStr);
	
	#ifdef _WIN32
		system("pause");
	#endif
	#ifdef linux
		printf("Press any key...");
		int pause = getchar();
	#endif

	return 0;
}

int printAsciiLogo(char* userStr) {
	if (userStr[0] == 1 ) {return 0;}

	const unsigned short symbolWidth = 30;
	const unsigned short symbolHeight = 10;

	char replacedSymbol = '.';

	unsigned short countOfSymbols = strlen(userStr);
	char paddingSymbol;

	short asciiUserIndexSymbol[SIZE];

	int nextSymbol = 0;
	int nextLine = 0;
	int spaces=0;
	int nonAvaible = 0;
	int savedSymbol = 0;
	int totalAsciiStrWidth = 0;

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









		// for (int i = 0; i < countOfSymbols; ++i) {

		// 	for (int i = 0; i < strlen(FONT[0][asciiUserIndexSymbol[nextSymbol]][4]); ++i) {
			
		// 		printf("line lenght %d\n", strlen(FONT[0][asciiUserIndexSymbol[nextSymbol]][4]));				

		// 		if(FONT[0][asciiUserIndexSymbol[nextSymbol]][4][i] == ' ') {
		// 			++spaces;
		// 			printf("%d\n", spaces);
		// 		} else {

		// 		}
			// 	if (FONT[0][asciiUserIndexSymbol[nextSymbol]][nextLine][i] == FONT[0][asciiUserIndexSymbol[nextSymbol]][nextLine][i+1]) {
			// 	}
			//}
			// printf("%s", FONT[0][asciiUserIndexSymbol[nextSymbol]][nextLine]);
			// //printf("%s", padding);
			// ++nextSymbol;	
		//}

				// 	if (FONT[0][asciiUserIndexSymbol[nextSymbol]][nextLine][i] == FONT[0][asciiUserIndexSymbol[nextSymbol]][nextLine][i+1]) {
			// 	}
			// for (int i = 0; i < strlen(FONT[0][asciiUserIndexSymbol[nextSymbol]][nextLine]); ++i) {	


			// }