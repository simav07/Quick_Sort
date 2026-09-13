#include "C:\TX\TXLib.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define MYDEBUG
#include "header.h"

void QuickSort(int * data, int leftIndex, int rightIndex, int (*Compare)(const void* a, const void* b));

void ChangeValues(int * firstElem, int * secondElem);

int MakeGraph();

int GetRandomIntNumber();

void StartTest();

int WriteSortedNumbsFile(char filename[], int * data, size_t nElems, size_t countOfRepeats);

void DrawPoint(double x, double y);

void DrawAxes(int SizeX, int SizeY);

void BubbleSort(int * data, size_t nElems);

void PrintIntMass(int * data, size_t nElems);

int CompareUp(const void * a, const void * b);
int CompareDown(const void * a, const void *b);

size_t COUNT_OF_REPEATS_QUICK  = 0;
size_t COUNT_OF_REPEATS_BUBBLE = 0;

// coeffs for window size
const double kx = 1.6, ky = 0.3;

const int WindowSizeX = 1200;
const int WindowSizeY = 800;

const int StartOX_y = 3 * WindowSizeY / 4;
const int StartOY_x = WindowSizeX / 8;

const char FileForQuick[] = "SortedNumsQuick.txt";

const int N_MAX = 500;

int main(int argc, char * argv[]) {

    ASSERT(argv);

    if ((argc == 2) && strcmp(argv[0], "--test")) {
        MakeGraph();
    }
    else {
        int data[] = {10, 40, 20, 22, 5};
        size_t nElems = sizeof(data)/sizeof(data[0]);
        QuickSort(data, 0, nElems - 1, &CompareUp);
        PrintIntMass(data, nElems);
    }

    return 0;
}

void QuickSort(int * data, int leftIndex, int rightIndex, int (*Compare)(const void* a, const void* b)) {

    ASSERT(data);
    
    COUNT_OF_REPEATS_QUICK++;

    if ((rightIndex - leftIndex) < 1)
        return;

    int firstIndex = leftIndex;
    int lastIndex  = rightIndex;
    int firstElem  = data[firstIndex];

    leftIndex++;

    while (leftIndex <= rightIndex) {

        int leftElem  = data[leftIndex];
        int rightElem = data[rightIndex];

        if (leftElem > firstElem) {
            if (rightElem < firstElem) {

                ChangeValues(&data[leftIndex], &data[rightIndex]);
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

    ChangeValues(&data[firstIndex], &data[rightIndex]);
    
    QuickSort(data, firstIndex, rightIndex - 1, &CompareUp);
    QuickSort(data, rightIndex + 1, lastIndex, &CompareUp);
}

void ChangeValues(int * firstElem, int * secondElem) {

    ASSERT(firstElem);
    ASSERT(secondElem);

    int temp = *firstElem;
    *firstElem = *secondElem;
    *secondElem = temp;

}

void DrawPoint(double x, double y) {

    // Пересчет математических координат в программные (для окна)

    x = (double)StartOY_x + kx * x;
    y = (double)StartOX_y - ky * y;
    txCircle(x, y, 1.75);

}

void DrawAxes(int SizeX, int SizeY) {

    //! Axe OX
    double X_x0 = 10;
    double X_y0 = StartOX_y;
    double X_x1 = SizeX - 10;
    double X_y1 = X_y0;

    //! Axe OY
    double Y_x0 = StartOY_x;
    double Y_y0 = 10;
    double Y_x1 = Y_x0;
    double Y_y1 = SizeY - 10;

    //! Draw axes
    txLine(X_x0, X_y0, X_x1, X_y1);
    txLine(X_x1 - 15, X_y1 + 10, X_x1, X_y1);
    txLine(X_x1 - 15, X_y1 - 10, X_x1, X_y1);

    txLine(Y_x0, Y_y0, Y_x1, Y_y1);
    txLine(Y_x1 - 10, Y_y0 + 15, Y_x1, Y_y0);
    txLine(Y_x1 + 10, Y_y0 + 15, Y_x1, Y_y0);
}

void StartTest() {

    for (size_t N = 3; N < N_MAX; N++) {

        COUNT_OF_REPEATS_QUICK  = 0;
        COUNT_OF_REPEATS_BUBBLE = 0;

        int * data_quick = (int *)calloc(N, sizeof(int));
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

        //DrawPoint((double)N, f_sort);
        DrawPoint((double)N, (double)COUNT_OF_REPEATS_QUICK);

        char * fileQuick = "SortedNumsQuick.txt";

        WriteSortedNumbsFile(fileQuick, data_quick, N, COUNT_OF_REPEATS_QUICK);

        BubbleSort(data_bubble, N);

        //double f_bubble = double(N * N);
        
        txSetColor(TX_RED, 4);
        DrawPoint((double)N, (double)COUNT_OF_REPEATS_BUBBLE);

        txSetColor(TX_BLACK, 4);
        WriteSortedNumbsFile("SortedNumsBubble.txt", data_bubble, N, COUNT_OF_REPEATS_BUBBLE);

        free(data_quick);
        free(data_bubble);

        //printf("N = %llu: %llu repeats\n", N, COUNT_OF_REPEATS_QUICK);
        //PrintMass(data, N);
    }
}

int WriteSortedNumbsFile(char filename[], int * data, size_t nElems, size_t countOfRepeats) {

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


int GetRandomIntNumber() {

    int numb = rand() % 100;
    return numb;

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

void BubbleSort(int * data, size_t nElems) {

    ASSERT(data);

    for (size_t i = 0; i < nElems - 1; i++) {
        bool swapped = false;
        
        for (size_t j = 0; j < nElems - i - 1; j++) {
            COUNT_OF_REPEATS_BUBBLE++;

            if (data[j] > data[j + 1]) {

                ChangeValues(&data[j], &data[j+1]);
                swapped = true;
            }
        }
        
        if (!swapped) {
            break;
        }
    }
}

void PrintIntMass(int * data, size_t nElems) {

    ASSERT(data);

    for (size_t i = 0; i < nElems; i++) {

        printf("%d ", data[i]);

    }

}

int CompareUp(const void * a, const void * b) {

    int A = *((const int *)a);
    int B = *((const int *)b);

    return (A-B);
}