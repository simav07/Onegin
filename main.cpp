#include "header.h"

int ReadFromFile(const char filename[], char ** index, size_t max_lines, size_t *nStrings);

void PrintStrings(char ** index_ptr, size_t nStrings);

int CompareUp(const int a, const int b);
int CompareAlpha(const void * Str1, const void * Str2);
int CompareAlphaReverse(const void * Str1, const void * Str2);

const size_t MAX_LEN_LINE = 5000;
const size_t MAX_N_LINES = 100;

const char OneginFilename[] = "onegin.txt";

int main() {

    char * index[MAX_N_LINES] = {};
    size_t nLinesOnegin = 0;
    int reading_result = ReadFromFile(OneginFilename, index, MAX_LEN_LINE, &nLinesOnegin);
    if (reading_result == errno) return errno;
    

    printf("------------------STANDART---------------------\n");
    PrintStrings(index, nLinesOnegin);
    printf("--------------------------------------------------\n");

    printf(BOLD_YELLOW "------------------AFTER SORT----------------------\n\n" RESET);
    QuickSort(index, 0, nLinesOnegin-1, CompareAlpha);
    PrintStrings(index, nLinesOnegin);
    printf(BOLD_YELLOW "--------------------------------------------------\n" RESET);

    printf(BOLD_CYAN "---------------AFTER REVERSE SORT-----------------\n\n" RESET);
    qsort(index, nLinesOnegin, sizeof(char *), CompareAlphaReverse);
    PrintStrings(index, nLinesOnegin);
    printf(BOLD_CYAN "-------------------------------------\n" RESET);
}

int CompareAlpha(const void * Str1, const void * Str2) {

    const char * str1 = (const char *)Str1;
    const char * str2 = (const char *)Str2;

    ASSERT(str1);
    ASSERT(str2);

    size_t i = 0, j = 0;

    size_t LenStr1 = strlen(str1);
    size_t LenStr2 = strlen(str2);

    while ((str1[i] != '\0') && (str2[j] != '\0')) {

        ASSERT((i < LenStr1));
        ASSERT((j < LenStr2));

        if (!isalpha(str1[i])) {
            i++;
            continue;
        }
        if (!isalpha(str2[j])) {
            j++;
            continue;
        }

        int comp = CompareUp(tolower(str1[i]), tolower(str2[j]));
        
        if (comp != 0) return comp;

        i++;
        j++;
    }

    return 0;
}

int CompareAlphaReverse(const void * Str1, const void * Str2) {

    ASSERT(Str1);
    ASSERT(Str2);

    const char * str1 = *(const char **)Str1;
    const char * str2 = *(const char **)Str2;

    int LenStr1 = (int)strlen(str1);
    int LenStr2 = (int)strlen(str2);
    ASSERT((LenStr1 >= 0));
    ASSERT((LenStr2 >= 0));

    if ((LenStr1 <= 0) || (LenStr2 <= 0)) return 0;

    int i = LenStr1;
    int j = LenStr2;

    while ((i >= 0) && (j >= 0)) {

        ASSERT((i <= LenStr1));
        ASSERT((j <= LenStr2));

        if (!isalpha(str1[i])) {
            i--;
            continue;
        }
        if (!isalpha(str2[j])) {
            j--;
            continue;
        }
        ASSERT((i >= 0 && j >= 0));

        int comp = CompareUp(tolower(str1[i]), tolower(str2[j]));
        
        if (comp != 0) return comp;

        i--;
        j--;
    }
    return 0;
}

int CompareUp(const int a, const int b) {

    ASSERT(a);
    ASSERT(b);

    return (a-b);
}

int ReadFromFile(const char filename[], char ** index_ptr, size_t max_len, size_t *nStrings) {

    ASSERT(filename);
    ASSERT(index_ptr);

    FILE * file_p = fopen(filename, "r");
    if (!file_p) return errno;

    char buffer[MAX_LEN_LINE] = "";
    size_t curr_line = 0;

    while ((fgets(buffer, (int)max_len, file_p) != NULL) && (curr_line < MAX_N_LINES)) {
        index_ptr[curr_line++] = MyStrdup(buffer);
        (*nStrings)++;
    }

    fclose(file_p);
    return 1;
}

void PrintStrings(char ** index_ptr, size_t nStrings) {

    ASSERT(index_ptr);
    ASSERT(*index_ptr);

    for (size_t i = 0; i < nStrings; i++) {
        printf("%s\n", index_ptr[i]);
    }
}