#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <windows.h>
  #define sleep_ms(ms) Sleep(ms)
  #define CLEAR_SCREEN "cls"
#else
  #include <unistd.h>
  #define sleep_ms(ms) usleep((ms) * 1000)
  #define CLEAR_SCREEN "clear"
#endif

#define SIZE 8

// Terminal visualizer showing array state, current active range, pivot, and scanning pointers
void visualizeStep(int arr[], int size, int low, int high, int pivotIdx, int iIdx, int jIdx) {
    system(CLEAR_SCREEN);
    printf("=== Quick Sort Visualizer ===\n");
    printf("Range: [%d..%d] | Pivot Value: %d at Index [%d]\n\n", low, high, arr[pivotIdx], pivotIdx);

    for (int k = 0; k < size; k++) {
        printf("Index [%d] | Value: %2d | ", k, arr[k]);
        
        for (int b = 0; b < arr[k]; b++) {
            printf("#");
        }

        if (k == pivotIdx) {
            printf(" <-- PIVOT");
        } else if (k == jIdx) {
            printf(" <-- Scanning (j)");
        } else if (k == iIdx) {
            printf(" <-- Smaller Boundary (i)");
        }
        printf("\n");
    }
    printf("\n");
}

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition Function
int partition(int arr[], int low, int high, int totalSize) {
    int pivot = arr[high]; // Select last element as pivot
    int i = (low - 1);     // Index of smaller element boundary

    for (int j = low; j <= high - 1; j++) {
        visualizeStep(arr, totalSize, low, high, high, i, j);
        sleep_ms(350);

        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Increment boundary of smaller elements
            swap(&arr[i], &arr[j]);
            visualizeStep(arr, totalSize, low, high, high, i, j);
            sleep_ms(350);
        }
    }

    // Place pivot at its correct sorted position (i + 1)
    swap(&arr[i + 1], &arr[high]);
    visualizeStep(arr, totalSize, low, high, i + 1, -1, -1);
    sleep_ms(400);

    return (i + 1); // Return pivot's index
}

// Recursive Quick Sort function
void quickSort(int arr[], int low, int high, int totalSize) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high, totalSize);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1, totalSize);
        quickSort(arr, pi + 1, high, totalSize);
    }
}

int main() {
    int data[SIZE] = {24, 9, 29, 14, 19, 27, 15, 3};

    printf("Starting Quick Sort...\n");
    printf("Press Enter to start...");
    getchar();

    quickSort(data, 0, SIZE - 1, SIZE);

    // Final state display
    system(CLEAR_SCREEN);
    printf("=== Quick Sort Visualizer ===\n");
    printf("SORTING COMPLETE!\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d] | Value: %2d [SORTED]\n", i, data[i]);
    }

    return 0;
}