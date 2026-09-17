#ifndef HEADER
#define HEADER

#include "C:\TX\TXLib.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

//---------------------------------------------------------------------------------------
// Colors
//---------------------------------------------------------------------------------------

#define YELLOW "\x1b[33m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define CYAN   "\x1b[36m"

#define BOLD_RED    "\x1b[1;31m"
#define BOLD_GREEN  "\x1b[1;32m"
#define BOLD_CYAN   "\x1b[1;36m"
#define BOLD_YELLOW "\x1b[1;33m"

// Colors reset
#define RESET  "\x1b[0m"

//#define MYDEBUG
//#define LOG_MODE

#ifdef MYDEBUG

#define ASSERT(right_instr) do { \
    if (!right_instr) { \
        fprintf(stderr, "\nAssertion failed: (%s), file <%s>, line: %d\n\n", #right_instr, __FILE__, __LINE__); \
        printf("Current function: %s\n", __PRETTY_FUNCTION__);\
        printf(RED "Link to the line:\n" RESET);          \
        printf("File: " __FILE__ ":%d:1:\n\n", __LINE__); \
        printf(RED "--------------------------------------------------" RESET); \
        abort(); \
    } \
} while (0)
#else
#define ASSERT(right_instr) do {} while(0)
#endif

#ifdef LOG_MODE

#define LOGGING(format, ...) MY_LOGGING(__FILE__, __PRETTY_FUNCTION__, __LINE__, format, ##__VA_ARGS__)

#else
#define LOGGING(format, ...) do {} while(0)

#endif

//----------------------------------------------------------------------------------------
//  Functions
//----------------------------------------------------------------------------------------

void MY_LOGGING(const char * fileName, const char *funcName, unsigned int nLine, const char * format, ...);

#endif