#include "header.h"

void QuickSort(char ** data, int leftIndex, int rightIndex, int (*Compare)(const void* a, const void* b)) {

    ASSERT(data);
    ASSERT(Compare);

    if ((rightIndex - leftIndex) < 1)
        return;

    int firstIndex = leftIndex;
    int lastIndex  = rightIndex;
    char * firstElem  = data[firstIndex];

    leftIndex++;

    while (leftIndex <= rightIndex) {

        ASSERT((leftIndex >= firstIndex && leftIndex <= lastIndex));
        ASSERT((rightIndex >= firstIndex && rightIndex <= lastIndex));

        char * leftElem  = data[leftIndex];
        char * rightElem = data[rightIndex];

        ASSERT((leftElem != NULL && rightElem != NULL));

        if (Compare((const void *)leftElem, (const void *)firstElem) > 0) {
            if (Compare((const void *)rightElem, (const void *)firstElem) < 0) {

                LOGGING("Call ChangePointers and send 1 elem = %p and second elem = %p", data[leftIndex], data[rightIndex]);
                ChangePointers(&data[leftIndex], &data[rightIndex]);
                LOGGING("Now 1 elem = %p, 2 elem = %p", data[leftIndex], data[rightIndex]);
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

    LOGGING("Call ChangePointers and send 1 elem = %p and second elem = %p", data[firstIndex], data[rightIndex]);
    ChangePointers(&data[firstIndex], &data[rightIndex]);
    LOGGING("Now 1 elem = %p, 2 elem = %p", data[firstIndex], data[rightIndex]);
    
    LOGGING("Call QuickSort and send leftIndex = %p, rightIndex = %p", firstIndex, rightIndex - 1);
    QuickSort(data, firstIndex, rightIndex - 1, Compare);
    LOGGING("Call QuickSort and send leftIndex = %p, rightIndex = %p", rightIndex + 1, lastIndex);
    QuickSort(data, rightIndex + 1, lastIndex, Compare);
}

void ChangePointers(char ** firstElem, char ** secondElem) {

    ASSERT(firstElem);
    ASSERT(secondElem);

    char * temp = *firstElem;
    *firstElem = *secondElem;
    *secondElem = temp;
}