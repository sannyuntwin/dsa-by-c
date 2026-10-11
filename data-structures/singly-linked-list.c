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

// Define Linked List Node structure
struct Node {
    int data;
    struct Node *next;
};

// Function to print and visualize list nodes in memory
void printList(struct Node *head) {
    system(CLEAR_SCREEN);
    printf("=== Singly Linked List Visualizer ===\n\n");

    if (head == NULL) {
        printf("List is empty: [ HEAD ] -> NULL\n\n");
        return;
    }

    printf("[ HEAD ] -> ");
    struct Node *temp = head;
    while (temp != NULL) {
        printf("[ Data: %d | Next: %p ] -> ", temp->data, (void *)temp->next);
        temp = temp->next;
    }
    printf("NULL\n\n");
}

// 1. Insert Node at the Head (Front)
void insertAtHead(struct Node **headRef, int newData) {
    // Allocate memory on the Heap for new Node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    
    newNode->data = newData;
    newNode->next = *headRef; // Point new node's next to current head
    *headRef = newNode;       // Shift head pointer to new node
}

// 2. Insert Node at the Tail (End)
void insertAtTail(struct Node **headRef, int newData) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    struct Node *last = *headRef;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

// 3. Delete Node by value
void deleteNode(struct Node **headRef, int key) {
    struct Node *temp = *headRef;
    struct Node *prev = NULL;

    // Case 1: Key is in Head node
    if (temp != NULL && temp->data == key) {
        *headRef = temp->next;
        free(temp); // Free memory back to Heap
        return;
    }

    // Case 2: Search for key in list keeping track of prev node
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Case 3: Key not found
    if (temp == NULL) return;

    // Unlink node from list and free memory
    prev->next = temp->next;
    free(temp);
}

// Free all allocated dynamic memory
void freeList(struct Node **headRef) {
    struct Node *current = *headRef;
    struct Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL;
}

int main() {
    struct Node *head = NULL; // Initialize empty list

    printList(head);
    sleep_ms(1000);

    printf("Inserting 10 at Head...\n");
    insertAtHead(&head, 10);
    printList(head);
    sleep_ms(1000);

    printf("Inserting 20 at Head...\n");
    insertAtHead(&head, 20);
    printList(head);
    sleep_ms(1000);

    printf("Inserting 30 at Tail...\n");
    insertAtTail(&head, 30);
    printList(head);
    sleep_ms(1000);

    printf("Deleting Node with value 10...\n");
    deleteNode(&head, 10);
    printList(head);
    sleep_ms(1000);

    // Free heap memory before exiting
    freeList(&head);
    printf("Memory freed. Program finished.\n");

    return 0;
}