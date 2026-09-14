#include "header.h"
#include <stdarg.h>

const char LOGFILE_NAME[] = "MyLogfile.txt";

void MY_LOGGING(const char * fileName, const char *funcName, unsigned int nLine,
                    const char * format, ...) {

    FILE *file_p = fopen(LOGFILE_NAME, "a");

    if (!file_p) {
         printf("Error opening file: <%s>\n", LOGFILE_NAME);
         return;
    }

    fprintf(file_p, "\n%s, time: %s\n", __DATE__, __TIME__);
    fprintf(file_p, "Я функция <%s> в файле <%s>.\n", funcName, fileName);

    va_list args;
    va_start(args, format);

    fprintf(file_p, "Сейчас я на строке %u, мое действие:\n", nLine);
    vfprintf(file_p, format, args);
    va_end(args);

    fclose(file_p);
}