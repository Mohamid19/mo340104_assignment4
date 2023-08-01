#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r) {
    int leftSize = m - l + 1;
    int rightSize = r - m;
    int leftArray[leftSize];
    int rightArray[rightSize];

    for (int i = 0; i < leftSize; ++i)
        leftArray[i] = pData[l + i];
    for (int i = 0; i < rightSize; ++i)
        rightArray[i] = pData[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            pData[k] = leftArray[i];
            ++i;
        } else {
            pData[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < leftSize) {
        pData[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < rightSize) {
        pData[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void mergeSortHelper(int pData[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(pData, l, m);
        mergeSortHelper(pData, m + 1, r);
        merge(pData, l, m, r);
    }
}

void mergeSort(int pData[], int l, int r) {
    extraMemoryAllocated += sizeof(int) * (r - l + 1);
    mergeSortHelper(pData, l, r);
}

void selectionSort(int* pData, int n) {
    extraMemoryAllocated = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (pData[j] < pData[minIndex])
                minIndex = j;
        }

        if (minIndex != i) {
            int temp = pData[i];
            pData[i] = pData[minIndex];
            pData[minIndex] = temp;
        }
    }
}

void insertionSort(int* pData, int n) {
    extraMemoryAllocated = 0;
    for (int i = 1; i < n; ++i) {
        int key = pData[i];
        int j = i - 1;
        while (j >= 0 && pData[j] > key) {
            pData[j + 1] = pData[j];
            --j;
            extraMemoryAllocated += sizeof(int);
        }
        pData[j + 1] = key;
    }
}

void bubbleSort(int* pData, int n) {
    extraMemoryAllocated = 0;
    for (int i = 0; i < n - 1; ++i) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; ++j) {
            if (pData[j] > pData[j + 1]) {
                int temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

int parseData(char* inputFileName, int** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d", &dataSz); // Remove \n from here
        *ppData = (int*)malloc(sizeof(int) * dataSz);

        for (int i = 0; i < dataSz; ++i) {
            fscanf(inFile, "%d", &(*ppData)[i]);
        }

        fclose(inFile);
        return dataSz;
    } else {
        printf("Error opening file: %s\n", inputFileName);
        return 0;
    }
}


void printArray(int pData[], int dataSz) {
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i = 0; i < 100; ++i) {
        printf("%d ", pData[i]);
    }
    printf("\n\t");

    for (i = sz; i < dataSz; ++i) {
        printf("%d ", pData[i]);
    }
    printf("\n\n");
}

int main(void) {
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

    for (i = 0; i < 3; ++i) {
        int* pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0) {
            printf("Unable to read data from file: %s\n", fileNames[i]);
            continue;
        }

        pDataCopy = (int*)malloc(sizeof(int) * dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSz);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }
}
