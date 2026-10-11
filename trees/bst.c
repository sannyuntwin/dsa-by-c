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

// Node structure for a Binary Search Tree
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

// Create a new BST Node
struct Node* createNode(int item) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Recursively insert a new key into the BST
struct Node* insert(struct Node *node, int key) {
    // If tree/subtree is empty, return new node
    if (node == NULL) return createNode(key);

    // Otherwise, recur down the tree
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }

    return node;
}

// 1. In-Order Traversal (Left, Root, Right) -> Prints in sorted order
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// 2. Pre-Order Traversal (Root, Left, Right)
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// 3. Post-Order Traversal (Left, Right, Root)
void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

// Free tree nodes from memory bottom-up
void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node *root = NULL;

    printf("Building Binary Search Tree...\n");
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    system(CLEAR_SCREEN);
    printf("=== Binary Search Tree Traversal Demo ===\n\n");
    printf("Inserted Keys: 50, 30, 20, 40, 70, 60, 80\n\n");

    printf("1. In-Order Traversal (Sorted): ");
    inorder(root);
    printf("\n\n");

    printf("2. Pre-Order Traversal:         ");
    preorder(root);
    printf("\n\n");

    printf("3. Post-Order Traversal:        ");
    postorder(root);
    printf("\n\n");

    freeTree(root);
    return 0;
}