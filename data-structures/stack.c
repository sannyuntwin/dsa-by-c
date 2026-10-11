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

// Dynamic Stack Structure
typedef struct {
    int *array;      // Pointer to dynamic array on Heap
    int top;         // Index of the top element
    int capacity;    // Max elements before dynamic resizing
} Stack;

// Initialize stack memory
Stack* createStack(int initialCapacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = initialCapacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Visualize stack state vertically in terminal
void visualizeStack(Stack *stack, const char *action) {
    system(CLEAR_SCREEN);
    printf("=== Dynamic Stack Visualizer (LIFO) ===\n");
    printf("Action: %s | Top Index: %d | Capacity: %d\n\n", action, stack->top, stack->capacity);

    if (stack->top == -1) {
        printf("  [ STACK IS EMPTY ]\n");
    } else {
        for (int i = stack->top; i >= 0; i--) {
            printf("  | %2d |", stack->array[i]);
            if (i == stack->top) {
                printf(" <-- TOP");
            }
            printf("\n  +----+");
            printf("\n");
        }
    }
    printf("\n");
}

// PUSH: Add element to stack (Resizes dynamically if full)
void push(Stack *stack, int item) {
    if (stack->top == stack->capacity - 1) {
        // Double capacity dynamically when full
        stack->capacity *= 2;
        stack->array = (int *)realloc(stack->array, stack->capacity * sizeof(int));
    }
    stack->array[++stack->top] = item;
    visualizeStack(stack, "PUSH");
}

// POP: Remove element from top of stack
int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Error: Stack Underflow!\n");
        return -1;
    }
    int poppedValue = stack->array[stack->top--];
    visualizeStack(stack, "POP");
    return poppedValue;
}

// PEEK: Look at the top element without removing
int peek(Stack *stack) {
    if (stack->top == -1) return -1;
    return stack->array[stack->top];
}

// Free allocated heap memory
void freeStack(Stack *stack) {
    free(stack->array);
    free(stack);
}

int main() {
    Stack *myStack = createStack(2); // Start with small capacity of 2 to demonstrate dynamic growth

    visualizeStack(myStack, "INIT");
    sleep_ms(1000);

    printf("Pushing 10, 20...\n");
    push(myStack, 10); sleep_ms(800);
    push(myStack, 20); sleep_ms(800);

    printf("Pushing 30 (Triggers dynamic resizing)...\n");
    push(myStack, 30); sleep_ms(800);

    printf("Pushing 40...\n");
    push(myStack, 40); sleep_ms(800);

    printf("Popping elements...\n");
    pop(myStack); sleep_ms(800);
    pop(myStack); sleep_ms(800);

    printf("Top element currently: %d\n", peek(myStack));

    freeStack(myStack);
    return 0;
}