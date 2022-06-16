#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>

#define PAUSE_ENABLE 0

#include "main.h"

int main(int argc, char const *argv[]) {
    FILE* sourceFile = NULL;
    bool isNextValue = false;

    char userStr[MAX_USER_STR_SIZE];
    char font[aatParameters.SYMBOLS][aatParameters.SYMBOL_HEIGHT][aatParameters.SYMBOL_WIDTH];

    if (( sourceFile = fopen(setFont(aatParameters.font), "r") ) == NULL) {
        printf("\nError: %25s", "Can't open file\n");
        return EXIT_FAILURE;
    }
    
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (isNextValue == true) {
                if (isalpha(argv[i][0])) {
                    size_t size = strlen(argv[i]);
                    char userInput[size];
                    memccpy(userInput, argv[i], '\0', size);

                    if (( sourceFile = fopen(setFont(userInput), "r") ) == NULL) {
                        printf("\nError: %25s", "Can't open file\n");
                        return EXIT_FAILURE;
                    }

                } else if (isdigit(argv[i][0]) && atoi(argv[i]) > 29) {
                    size_t size = strlen(argv[i]);
                    char buf[size];
                    memccpy(buf, argv[i], '\0', size);
                    aatParameters.windowWidth = atoi(buf);  
                }

                isNextValue = false;
                continue;
            }   

            if (strcmp(argv[i], "--left") == 0 || strcmp(argv[i], "-l") == 0) {
                aatParameters.outputAlignment = LEFT;
                continue;
            }
            if (strcmp(argv[i], "--center") == 0 || strcmp(argv[i], "-c") == 0) {
                aatParameters.outputAlignment = CENTER;
                continue;
            }
            if (strcmp(argv[i], "--right") == 0 || strcmp(argv[i], "-r") == 0) {
                aatParameters.outputAlignment = RIGHT;
                continue;
            }
            if (strcmp(argv[i], "--padding1") == 0 || strcmp(argv[i], "-p1") == 0) {
                aatParameters.isPaddingEnable = ON;
                continue;
            }
            if (strcmp(argv[i], "--likeAcom1") == 0 || strcmp(argv[i], "-lk1") == 0) {
                aatParameters.isLikeAComment = ON;
                continue;
            }
            if (strcmp(argv[i], "--Red") == 0 || strcmp(argv[i], "--red") == 0) {
                aatParameters.color=RED;
                continue;
            }
            if (strcmp(argv[i], "--Green") == 0 || strcmp(argv[i], "--green") == 0) {
                aatParameters.color=GREEN;
                continue;
            }
            if (strcmp(argv[i], "--Yellow") == 0 || strcmp(argv[i], "--yellow") == 0) {
                aatParameters.color=YELLOW;
                continue;
            }
            if (strcmp(argv[i], "--Blue") == 0 || strcmp(argv[i], "--blue") == 0) {
                aatParameters.color = BLUE;
                continue;
            }
            if (strcmp(argv[i], "--Purple") == 0 || strcmp(argv[i], "--purple") == 0) {
                aatParameters.color = PURPLE;
                continue;
            }
            if (strcmp(argv[i], "--Cyan") == 0 || strcmp(argv[i], "--cyan") == 0) {
                aatParameters.color = CYAN;
                continue;
            }
            if (strcmp(argv[i], "--Black") == 0 || strcmp(argv[i], "--black") == 0) {
                aatParameters.color = BLACK;
                continue;
            }
            if (strcmp(argv[i], "--replace1") == 0 || strcmp(argv[i], "-rp1") == 0) {
                aatParameters.isChangeSpace = ON;
                continue;
            }
            if (strcmp(argv[i], "--smashing1") == 0 || strcmp(argv[i], "-s1") == 0) {
                aatParameters.isSmashing = ON;
                continue;
            }
            if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                printf("%s", reducedDocumentation);
                return EXIT_SUCCESS;
            }
            if (strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0) {
                isNextValue = true;
                continue;
            }
            if (strcmp(argv[i], "--font") == 0 || strcmp(argv[i], "-f") == 0) {
                isNextValue = true;
                continue;
            }
            if (isNextValue != true) {
                strcpy(userStr, argv[i]);
            }
        }    
    }
    
    parseData(sourceFile, font);
    fclose(sourceFile);

    if (argc == 1) {
        printf("Enter a string: ");
        scanf("%20[^\n]s", userStr);
    } 

    printAsciiArtText(userStr, font);
    
    #if PAUSE_ENABLE == ON
        #ifdef _WIN32
            system("pause");
        #endif
        #ifdef linux
            printf("Press X to win..."); //Press any key...
            int pause = getchar();
        #endif
    #endif

    return EXIT_SUCCESS;
}

const char* setFont(const char* argv) {
    static char fileToOpen[FONT_NAME_STR_SIZE+FONT_EXTENSION_LEN+FONTS_DIRECTION_LEN+1]; 
    char fileName[FONT_NAME_STR_SIZE];

    strcpy(fileName, argv);
    
    strcpy(fileToOpen, DEFAULT_FONTS_DIRECTORY);
    strcat(fileToOpen, fileName); 
    strcat(fileToOpen, DEFAULT_FONT_EXTENSION); 

    return fileToOpen;
}

void parseData(FILE* sourceFile, char font[aatParameters.SYMBOLS][aatParameters.SYMBOL_HEIGHT][aatParameters.SYMBOL_WIDTH]) { 
    char buf[aatParameters.SYMBOL_WIDTH];

    for (int s = 0; s < aatParameters.SYMBOLS; ++s) {
        for (int h = 0; h < aatParameters.SYMBOL_HEIGHT; ++h) {
            fgets(buf, aatParameters.SYMBOL_WIDTH, sourceFile);
            strcpy(buf, strtok(buf, "%"));
            strcpy(font[s][h], buf);
        }
    }
}

int printAsciiArtText(char* userStr, char font[aatParameters.SYMBOLS][aatParameters.SYMBOL_HEIGHT][aatParameters.SYMBOL_WIDTH]) {
    if (userStr[0] == 1) {
        return EXIT_SUCCESS;
    }
    if (strlen(userStr) == MAX_USER_STR_SIZE || strlen(userStr) > MAX_USER_STR_SIZE) {
        printf("String too long. Max len = %d\n", MAX_USER_STR_SIZE-1);
        return EXIT_FAILURE;
    }

    short asciiUserIndexSymbol[MAX_USER_STR_SIZE];
    unsigned short userStrSymbolCounts = strlen(userStr);
    
    char paddingSymbol;
    char replacedSymbol = '.';
    
    int totalAsciiStrWidth = 0;
    int savedSymbol = 0;
    int nextSymbol = 0;
    int nonAvaible = 0;
    int nextLine = 0;
    int spaces = 0;

    switch(aatParameters.color) {
        case RED    : printf(CSI"0;31m"); break;
        case GREEN  : printf(CSI"0;32m"); break;
        case YELLOW : printf(CSI"0;33m"); break;
        case BLUE   : printf(CSI"0;34m"); break;
        case PURPLE : printf(CSI"0;35m"); break;
        case CYAN   : printf(CSI"0;36m"); break;
        case BLACK  : printf(CSI"0;30m"); break;
        default     : printf(CSI"0m");    break;
    }

    if (aatParameters.isLikeAComment == ON) {
        printf("/***\n");
    }

    if (aatParameters.isChangeSpace == ON) {
        paddingSymbol = aatParameters.replacedSymbol;
    } else {
        paddingSymbol = ' ';
    }

    defineSymbols(userStrSymbolCounts, asciiUserIndexSymbol, userStr);

    for (int i = 0; i < userStrSymbolCounts; ++i) {
        if (aatParameters.isPaddingEnable == ON) {
            totalAsciiStrWidth += strlen(font[asciiUserIndexSymbol[i]][nextLine]) + 1;
            if (totalAsciiStrWidth > aatParameters.windowWidth) {
                nonAvaible++;
            }
        } else {
            totalAsciiStrWidth += strlen(font[asciiUserIndexSymbol[i]][nextLine]);
            if (totalAsciiStrWidth > aatParameters.windowWidth) {
                nonAvaible++;
            }
        }
    }

    if (totalAsciiStrWidth > 233 && totalAsciiStrWidth != 233) {
        printf("Change a last symbol. String is too long.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < aatParameters.SYMBOL_HEIGHT; ++i) {

        if (aatParameters.outputAlignment == CENTER) {for (int i = 0; i < (((round(aatParameters.windowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
        if (aatParameters.outputAlignment == RIGHT) {for (int i = 0; i < ((round(aatParameters.windowWidth - totalAsciiStrWidth))); ++i) {printf("%c", paddingSymbol);}}
        
        for (int i = 0; i < userStrSymbolCounts - nonAvaible; ++i) {
            for (int i = 0; i < strlen(font[asciiUserIndexSymbol[nextSymbol]][nextLine]); ++i) {
                if (aatParameters.isChangeSpace == ON && aatParameters.isSmashing == OFF) {
                    if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                        font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] = aatParameters.replacedSymbol;
                    }   
                }
                
                if (aatParameters.isSmashing == ON) {
                    int ip = ((i == 0)? 0 : (i-1));                 
                    char previousChar = font[asciiUserIndexSymbol[nextSymbol]][nextLine][ip];
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
                        if (aatParameters.isChangeSpace == ON && aatParameters.isSmashing == ON && isAllStringIsEmpty != 1) {
                            if (font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] == ' ') {
                                font[asciiUserIndexSymbol[nextSymbol]][nextLine][i] = replacedSymbol;
                            }   
                        }
                        printf("%c", font[asciiUserIndexSymbol[nextSymbol]][nextLine][i]);
                    }
                }

                if (aatParameters.isSmashing == OFF) {
                    printf("%c", font[asciiUserIndexSymbol[nextSymbol]][nextLine][i]);                        
                }
            }
            
            if (aatParameters.isPaddingEnable == ON) {
                printf("%c", paddingSymbol);
            } 

            ++nextSymbol;
            savedSymbol = nextSymbol;
        }

        printf("\n");
        ++nextLine;
        nextSymbol = 0;   
    }

    if (totalAsciiStrWidth > aatParameters.windowWidth) {
        int nonAvaibleSymbol = savedSymbol;

        for (int i = 0; i < aatParameters.SYMBOL_HEIGHT; ++i) {

            if (aatParameters.outputAlignment == CENTER) {for (int i = 0; i < (((round(aatParameters.windowWidth - totalAsciiStrWidth))/2)-3); ++i) {printf("%c", paddingSymbol);}}
            if (aatParameters.outputAlignment == RIGHT) {for (int i = 0; i < ((round(aatParameters.windowWidth - totalAsciiStrWidth))); ++i) {printf("%c", paddingSymbol);}}

            for (int i = 0; i < nonAvaible; ++i) {
                for (int i = 0; i < (((nonAvaibleSymbol == (nonAvaible-1))? strlen(font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine])-1 : strlen(font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine]))); ++i) {
                    if (aatParameters.isChangeSpace == ON) {
                        if (font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] == ' ') {
                            font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i] = aatParameters.replacedSymbol;
                        }   
                    }
                    printf("%c", font[asciiUserIndexSymbol[nonAvaibleSymbol]-1][nextLine][i]);    
                }

                if (aatParameters.isPaddingEnable == ON) {
                    printf("%c", paddingSymbol);
                } 

                ++nonAvaibleSymbol;
            }

            printf("\n");
            ++nextLine;
            nonAvaibleSymbol = savedSymbol;   
        }
    }

    if (aatParameters.isLikeAComment == ON) {
        printf("***/\n");
    }

    //Reset color Settings
    printf("\033[0m"); 

    return EXIT_SUCCESS;
}

void defineSymbols(unsigned short userStrSymbolCounts, short asciiUserIndexSymbol[MAX_USER_STR_SIZE], char userStr[MAX_USER_STR_SIZE]) {
    for (int csi = 0; csi < userStrSymbolCounts; ++csi) {
        #include "symbolsDefinition.ini"
    }
}