#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to visualize adjacent elements being compared or swapped
void visualizeStep(int arr[], int size, int active1, int active2, int pass) {
    system(CLEAR_SCREEN);
    printf("=== Bubble Sort Visualizer ===\n");
    printf("Pass #: %d\n\n", pass);

    for (int i = 0; i < size; i++) {
        printf("Index [%d] | Value: %2d ", i, arr[i]);
        
        // Draw ASCII bars for visual length
        printf("| ");
        for (int k = 0; k < arr[i]; k++) {
            printf("#");
        }

        if (i == active1 || i == active2) {
            printf(" <-- Comparing / Swapping");
        }
        printf("\n");
    }
    printf("\n");
}

// Optimized Bubble Sort Implementation
void bubbleSort(int arr[], int size) {
    bool swapped;

    for (int i = 0; i < size - 1; i++) {
        swapped = false;

        for (int j = 0; j < size - i - 1; j++) {
            visualizeStep(arr, size, j, j + 1, i + 1);
            sleep_ms(400);

            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;

                // Show state immediately after swap
                visualizeStep(arr, size, j, j + 1, i + 1);
                sleep_ms(400);
            }
        }

        // If no two elements were swapped in inner loop, array is sorted
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int data[SIZE] = {25, 12, 8, 30, 4, 18, 2, 15};

    printf("Starting Bubble Sort...\n");
    printf("Press Enter to start...");
    getchar();

    bubbleSort(data, SIZE);

    // Final clean display
    system(CLEAR_SCREEN);
    printf("=== Bubble Sort Visualizer ===\n");
    printf("SORTING COMPLETE!\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d] | Value: %2d\n", i, data[i]);
    }

    return 0;
}