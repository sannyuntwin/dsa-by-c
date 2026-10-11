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

// Function to visualize current search state in terminal
void visualizeStep(int arr[], int size, int currentIndex, int target) {
    system(CLEAR_SCREEN);
    printf("=== Linear Search Visualizer ===\n");
    printf("Target Value: %d\n\n", target);

    for (int i = 0; i < size; i++) {
        printf("Index [%d] | Value: %2d ", i, arr[i]);
        
        if (i == currentIndex) {
            if (arr[i] == target) {
                printf(" <-- MATCH FOUND!");
            } else {
                printf(" <-- Checking (No match)");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Linear Search algorithm implementation
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        // Step visualization delay
        visualizeStep(arr, size, i, target);
        sleep_ms(600); // Wait 600ms per step

        if (arr[i] == target) {
            return i; // Target match found at index i
        }
    }
    return -1; // Target not found after checking all elements
}

int main() {
    int data[SIZE] = {15, 42, 8, 23, 91, 34, 67, 50};
    int target = 91;

    printf("Starting Linear Search for target: %d\n", target);
    printf("Press Enter to start...");
    getchar();

    int resultIndex = linearSearch(data, SIZE, target);

    if (resultIndex != -1) {
        printf("SUCCESS: Found target %d at index %d!\n", target, resultIndex);
    } else {
        printf("FAILED: Target %d is not in the array.\n", target);
    }

    return 0;
}