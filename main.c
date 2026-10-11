#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

typedef struct {
    const char *name;
    const char *src;
    const char *exe;
} Algorithm;

static Algorithm algorithms[] = {
    { "Linear Search",        "searching/linear-search.c",           "linear-search"      },
    { "Binary Search",        "searching/binary-search.c",           "binary-search"      },
    { "Bubble Sort",          "sorting/bubble-sort.c",               "bubble-sort"        },
    { "Selection Sort",       "sorting/selection-sort.c",            "selection-sort"     },
    { "Insertion Sort",       "sorting/insertion-sort.c",            "insertion-sort"     },
    { "Merge Sort",           "sorting/merge-sort.c",                "merge-sort"         },
    { "Quick Sort",           "sorting/quick-sort.c",                "quick-sort"         },
    { "Singly Linked List",   "data-structures/singly-linked-list.c","singly-linked-list" },
    { "Stack",                "data-structures/stack.c",             "stack"              },
    { "Queue",                "data-structures/queue.c",             "queue"              },
    { "Binary Search Tree",   "trees/bst.c",                         "bst"                },
    { "Breadth-First Search", "graph/bfs.c",                         "bfs"                },
    { "Depth-First Search",   "graph/dfs.c",                         "dfs"                },
};

#define COUNT (int)(sizeof(algorithms) / sizeof(algorithms[0]))

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMenu() {
    system(CLEAR);
    printf("+=============================================+\n");
    printf("|          C Algorithm Collection             |\n");
    printf("+=============================================+\n");
    printf("|  Searching                                  |\n");
    printf("|    1.  Linear Search                        |\n");
    printf("|    2.  Binary Search                        |\n");
    printf("|  Sorting                                    |\n");
    printf("|    3.  Bubble Sort                          |\n");
    printf("|    4.  Selection Sort                       |\n");
    printf("|    5.  Insertion Sort                       |\n");
    printf("|    6.  Merge Sort                           |\n");
    printf("|    7.  Quick Sort                           |\n");
    printf("|  Data Structures                            |\n");
    printf("|    8.  Singly Linked List                   |\n");
    printf("|    9.  Stack                                |\n");
    printf("|   10.  Queue                                |\n");
    printf("|  Trees                                      |\n");
    printf("|   11.  Binary Search Tree (BST)             |\n");
    printf("|  Graph Traversal                            |\n");
    printf("|   12.  Breadth-First Search (BFS)           |\n");
    printf("|   13.  Depth-First Search  (DFS)            |\n");
    printf("|    0.  Exit                                 |\n");
    printf("+=============================================+\n");
    printf("\n  Choose (0-13): ");
}

void runAlgorithm(int choice) {
    if (choice < 1 || choice > COUNT) {
        printf("Invalid choice. Press Enter to continue...");
        clearInput();
        return;
    }

    Algorithm *alg = &algorithms[choice - 1];
    char cmd[512];

    // Compile
    system(CLEAR);
    printf("Compiling %s...\n", alg->name);
    snprintf(cmd, sizeof(cmd), "gcc \"%s\" -o \"%s\"", alg->src, alg->exe);
    if (system(cmd) != 0) {
        printf("\nCompilation failed! Press Enter to return to menu...");
        clearInput();
        return;
    }

    // Run
#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), ".\\%s", alg->exe);
#else
    snprintf(cmd, sizeof(cmd), "./%s", alg->exe);
#endif
    system(cmd);

    printf("\nPress Enter to return to menu...");
    clearInput();
}

int main() {
    int choice;
    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            clearInput();
            continue;
        }
        clearInput();

        if (choice == 0) {
            system(CLEAR);
            printf("Goodbye!\n");
            break;
        }
        runAlgorithm(choice);
    }
    return 0;
}
