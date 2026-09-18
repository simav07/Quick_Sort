#include "header.h"

// Algorithms
void QuickSort(int * data, int leftIndex, int rightIndex, int (*Compare)(const void* a, const void* b));
void BubbleSort(int * data, size_t nElems, int (*Compare)(const void* a, const void* b));

// Comparators
int CompareUp(const void * a, const void * b);
int CompareDown(const void * a, const void *b);

// Algorithm complexity test mode
void StartTest();
int MakeGraph();
void DrawPoint(double x, double y);
void DrawAxes(int SizeX, int SizeY);
int WriteSortedNumbsFile(const char filename[], int * data, size_t nElems, size_t countOfRepeats);

// Standard stdout print
void PrintIntMass(int * data, size_t nElems);

// Debug ColoredPrint
int PrintColorData(const char message[], int * data, int firstIndex, int lastIndex, int leftIndex, int rightIndex, size_t nElems);
void ChangeValues(int * firstElem, int * secondElem);
int GetRandomIntNumber();

size_t COUNT_OF_REPEATS_QUICK  = 0;
size_t COUNT_OF_REPEATS_BUBBLE = 0;

// Coeffs for window size
const double kx = 1.6, ky = 0.3;

const int WindowSizeX = 1200;
const int WindowSizeY = 800;

const int StartOX_y = 3 * WindowSizeY / 4;
const int StartOY_x = WindowSizeX / 8;

const char FileForQuick[]  = "SortedNumsQuick.txt";
const char FileForBubble[] = "SortedNumsBubble.txt";

const int N_MAX = 500;

int main(int argc, char * argv[]) {

    ASSERT(argv);

    if ((argc == 2) && strcmp(argv[0], "--test")) {
        LOGGING("Запущен режим вычисления сложности алгоритмов");
        MakeGraph();
    }
    else {
        int data[] = {40, 20, 30, 50, 70, 80, 10};
        size_t nElems = sizeof(data)/sizeof(data[0]);

        QuickSort(data, 0, int(nElems - 1), &CompareUp);
        // BubbleSort(data, sizeof(data)/sizeof(data[0]), &CompareUp);
        PrintIntMass(data, nElems);
    }

    LOGGING("Программа завершена без ошибок");
    return 0;
}

void QuickSort(int * data, int leftIndex, int rightIndex, int (*Compare)(const void* a, const void* b)) {

    ASSERT(data);
    ASSERT(Compare);
    
    COUNT_OF_REPEATS_QUICK++;

    if ((rightIndex - leftIndex) < 1)
        return;

    size_t nElems = (rightIndex - leftIndex) + 1;
    int firstIndex = leftIndex;
    int lastIndex  = rightIndex;
    int * firstElem  = data + firstIndex;

    leftIndex++;

    while (leftIndex <= rightIndex) {

        ASSERT((leftIndex >= firstIndex && leftIndex <= lastIndex));
        ASSERT((rightIndex >= firstIndex && rightIndex <= lastIndex));

        int * leftElem  = data + leftIndex;
        int * rightElem = data + rightIndex;

        PrintColorData("Checking numbers...", data, firstIndex, lastIndex, leftIndex, rightIndex, nElems);

        ASSERT((leftElem != NULL && rightElem != NULL));

        if (Compare((void *)leftElem, (void *)firstElem) > 0) {
            if (Compare((void *)rightElem, (void *)firstElem) < 0) {

                LOGGING("Вызываю ChangeValues и передаю туда первый элемент - %d и второй - %d", data[firstIndex], data[rightIndex]);
                ChangeValues(&data[leftIndex], &data[rightIndex]);
                PrintColorData("Elements have been changed", data, firstIndex, lastIndex, leftIndex, rightIndex, nElems);
                LOGGING("Теперь первый - %d, второй - %d", data[leftIndex], data[rightIndex]);
                leftIndex++;
                rightIndex--;
            }
            else {
                rightIndex--;
            }
        }
        else {
            leftIndex++;
        }
    }

    LOGGING("Вызываю ChangeValues и передаю туда первый элемент - %d и второй - %d", data[firstIndex], data[rightIndex]);
    PrintColorData("Checking numbers...", data, firstIndex, lastIndex, leftIndex, rightIndex, nElems);
    ChangeValues(&data[firstIndex], &data[rightIndex]);
    PrintColorData("Checking numbers...", data, firstIndex, lastIndex, leftIndex, rightIndex, nElems);
    LOGGING("Теперь первый - %d, второй - %d", data[firstIndex], data[rightIndex]);
    
    LOGGING("Вызываю QuickSort и передаю туда leftIndex = %d, rightIndex = %d", firstIndex, rightIndex - 1);
    QuickSort(data, firstIndex, rightIndex - 1, Compare);
    LOGGING("Вызываю QuickSort и передаю туда leftIndex = %d, rightIndex = %d", rightIndex + 1, lastIndex);
    QuickSort(data, rightIndex + 1, lastIndex, Compare);
}

int PrintColorData(const char message[], int * data, int firstIndex, int lastIndex, int leftIndex, int rightIndex, size_t nElems) {
#ifdef MYDEBUG
    // Bold Green - first elem for comparison
    // Cyan       - already sorted on the left side
    // Bold Cyan  - current left index
    // Bold Red   - current right index
    // Red        - already sorted on the right side

    ASSERT(data);
    ASSERT((nElems > 0));
    // guard
    if (firstIndex < 0 || (lastIndex - firstIndex) >= (int)nElems || firstIndex > lastIndex || rightIndex <= firstIndex || nElems < 3 || rightIndex > lastIndex)
        return 0;
    
    if (leftIndex > rightIndex) ChangeValues(&leftIndex, &rightIndex);
    
    printf(BOLD_YELLOW "\n--------------------------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW ">>>[ %s ]\n\n" RESET, message);
    for (int c = firstIndex; c < (int)(nElems + firstIndex); c++) {
        if (c == leftIndex && c == rightIndex) printf("[LR]\t");
        else if (c == leftIndex) printf("[L]\t");
        else if (c == rightIndex) printf("[R]\t");
        else printf("---\t");
    }
    printf("\n");
    
    size_t i = firstIndex;
    
    printf(GREEN "%3d\t" RESET, data[i++]);
    
    while ((int)i < leftIndex && (int)i < rightIndex && (int)i <= lastIndex) {
        printf(CYAN "%3d\t" RESET, data[i++]);
    }

    if ((int)i == leftIndex && (int)i <= lastIndex) {
        if ((int)i == rightIndex) {
            printf(BOLD_RED "%3d\t" RESET, data[i++]); // Если совпали на N=2/3 - RED
        } else {
            printf(BOLD_CYAN "%3d\t" RESET, data[i++]);
        }
    }
    
    while (((int)i > leftIndex) && ((int)i < rightIndex) && (int)i <= lastIndex) {
        printf("%3d\t", data[i++]);
    }
    
    if ((int)i == rightIndex && (int)i <= lastIndex) {
        printf(BOLD_RED "%3d\t" RESET, data[i++]);
    }
    
    while (((int)i <= lastIndex)) {
        printf(RED "%3d\t" RESET, data[i++]);
    }
    printf(YELLOW "\n\n--------------------------------------------------------------------\n" RESET);
    printf("\nPlease tap <Enter> to continue\n");
    int cont_flag = 0;
    while ((cont_flag = (int)getchar()) != '\n') continue;
    return 1;
#else
    return 0;
#endif
}

void BubbleSort(int * data, size_t nElems, int (*Compare)(const void* a, const void* b)) {

    ASSERT(data);

    for (size_t i = 0; i < nElems - 1; i++) {
        bool swapped = false;
        
        for (size_t j = 0; j < nElems - i - 1; j++) {
            COUNT_OF_REPEATS_BUBBLE++;

            if (Compare(data + j, data + j + 1) > 0) {

                ChangeValues(&data[j], &data[j+1]);
                swapped = true;
            }
        }
        
        if (!swapped) {
            break;
        }
    }
}

int CompareUp(const void * a, const void * b) {

    ASSERT(a);
    ASSERT(b);
    ASSERT((a != b));

    int A = *((const int *)a);
    int B = *((const int *)b);

    return (A-B);
}

int CompareDown(const void * a, const void * b) {

    ASSERT(a);
    ASSERT(b);
    ASSERT((a != b));

    int A = *((const int *)a);
    int B = *((const int *)b);

    return (B-A);
}

void StartTest() {

    for (size_t N = 3; N < N_MAX; N++) {

        COUNT_OF_REPEATS_QUICK  = 0;
        COUNT_OF_REPEATS_BUBBLE = 0;

        int * data_quick =  (int *)calloc(N, sizeof(int));
        int * data_bubble = (int *)calloc(N, sizeof(int));

        ASSERT(data_quick);
        ASSERT(data_bubble);

        for (size_t i = 0; i < N; i++) {
            int randomElem = GetRandomIntNumber();
            *(data_quick + i) = randomElem;
            *(data_bubble + i) = randomElem;
        }

        QuickSort(data_quick, 0, (int)N-1, &CompareUp);

        //double f_sort = N * (log( (double) N) / log(2.0));

        DrawPoint((double)N, (double)COUNT_OF_REPEATS_QUICK);

        WriteSortedNumbsFile(FileForQuick, data_quick, N, COUNT_OF_REPEATS_QUICK);

        BubbleSort(data_bubble, N, &CompareUp);

        //double f_bubble = double(N * N);
        
        txSetColor(TX_RED, 4);
        DrawPoint((double)N, (double)COUNT_OF_REPEATS_BUBBLE);

        txSetColor(TX_BLACK, 4);
        WriteSortedNumbsFile(FileForBubble, data_bubble, N, COUNT_OF_REPEATS_BUBBLE);

        free(data_quick);
        free(data_bubble);

    }
}

int WriteSortedNumbsFile(const char filename[], int * data, size_t nElems, size_t countOfRepeats) {

    ASSERT(filename);
    ASSERT(data);

    FILE *file_p = fopen(filename, "a");
    if (!file_p) {
        printf("Error opening file: <%s>\n", filename);
        return 0;
    }

    fprintf(file_p, "N = %llu, Repeats = %llu\n", nElems, countOfRepeats);

    for (size_t i = 0; i < nElems; i++) {

     fprintf(file_p, "%d ", data[i]);
    
    }
    fprintf(file_p, "\n");

    fclose(file_p);
    return 1;
}
   
int MakeGraph() {

    system("cls");

    txCreateWindow(WindowSizeX, WindowSizeY);
    txSetColor(TX_BLACK, 4);

    txBegin();
    txClear(txDC());

    DrawAxes(WindowSizeX, WindowSizeY);
    StartTest();
    
    txRedrawWindow();
    txEnd();
        
    return 0;
}

void ChangeValues(int * firstElem, int * secondElem) {

    ASSERT(firstElem);
    ASSERT(secondElem);

    int temp = *firstElem;
    *firstElem = *secondElem;
    *secondElem = temp;
}

void PrintIntMass(int * data, size_t nElems) {

    ASSERT(data);

    for (size_t i = 0; i < nElems; i++) {

        printf("%d ", data[i]);

    }
}

int GetRandomIntNumber() {

    int numb = rand() % 100;
    return numb;
}

void DrawPoint(double x, double y) {

    // Draw using maths coordinates
    x = (double)StartOY_x + kx * x;
    y = (double)StartOX_y - ky * y;
    txCircle(x, y, 1.75);
}

void DrawAxes(int SizeX, int SizeY) {

    // Axe OX
    double X_x0 = 10;
    double X_y0 = StartOX_y;
    double X_x1 = SizeX - 10;
    double X_y1 = X_y0;

    // Axe OY
    double Y_x0 = StartOY_x;
    double Y_y0 = 10;
    double Y_x1 = Y_x0;
    double Y_y1 = SizeY - 10;

    // Draw axes
    txLine(X_x0, X_y0, X_x1, X_y1);
    txLine(X_x1 - 15, X_y1 + 10, X_x1, X_y1);
    txLine(X_x1 - 15, X_y1 - 10, X_x1, X_y1);

    txLine(Y_x0, Y_y0, Y_x1, Y_y1);
    txLine(Y_x1 - 10, Y_y0 + 15, Y_x1, Y_y0);
    txLine(Y_x1 + 10, Y_y0 + 15, Y_x1, Y_y0);
}