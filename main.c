#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>

#define MAXUSERSTRSIZE (25+1) 

const unsigned short symbolWidth = 30;
const unsigned short symbolHeight = 10;
const unsigned short symbols = 95;

int printAsciiArtText(char* userStr, char font[symbols][symbolHeight][symbolWidth]);
void defineSymbols(unsigned short symbolCounts, short asciiUserIndexSymbol[MAXUSERSTRSIZE], char userStr[MAXUSERSTRSIZE]);
const char* setFont(int argc, const char* argv);
void parseData(int symbols, int symbolHeight, int symbolWidth, FILE* sourceFile, char font[symbols][symbolHeight][symbolWidth]);

char* reducedDocumentation = 
            "AAT - Ascii Art Text Generator\n"
            "\tThis utility create a cool visual ascii symbols\n"
            "Syntax: aat --option --option\"str\"\n\n"
            "1.ALL ARGUMENTS MUST BE SEPARATED BY SPACE --opt1 --opt2\n"
            "2.RECOMENDED USE \"\" FOR YOUR STRING ARGUMENT BUT YOU CAN USE JUST A SYMBOLS BUT WITHOUT SPACE\n\n"
            "All Options:\n"
            "\t--help print a reduced documentation for you\n"
            "\t--f \"fontName\" set a font for output string. Font name must be without .af extension. For example: --f test\n"
            "\t--p0 put Off space between symbols\n"
            "\t--p1 put On space between symbols\n"
            "\t--Red change output text color\n"
            "\t--Blue change output text color\n"
            "\t--Yellow change output text color\n"
            "\t--Cyan change output text color\n"
            "\t--Purple change output text color\n"
            "\t--Black change output text color\n"
            "\t--Green change output text color\n"
            "\t--l print output by left side\n"
            "\t--r print output by right side\n"
            "\t--c print output by center\n"
            "\tFor more information check a Documentaion file";

char* fileToOpen;
char* defaultFont = "Big";

int terminalWidth = 120;
int isNextValue = 0;
int isPaddingEnable = 1;
int color = 0;
int outputAlignment = 1; // 0 - left 1 - center 2 - right
int isLikeAComment = 0;
int isChangeSpace = 0;
int windowWidth = 120;
int isSmashing = 0; // beta

int main(int argc, char const *argv[]) {
    FILE* sourceFile = NULL;

    char userStr[MAXUSERSTRSIZE];
    char font[symbols][symbolHeight][symbolWidth];

    sourceFile = fopen(setFont(argc, defaultFont), "r");
    if (sourceFile == NULL) {printf("\nError: %25s", "Can't open file\n");return 1;}
    
    for (int i = 1; i < argc; ++i) {
        if (isNextValue == 1) {
            if ( isalpha(argv[i][0]) ) {
                size_t size = strlen(argv[i]);
                char userInput[size];
                memccpy(userInput, argv[i], '\0', size);

                sourceFile = fopen(setFont(argc, userInput), "r");
                if (sourceFile == NULL) {printf("\nError: %25s", "Can't open file\n");return 1;}
                free(fileToOpen);

            } else if (isdigit(argv[i][0]) && atoi(argv[i]) > 29) {
                size_t size = strlen(argv[i]);
                char buf[size];
                memccpy(buf, argv[i], '\0', size);
                windowWidth = atoi(buf);  
            }

            isNextValue = 0;
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
            && strcmp(argv[i], "--wt")     !=0
            && strcmp(argv[i], "--w")      !=0
            && strcmp(argv[i], "--s0")     !=0
            && strcmp(argv[i], "--s1")     !=0
            && isNextValue                 !=1 ) {
            
            for (int j = 0; j < strlen(argv[i]); ++j) {
                if (argc > 1 ) {
                    userStr[j] = argv[i][j];
                    userStr[strlen(argv[i])] = '\0';
                }
            }
        }

        if (strcmp(argv[i], "--c")==0) {outputAlignment = 1;}
        if (strcmp(argv[i], "--l")==0) {outputAlignment = 0;}
        if (strcmp(argv[i], "--r")==0) {outputAlignment = 2;}
        if (strcmp(argv[i], "--p0")==0) {isPaddingEnable = 0;}
        if (strcmp(argv[i], "--p1")==0) {isPaddingEnable = 1;}
        if (strcmp(argv[i], "--help")==0) {printf("%s",reducedDocumentation);return 0;}
        if (strcmp(argv[i], "--lk0")==0) {isLikeAComment = 0;}
        if (strcmp(argv[i], "--lk1")==0) {isLikeAComment = 1;}
        if (strcmp(argv[i], "--Red")==0) {color=1;}
        if (strcmp(argv[i], "--Green")==0) {color=2;}
        if (strcmp(argv[i], "--Yellow")==0) {color=3;}
        if (strcmp(argv[i], "--Blue")==0) {color=4;}
        if (strcmp(argv[i], "--Purple")==0) {color=5;}
        if (strcmp(argv[i], "--Cyan")==0) {color=6;}
        if (strcmp(argv[i], "--Black")==0) {color=7;}
        if (strcmp(argv[i], "--rp1")==0) {isChangeSpace=1;}
        if (strcmp(argv[i], "--rp0")==0) {isChangeSpace=0;}
        if (strcmp(argv[i], "--s0")==0) {isSmashing=0;}
        if (strcmp(argv[i], "--s1")==0) {isSmashing=1;}
        if (strcmp(argv[i], "--wt")==0) {windowWidth=terminalWidth;}
        if (strcmp(argv[i], "--w")==0) {
            isNextValue = 1;
            continue;
        }
        if (strcmp(argv[i], "--f")==0) {
            isNextValue = 1;
            continue;
        }
    }

    parseData(symbols, symbolHeight, symbolWidth, sourceFile, font);
    fclose(sourceFile);

    if (argc == 1) {
        printf("Enter a string: ");
        scanf("%20[^\n]s", userStr);
    } 

    printAsciiArtText(userStr, font);
    

    #ifdef _WIN32
        system("pause");
    #endif
    #ifdef linux
        printf("Press any key...");
        int pause = getchar();
    #endif

    return 0;
}

const char* setFont(int argc, const char* argv) {
    char fileName[16]; 

    if (argc == 1) {strcpy(fileName, "Big");} 
    else {strcpy(fileName, argv);}

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

int printAsciiArtText(char* userStr, char font[symbols][symbolHeight][symbolWidth]) {
    if (userStr[0] == 1) {return 0;}
    if (strlen(userStr) == MAXUSERSTRSIZE || strlen(userStr) > MAXUSERSTRSIZE) {
        printf("String too long. Max len = %d\n", MAXUSERSTRSIZE-1);
        return 0;
    }

    short asciiUserIndexSymbol[MAXUSERSTRSIZE];
    unsigned short symbolCounts = strlen(userStr);
    
    char paddingSymbol;
    char replacedSymbol = '.';
    
    int totalAsciiStrWidth = 0;
    int savedSymbol = 0;
    int nextSymbol = 0;
    int nonAvaible = 0;
    int nextLine = 0;
    int spaces = 0;

    switch(color) {
        case 1: printf("\033[0;31m"); break; // Red
        case 2: printf("\033[0;32m"); break; // Green
        case 3: printf("\033[0;33m"); break; // Yellow
        case 4: printf("\033[0;34m"); break; // Blue
        case 5: printf("\033[0;35m"); break; // Purple
        case 6: printf("\033[0;36m"); break; // Cyan
        case 7: printf("\033[0;30m"); break; // Black
        default: printf("\033[0m"); break;
    }

    if (isLikeAComment == 1) {printf("/***\n");}

    if (isChangeSpace == 1) {paddingSymbol = replacedSymbol;} 
    else {paddingSymbol = ' ';}

    defineSymbols(symbolCounts, asciiUserIndexSymbol, userStr);

    for (int i = 0; i < symbolCounts; ++i) {
        if (isPaddingEnable == 1) {
            totalAsciiStrWidth += strlen(font[asciiUserIndexSymbol[i]][nextLine]) + 1;
            if (totalAsciiStrWidth > windowWidth) {nonAvaible++;}
        } else {
            totalAsciiStrWidth += strlen(font[asciiUserIndexSymbol[i]][nextLine]);
            if (totalAsciiStrWidth > windowWidth) {nonAvaible++;}
        }
    }

    if (totalAsciiStrWidth > 233 && totalAsciiStrWidth != 233) {
        printf("Change a last symbol. String is too long.\n");
        return 0;
    }

    for (int i = 0; i < symbolHeight; ++i) {

        if(outputAlignment == 1) {for (int i = 0; i < (((round(windowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
        if(outputAlignment == 2) {for (int i = 0; i < ((round(windowWidth - totalAsciiStrWidth))); ++i) {printf("%c", paddingSymbol);}}
        
        for (int i = 0; i < symbolCounts-nonAvaible; ++i) {
            for (int i = 0; i < strlen(font[asciiUserIndexSymbol[nextSymbol]][nextLine]); ++i) {
                if (isChangeSpace == 1 && isSmashing == 0) {
                    if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                        font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] = replacedSymbol;
                    }   
                }
                
                if (isSmashing == 1) {
                    int ip = ((i == 0)? 0 : (i-1));                 
                    char previusChar = font[asciiUserIndexSymbol[nextSymbol]][nextLine][ip];
                    char currentChar = font[asciiUserIndexSymbol[nextSymbol]][nextLine][i];
                    
                    int skipEndSpaces = 0;
                    int skipStartSpaces = 0;

                    int isAllStringIsEmpty;
                    int canBeSmushed = 0;
                    int len = strlen( font[asciiUserIndexSymbol[nextSymbol]][nextLine]);
                    
                    for (int i = 0; i < len; ++i) {
                        if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] != ' ') {
                            skipEndSpaces = 0;
                        }
                        if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                            ++skipEndSpaces;    
                        }
                    }

                    for (int i = 0; i < len; ++i) {
                        if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] != ' ') {
                            break;
                        }
                        if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                            ++skipStartSpaces;
                        }
                    }

                    for (int i = 0; i < len; ++i) {
                        isAllStringIsEmpty = 0;
                        int spaces = 0;

                        if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                            ++spaces;
                        }
                        if (spaces == len) {
                            isAllStringIsEmpty=1;
                        }
                    }
                        
                    if (i < skipStartSpaces && nextSymbol != 0 && isAllStringIsEmpty != 1) {
                        continue;
                    } else if (i > len-skipEndSpaces-1) {
                        continue;
                    } else {
                        if (isChangeSpace == 1 && isSmashing == 1 && isAllStringIsEmpty != 1) {
                            if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                                font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] = replacedSymbol;
                            }   
                        }
                        printf("%c", font[asciiUserIndexSymbol[nextSymbol]][nextLine][i]);
                    }
                }

                if (isSmashing == 0) {
                    printf("%c", font[asciiUserIndexSymbol[nextSymbol]][nextLine][i]);                        
                }
            }
            
            if (isPaddingEnable == 1) {printf("%c", paddingSymbol);} 

            ++nextSymbol;
            savedSymbol = nextSymbol;
        }

        printf("\n");
        ++nextLine;
        nextSymbol=0;   
    }

    if (totalAsciiStrWidth > windowWidth) {
        int nonAvaibleSymbol = savedSymbol;

        for (int i = 0; i < symbolHeight; ++i) {

            if(outputAlignment==1) {for (int i = 0; i < (((round(windowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
            if(outputAlignment==2) {for (int i = 0; i < ((round(windowWidth - totalAsciiStrWidth))); ++i) {printf("%c", paddingSymbol);}}

            for (int i = 0; i < nonAvaible; ++i) {
                for (int i = 0; i < (((nonAvaibleSymbol == (nonAvaible-1))? strlen(font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine])-1 : strlen(font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine]))); ++i) {
                    if (isChangeSpace == 1) {
                        if (font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] == ' ') {
                            font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] = replacedSymbol;
                        }   
                    }
                    printf("%c", font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i]);    
                }
            
                if (isPaddingEnable == 1) {printf("%c", paddingSymbol);} 

                    ++nonAvaibleSymbol;
                }

                printf("\n");
                ++nextLine;
                nonAvaibleSymbol = savedSymbol;   
            }
        }

    if (isLikeAComment == 1) {printf("***/\n");}

    //Reset color Settings
    printf("\033[0m"); 
}

void defineSymbols(unsigned short symbolCounts, short asciiUserIndexSymbol[MAXUSERSTRSIZE], char userStr[MAXUSERSTRSIZE]) {
    for (int csi = 0; csi < symbolCounts; ++csi) {
        #include "symbolsDefinition.ini"
    }
}