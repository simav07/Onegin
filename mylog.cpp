#include "header.h"
#include <stdarg.h>

//static
const char LOGFILE_NAME[] = "MyLogfile.txt";

void MY_LOGGING(const char * fileName, const char *funcName, unsigned int nLine,
                    const char * format, ...) {

    ASSERT(fileNmae);
    ASSERT(funcName);
    ASSERT(format);

    FILE *file_p = fopen(LOGFILE_NAME, "a");

    if (!file_p) {
        printf("Error opening file: <%s>\n", LOGFILE_NAME);
        return;
    }

    //fprintf(file_p, "\n%s, time: %s\n", __DATE__, __TIME__);
    fprintf(file_p, "\n--------------------------------------------------------");
    fprintf(file_p, "\nI'm function <%s> in <%s>.\n", funcName, fileName);

    va_list args;
    va_start(args, format);

    fprintf(file_p, "Now I'm on %u line, my action:\n", nLine);
    fprintf(file_p, "--------------------------------------------------------\n");
    vfprintf(file_p, format, args);
    fprintf(file_p, "\n");
    va_end(args);

    fclose(file_p);
}