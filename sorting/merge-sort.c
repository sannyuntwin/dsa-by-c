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

// Terminal visualizer showing array state and current active range [left..right]
void visualizeStep(int arr[], int size, int left, int right, const char *action) {
    system(CLEAR_SCREEN);
    printf("=== Merge Sort Visualizer ===\n");
    printf("Action: %s | Active Subarray Range: Index [%d] to [%d]\n\n", action, left, right);

    for (int i = 0; i < size; i++) {
        printf("Index [%d] | Value: %2d | ", i, arr[i]);
        
        for (int k = 0; k < arr[i]; k++) {
            printf("#");
        }

        if (i >= left && i <= right) {
            printf(" <-- Active Subarray");
        }
        printf("\n");
    }
    printf("\n");
}

// Function to merge two sorted subarrays: arr[left..mid] and arr[mid+1..right]
void merge(int arr[], int left, int mid, int right, int totalSize) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary dynamic arrays for left and right subarrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    // Merge temp arrays back into main arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    visualizeStep(arr, totalSize, left, right, "MERGED SUBARRAYS");
    sleep_ms(500);

    // Free temporary dynamic memory
    free(L);
    free(R);
}

// Recursive Merge Sort function
void mergeSort(int arr[], int left, int right, int totalSize) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        visualizeStep(arr, totalSize, left, right, "SPLITTING LEFT");
        sleep_ms(350);

        // Sort first half
        mergeSort(arr, left, mid, totalSize);

        visualizeStep(arr, totalSize, left, right, "SPLITTING RIGHT");
        sleep_ms(350);

        // Sort second half
        mergeSort(arr, mid + 1, right, totalSize);

        // Merge the sorted halves
        merge(arr, left, mid, right, totalSize);
    }
}

int main() {
    int data[SIZE] = {38, 27, 43, 3, 9, 82, 10, 19};

    printf("Starting Merge Sort...\n");
    printf("Press Enter to start...");
    getchar();

    mergeSort(data, 0, SIZE - 1, SIZE);

    // Final state display
    system(CLEAR_SCREEN);
    printf("=== Merge Sort Visualizer ===\n");
    printf("SORTING COMPLETE!\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d] | Value: %2d [SORTED]\n", i, data[i]);
    }

    return 0;
}