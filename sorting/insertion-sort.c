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

// Visualizer showing key extraction, active comparisons, and rightward shifts
void visualizeStep(int arr[], int size, int key, int keyIdx, int compareIdx) {
    system(CLEAR_SCREEN);
    printf("=== Insertion Sort Visualizer ===\n");
    printf("Current Key: %d (Extracted from index [%d])\n\n", key, keyIdx);

    for (int i = 0; i < size; i++) {
        printf("Index [%d] | Value: %2d | ", i, arr[i]);
        
        for (int k = 0; k < arr[i]; k++) {
            printf("#");
        }

        if (i == compareIdx) {
            printf(" <-- Comparing & Shifting");
        } else if (i == keyIdx) {
            printf(" <-- Key Slot");
        }
        printf("\n");
    }
    printf("\n");
}

// Insertion Sort Implementation
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        visualizeStep(arr, size, key, i, j);
        sleep_ms(400);

        // Shift elements greater than key to one position ahead
        while (j >= 0 && arr[j] > key) {
            visualizeStep(arr, size, key, i, j);
            sleep_ms(350);

            arr[j + 1] = arr[j]; // Shift right
            j = j - 1;
        }

        // Place key at its correct position
        arr[j + 1] = key;
        
        visualizeStep(arr, size, key, i, j + 1);
        sleep_ms(400);
    }
}

int main() {
    int data[SIZE] = {33, 12, 52, 18, 6, 25, 41, 10};

    printf("Starting Insertion Sort...\n");
    printf("Press Enter to start...");
    getchar();

    insertionSort(data, SIZE);

    // Final state display
    system(CLEAR_SCREEN);
    printf("=== Insertion Sort Visualizer ===\n");
    printf("SORTING COMPLETE!\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d] | Value: %2d [SORTED]\n", i, data[i]);
    }

    return 0;
}