#include "header.h"
#include <sys/types.h>
#include <sys/stat.h>

//! All used file information
struct FileStat {
    char * text_ptr = NULL;
    char ** index = {};
    off_t sizeInBytes = 0;
    size_t nLines = 0;
    unsigned int sizeOfElem = sizeof(char);
    char * readFrom = NULL;
    char * printTo  = NULL;
};

//! Get filenames from console (stdin)
int GetFilenameStd(int argc, char * argv[], FileStat * fileInfo);

//! Format validation
int CheckFileFormat(const char filename[], const char exp[]);

//! Fill buffer from file
int ReadFile(const char filename[], FileStat * fileInfo);

//! Get indexes and fill massiv of indexes
void FillIndexes(FileStat * fileInfo);
size_t StringsParser(char * buffer, char diffElem, char ** index);
size_t CountElems(const char * string, int Elem);

//! Printing
void PrintStrings(FILE * stream, char ** index_ptr, size_t nStrings);
void PrintErrno(const char filename[], int err_inf);
//! Clean file
void CleanFile(const char filename[]);

//! Comparators
int CompareUp(const size_t a, const size_t b);
int CompareAlpha(const void * Str1, const void * Str2);
int CompareAlphaReverse(const void * Str1, const void * Str2);
int CompareUpPtr(const void * ptr1, const void * ptr2);

//! Cool print
void PrintBeautyText(const char filename[], const char title[], FileStat fileInfo);
void SetBackground(const char htmlFilename[], const char ImageName[]);

int main(int argc, char * argv[]) {

    ASSERT(argv);
    ASSERT((argc > 0));

    FileStat fileInfo = {};

    if (!GetFilenameStd(argc, argv, &fileInfo)) return false;
    
    int readingResult = ReadFile(fileInfo.readFrom, &fileInfo);
    if (!readingResult) return false;



    QuickSort(fileInfo.index, 0, int(fileInfo.nLines-1), CompareAlpha);
    PrintBeautyText(fileInfo.printTo, "Sorted Onegin", fileInfo);
    qsort(fileInfo.index, fileInfo.nLines, sizeof(char *), CompareAlphaReverse);
    PrintBeautyText(fileInfo.printTo, "Reverse-sorted Onegin", fileInfo);
    qsort(fileInfo.index, fileInfo.nLines, sizeof(char *), CompareUpPtr);
    PrintBeautyText(fileInfo.printTo, "Standard Onegin", fileInfo);
    return true;
}

int GetFilenameStd(int argc, char * argv[], FileStat * fileInfo) {

    if ((argc == 5) && ((!strcmp(argv[1], "--readfile")  && !strcmp(argv[3], "--printfile")) ||
                        (!strcmp(argv[1], "--printfile") && !strcmp(argv[3], "--readfile")))) {
        if (!argv[2] || !argv[4]) return false;

        if (!strcmp(argv[1], "--readfile")  && !strcmp(argv[3], "--printfile")) {

            if (!(CheckFileFormat(argv[4], ".htm") || CheckFileFormat(argv[4], ".html") ||
                  CheckFileFormat(argv[4], ".txt"))) return false;

            (*fileInfo).readFrom = argv[2];
            (*fileInfo).printTo  = argv[4];
            CleanFile((*fileInfo).printTo);
            SetBackground((*fileInfo).printTo, "onegin_background.jpg");

            return true;
        }

        if (!CheckFileFormat(argv[2], ".htm") || !CheckFileFormat(argv[2], ".html") ||
            !CheckFileFormat(argv[2], ".txt")) return false;

        (*fileInfo).readFrom = argv[4];
        (*fileInfo).printTo  = argv[2];
        return true;
    }
    printf("\nError of reading stdin\n");
    return false;
}

int CheckFileFormat(const char filename[], const char exp[]) {

    if (strstr(filename, exp) != NULL) return true;
    
    printf(BOLD_RED "Incorrect format of file <%s>.\n" RESET, filename);
    printf(BOLD_RED "Expansion must be <%s>\n" RESET, exp);

    return false;
}

//! Splits the file's strings from fileInfo.text_ptr at a specified char - "diffElem" 
size_t StringsParser(char * buffer, char diffElem, char ** index) {
    
    ASSERT(buffer);
    ASSERT(index);

    char * currPtr = (char *)buffer;
    char * lastPtr = strchr(buffer, '\0');

    size_t indexPtr = 0;
    index[indexPtr++] = currPtr; // first string

    while ((currPtr <= lastPtr) && (*currPtr != '\0') && (currPtr != NULL)) {

        char * newPtr = strchr(currPtr, diffElem);
        //printf("NewPtr: %p", newPtr);

        if ((newPtr == NULL) || (newPtr > lastPtr)) {
            //printf("break\n");
            break;
        }
        currPtr = newPtr;
        *currPtr = '\0';

        index[indexPtr++] = currPtr+1;
        currPtr++;
    }

    return indexPtr;
}

void FillIndexes(FileStat * fileInfo) {

    ASSERT(fileInfo);
    ASSERT((*fileInfo).text_ptr);

    (*fileInfo).nLines = CountElems((*fileInfo).text_ptr, '\n');

    (*fileInfo).index = (char **)calloc((*fileInfo).nLines, sizeof(char *));

    StringsParser((*fileInfo).text_ptr, '\n', (*fileInfo).index);

}

size_t CountElems(const char * string, int Elem) {

    size_t count = 0;

    while ((*string != '\0') && (*string != EOF)) {

        if (*string == Elem) count++;
        string++;
    }

    return count;
}

void PrintErrno(const char filename[], int err_inf) {

    printf(RED "File: <%s>\n", filename);

    const char * errorMessage = strerror(err_inf);

    if (errorMessage) perror(errorMessage);
    printf(RESET);
}

int CompareAlpha(const void * Str1, const void * Str2) {

    ASSERT(Str1);
    ASSERT(Str2);

    const char * str1 = (const char *)Str1;
    const char * str2 = (const char *)Str2;

    size_t i = 0, j = 0;

    //size_t LenStr1 = strlen(str1);
    //size_t LenStr2 = strlen(str2);

    while ((str1[i] != '\0') && (str2[j] != '\0')) {

        ASSERT((i < strlen(str1)));
        ASSERT((j < strlen(str2)));

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

    return false;
}

int CompareAlphaReverse(const void * Str1, const void * Str2) {
    ASSERT(Str1);
    ASSERT(Str2);

    const char * str1 = *(const char * const *)Str1;
    const char * str2 = *(const char * const *)Str2;

    int i = (int)strlen(str1) - 1;
    int j = (int)strlen(str2) - 1;

    while (i >= 0) {
        if (isalpha((unsigned char)str1[i])) break;
        i--;
    }
    while (j >= 0) {
        if (isalpha((unsigned char)str2[j])) break;
        j--;
    }

    while (i >= 0 && j >= 0) {
        int a = tolower((unsigned char)str1[i]);
        int b = tolower((unsigned char)str2[j]);

        if (a != b) return a - b;

        do { i--; } while (i >= 0 && !isalpha((unsigned char)str1[i]));
        do { j--; } while (j >= 0 && !isalpha((unsigned char)str2[j]));
    }

    return i - j;
}

int CompareUp(const size_t a, size_t  b) {

    ASSERT(a);
    ASSERT(b);

    return (int)(a-b);
}

int CompareUpPtr(const void * ptr1, const void * ptr2) {
    const char * s1 = *(const char * const *)ptr1;
    const char * s2 = *(const char * const *)ptr2;

    uintptr_t p1 = (uintptr_t)s1;
    uintptr_t p2 = (uintptr_t)s2;

    if (p1 < p2) return -1;
    if (p1 > p2) return  1;

    return 0;
}

int ReadFile(const char filename[], FileStat * fileInfo) {

    ASSERT(filename);
    ASSERT(fileInfo);

    struct _stat fileStat = {};
    
    FILE * file_p = fopen(filename, "r");

    if (!file_p || (_stat(filename, &fileStat) == -1)) {
        PrintErrno((*fileInfo).readFrom, errno);
        return false;
    }

    (*fileInfo).sizeInBytes = fileStat.st_size;

    char * buffer = (char *)calloc((*fileInfo).sizeInBytes + (off_t)1, (*fileInfo).sizeOfElem);
    ASSERT(buffer);

    size_t lastIndex = fread((void *)buffer, (*fileInfo).sizeOfElem, (*fileInfo).sizeInBytes, file_p);
    buffer[lastIndex] = '\0';

    (*fileInfo).text_ptr = buffer;

    fclose(file_p);

    FillIndexes(fileInfo);

    return true;
}

void PrintStrings(FILE * stream, char ** index_ptr, size_t nStrings) {

    ASSERT(index_ptr);
    ASSERT(*index_ptr);

    for (size_t count = 0; count < nStrings; count++) {

        ASSERT(index_ptr[count]);
        fprintf(stream, "%s\n", index_ptr[count]);

    }
}



void PrintBeautyText(const char filename[], const char title[], FileStat fileInfo) {

    ASSERT(filename);
    ASSERT(title);
    ASSERT(fileInfo.text_ptr);
    ASSERT(fileInfo.index);
    ASSERT(fileInfo.text_ptr);

    FILE * file_p = fopen(filename, "a");
    if (!file_p) return;

    fprintf(file_p, "<pre>\n");

    fprintf(file_p, "<hr style=\"border: none; height: 2px; background-color: #333; width: 80%;\">");
    fprintf(file_p, "<h1 style=\"text-align: center; font-family: 'Times New Roman', Times, serif; font-size: 38px; "
                    "font-weight: bold; background: linear-gradient(45deg, #262729, #3f4040); -webkit-background-clip: text; "
                    "-webkit-text-fill-color: transparent; background-clip: text;\">%s</h1>\n", title);
    fprintf(file_p, "<hr style=\"border: none; height: 2px; background-color: #333; width: 80%;\">");
    fprintf(file_p, "<p style=\"text-align: center; font-family: 'Times New Roman', Times, serif;\">");
    PrintStrings(file_p, fileInfo.index, fileInfo.nLines);
    fprintf(file_p, "</p>\n");

    fclose(file_p);
}

void CleanFile(const char filename[]) {

    ASSERT(filename);
    fopen(filename, "w");

}

void SetBackground(const char htmlFilename[], const char ImageName[]) {

    ASSERT(htmlFilename);
    ASSERT(ImageName);

    FILE * file_p = fopen(htmlFilename, "a");

    fprintf(file_p, "<style>"
    "body { "
        "background-image: linear-gradient(rgba(255, 255, 255, 0.7), rgba(255, 255, 255, 0.7)), url('");
    fprintf(file_p, "%s", ImageName);
    fprintf(file_p, "');"
        "background-size: cover;"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-attachment: fixed;"
    "}"
    "</style>");

    fclose(file_p);
}