#ifndef HEADER
#define HEADER

//---------------------------------------------------------------------------------------
// Colors
//---------------------------------------------------------------------------------------

#define YELLOW "\x1b[33m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"

// Colors reset
#define RESET  "\x1b[0m"

//#define MYDEBUG

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

#endif
