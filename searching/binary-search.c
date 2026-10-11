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

#define SIZE 10

// Function to visualize low, mid, and high pointers in terminal
void visualizeStep(int arr[], int low, int mid, int high, int target) {
    system(CLEAR_SCREEN);
    printf("=== Binary Search Visualizer ===\n");
    printf("Target Value: %d\n", target);
    printf("Search Range: Index [%d] to Index [%d]\n\n", low, high);

    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d] | Value: %2d ", i, arr[i]);
        
        if (i == mid) {
            if (arr[i] == target) {
                printf(" <-- MID (MATCH FOUND!)");
            } else {
                printf(" <-- MID");
            }
        } else if (i == low && i == high) {
            printf(" <-- LOW & HIGH");
        } else if (i == low) {
            printf(" <-- LOW");
        } else if (i == high) {
            printf(" <-- HIGH");
        }
        
        printf("\n");
    }
    printf("\n");
}

// Binary Search implementation
int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        // Prevent overflow compared to (low + high) / 2
        int mid = low + (high - low) / 2;

        visualizeStep(arr, low, mid, high, target);
        sleep_ms(800); // Pause to view mid pointer

        if (arr[mid] == target) {
            return mid; // Target match found
        }

        if (arr[mid] < target) {
            low = mid + 1;  // Discard left half
        } else {
            high = mid - 1; // Discard right half
        }
    }

    return -1; // Target not found
}

int main() {
    // Array MUST be sorted for Binary Search
    int data[SIZE] = {2, 7, 11, 18, 23, 31, 45, 59, 72, 88};
    int target = 59;

    printf("Starting Binary Search for target: %d\n", target);
    printf("Press Enter to start...");
    getchar();

    int resultIndex = binarySearch(data, SIZE, target);

    if (resultIndex != -1) {
        printf("SUCCESS: Found target %d at index %d!\n", target, resultIndex);
    } else {
        printf("FAILED: Target %d is not in the array.\n", target);
    }

    return 0;
}