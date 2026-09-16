#include "header.h"

int ReadFromFile(const char filename[], const char ** index, size_t max_lines, size_t *nStrings);

void PrintStrings(const char ** index_ptr, size_t nStrings);

int CompareUp(const int a, const int b);
int CompareAlpha(const char * str1, const char * str2);

const size_t MAX_LEN_LINE = 5000;
const size_t MAX_N_LINES = 100;

const char OneginFilename[] = "onegin.txt";

int main() {

    const char * index[MAX_N_LINES] = {};
    size_t nLinesOnegin = 0;
    int reading_result = ReadFromFile(OneginFilename, index, MAX_LEN_LINE, &nLinesOnegin);
    if (reading_result == errno) return errno;

    PrintStrings(index, nLinesOnegin);
}

int CompareAlpha(const char * str1, const char * str2) {

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

int CompareUp(const int a, const int b) {

    ASSERT(a);
    ASSERT(b);
    ASSERT((a != b));

    // int A = *((const int *)a);
    // int B = *((const int *)b);

    return (a-b);
}

int ReadFromFile(const char filename[], const char ** index_ptr, size_t max_len, size_t *nStrings) {

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

void PrintStrings(const char ** index_ptr, size_t nStrings) {

    ASSERT(index_ptr);
    ASSERT(*index_ptr);

    for (size_t i = 0; i < nStrings; i++) {
        printf("%s\n", index_ptr[i]);
    }
}