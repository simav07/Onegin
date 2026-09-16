#include "header.h"

const char * MyStrstr(const char str1[], const char str2[]);

size_t MyGetline(char **buffer, size_t *n, FILE *from);

const int MAXBUFFER = 1000;

// first realisation
int MyStrlen(const char string[]) {

    ASSERT(string);

    int n_symb = 0;

    while (string[n_symb] != '\0') {
        n_symb++;
    }
    
    return n_symb;
}

// second realisation
int MyStrlenP(const char string[]) {

    ASSERT(string);

    const char * firstSymb_p = &string[0];

    while (*string != '\0') {
        string++;
    }
    
    return int(string - firstSymb_p);

}

int MyPuts(const char string[]) {

    ASSERT(string);

    while ((*string != '\0') && (*string != '\n')) {

        putc(*string, stdout);
        string++;
    }
    return 1;

}

size_t MyStrcpy(const char from[], char to[], size_t SizeOfTo) {

    ASSERT(from);
    ASSERT(to);
    ASSERT((from != to));

    size_t i = 0;  

    do {
        to[i] = from[i];
        i++;
    } while ((i < SizeOfTo) && (from[i] != '\0'));

    return i;
}

int MyStrcat(char MainString[], const char AddString[], int SizeOfMainString) {

    ASSERT(MainString);
    ASSERT(AddString);
    ASSERT((MainString != AddString));

    int LastSymbIndex = MyStrlen(MainString);
    int AddStringIndex = 0;

    // "dasd" "" 
    // "" ""
    // "" "dasd"
    while ((LastSymbIndex < SizeOfMainString) && (AddString[AddStringIndex] != '\0')) {

        MainString[LastSymbIndex] = AddString[AddStringIndex];
        AddStringIndex++;
        LastSymbIndex++;
    }

    return LastSymbIndex;
}

int MyStrcmp(const char FirstStr[], const char SecondStr[]) {

    ASSERT(FirstStr);
    ASSERT(SecondStr);

    int index = 0;
 
    while ((FirstStr[index] != '\0') || (SecondStr[index] != '\0')) {

        if ((int)FirstStr[index] != (int)SecondStr[index]) {

            return FirstStr[index] - SecondStr[index];

        }
        index++;

    }
    return 0;

}

char * MyStrdup(const char FromLine[]) {

    ASSERT(FromLine);

    int nBytes = MyStrlen(FromLine) + 1;

    char *NewLine = (char *)calloc(nBytes, sizeof(FromLine[0]));
    if (NewLine != NULL) {

        MyStrcpy(FromLine, NewLine, nBytes);
        return NewLine;

    }
    free(NewLine);

    return NULL;
}

const char * MyStrchr(const char string[], int chr_symb) {

    ASSERT(string);
    
    while ((*string != '\0') && (string != NULL)) {

        if ( (int)(*string) == chr_symb ) {
            return string;
        }

        string++;

    }

    return NULL;

}

const char * MyStrrchr(const char string[], int chr_symb) {

    ASSERT(string);
    ASSERT(isfinite(chr_symb));

    const char * p_LastSymb = NULL;

    while ((*string != '\0') && (string != NULL)) {

        if ( (int)(*string) == chr_symb ) {
            
            p_LastSymb = string;

        }

        string++;

    }

    return p_LastSymb;

}

const char * MyStrstr(const char str1[], const char str2[]) {

    ASSERT(str1);
    ASSERT(str2);

    int i = 0, j = 0;

    int LenStr2 = MyStrlen(str2);

    while (str1[i] != '\0') {

        for (j = 0; j < LenStr2; j++) {

            if (str1[i+j] != str2[j]) {
                break;
            }

            else if ((j + 1) == LenStr2) {
                return (str1 + i);
            }

            //printf("i = %d, j = %d, char1 = %c, char2 = %c\n", i+j, j, str1[i+j], str2[j]);

        }

        i++;

    }

    return NULL;

}

size_t MyGetline(char **buffer, size_t *n, FILE *from) {

    ASSERT(from);
    ASSERT(buffer);
    ASSERT(n);
    ASSERT(*buffer);

    int symb_char = 0;
    size_t length = 0;
    char * first_symb_ptr = *buffer;
    
    do {

        symb_char = fgetc(from);

        // if num of symbols in input line is bigger then max number of symbols in buffer
        if ( length >= *n ) {

            char * new_ptr = (char *)realloc(*buffer, *n + sizeof(char));

            if (new_ptr == NULL)
                return 0;

            // change the first_symb_ptr value if it is needed
            if (new_ptr != *buffer)
                first_symb_ptr = new_ptr;

            *buffer = new_ptr;
            *n = *n + sizeof(char);


        }
        
        first_symb_ptr[length] = (char)symb_char;
        length++;

    } while (symb_char != '\n' );

    first_symb_ptr[length+1] = '\n';

    printf("Output result: <%p>\n", *buffer);

    return length;

}