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

// Visualizer showing sorted boundary, current minimum, and scanning pointer
void visualizeStep(int arr[], int size, int sortedIdx, int currentMinIdx, int checkingIdx) {
    system(CLEAR_SCREEN);
    printf("=== Selection Sort Visualizer ===\n");
    printf("Sorted Boundary: Index [0] to [%d]\n\n", sortedIdx - 1);

    for (int i = 0; i < size; i++) {
        printf("Index [%d] | Value: %2d | ", i, arr[i]);
        
        for (int k = 0; k < arr[i]; k++) {
            printf("#");
        }

        if (i < sortedIdx) {
            printf(" [SORTED]");
        } else if (i == currentMinIdx) {
            printf(" <-- CURRENT MIN");
        } else if (i == checkingIdx) {
            printf(" <-- Scanning");
        }
        printf("\n");
    }
    printf("\n");
}

// Selection Sort Implementation
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < size; j++) {
            visualizeStep(arr, size, i, min_idx, j);
            sleep_ms(350);

            if (arr[j] < arr[min_idx]) {
                min_idx = j; // Found new minimum
                visualizeStep(arr, size, i, min_idx, j);
                sleep_ms(350);
            }
        }

        // Swap the found minimum element with the first unsorted element
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main() {
    int data[SIZE] = {29, 10, 14, 37, 13, 5, 22, 19};

    printf("Starting Selection Sort...\n");
    printf("Press Enter to start...");
    getchar();

    selectionSort(data, SIZE);

    // Final state display
    system(CLEAR_SCREEN);
    printf("=== Selection Sort Visualizer ===\n");
    printf("SORTING COMPLETE!\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d] | Value: %2d [SORTED]\n", i, data[i]);
    }

    return 0;
}