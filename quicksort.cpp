#include "header.h"

void QuickSort(int * data, int leftIndex, int rightIndex, int (*Compare)(const void* a, const void* b)) {

    ASSERT(data);
    ASSERT(Compare);

    if ((rightIndex - leftIndex) < 1)
        return;

    int firstIndex = leftIndex;
    int lastIndex  = rightIndex;
    int * firstElem  = data + firstIndex;

    leftIndex++;

    while (leftIndex <= rightIndex) {

        ASSERT((leftIndex >= firstIndex && leftIndex <= lastIndex));
        ASSERT((rightIndex >= firstIndex && rightIndex <= lastIndex));

        int * leftElem  = data + leftIndex;
        int * rightElem = data + rightIndex;

        ASSERT((leftElem != NULL && rightElem != NULL));

        if (Compare((void *)leftElem, (void *)firstElem) > 0) {
            if (Compare((void *)rightElem, (void *)firstElem) < 0) {

                LOGGING("Call ChangeValues and send 1 elem = %d and second elem = %d", data[firstIndex], data[rightIndex]);
                ChangeValues(&data[leftIndex], &data[rightIndex]);
                LOGGING("Now 1 elem = %d, 2 elem = %d", data[leftIndex], data[rightIndex]);
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

    LOGGING("Call ChangeValues and send 1 elem = %d and second elem = %d", data[firstIndex], data[rightIndex]);
    ChangeValues(&data[firstIndex], &data[rightIndex]);
    LOGGING("Now 1 elem = %d, 2 elem = %d", data[firstIndex], data[rightIndex]);
    
    LOGGING("Call QuickSort and send leftIndex = %d, rightIndex = %d", firstIndex, rightIndex - 1);
    QuickSort(data, firstIndex, rightIndex - 1, Compare);
    LOGGING("Call QuickSort and send leftIndex = %d, rightIndex = %d", rightIndex + 1, lastIndex);
    QuickSort(data, rightIndex + 1, lastIndex, Compare);
}

void ChangeValues(int * firstElem, int * secondElem) {

    ASSERT(firstElem);
    ASSERT(secondElem);

    int temp = *firstElem;
    *firstElem = *secondElem;
    *secondElem = temp;
}