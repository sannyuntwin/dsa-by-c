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

// Circular Queue Structure
typedef struct {
    int *array;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Create a queue with specified capacity
Queue* createQueue(int capacity) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->rear = capacity - 1; // Initialized so first enqueue hits index 0
    q->array = (int *)malloc(capacity * sizeof(int));
    return q;
}

// Visualize queue horizontally in terminal
void visualizeQueue(Queue *q, const char *action) {
    system(CLEAR_SCREEN);
    printf("=== Circular Queue Visualizer (FIFO) ===\n");
    printf("Action: %s | Size: %d/%d | Front: Index [%d] | Rear: Index [%d]\n\n", 
           action, q->size, q->capacity, q->front, q->rear);

    if (q->size == 0) {
        printf("[ QUEUE IS EMPTY ]\n\n");
        return;
    }

    printf("Front -> ");
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        printf("[ %d ] ", q->array[index]);
    }
    printf("<- Rear\n\n");
}

// ENQUEUE: Add element to rear
void enqueue(Queue *q, int item) {
    if (q->size == q->capacity) {
        printf("Error: Queue Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = item;
    q->size++;
    visualizeQueue(q, "ENQUEUE");
}

// DEQUEUE: Remove element from front
int dequeue(Queue *q) {
    if (q->size == 0) {
        printf("Error: Queue Underflow!\n");
        return -1;
    }
    int item = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    visualizeQueue(q, "DEQUEUE");
    return item;
}

// Free allocated memory
void freeQueue(Queue *q) {
    free(q->array);
    free(q);
}

int main() {
    Queue *myQueue = createQueue(5);

    visualizeQueue(myQueue, "INIT");
    sleep_ms(1000);

    printf("Enqueueing 10, 20, 30, 40...\n");
    enqueue(myQueue, 10); sleep_ms(800);
    enqueue(myQueue, 20); sleep_ms(800);
    enqueue(myQueue, 30); sleep_ms(800);
    enqueue(myQueue, 40); sleep_ms(800);

    printf("Dequeuing 2 items...\n");
    dequeue(myQueue); sleep_ms(800);
    dequeue(myQueue); sleep_ms(800);

    printf("Enqueueing 50, 60 (Demonstrating circular reuse)...\n");
    enqueue(myQueue, 50); sleep_ms(800);
    enqueue(myQueue, 60); sleep_ms(800);

    freeQueue(myQueue);
    return 0;
}