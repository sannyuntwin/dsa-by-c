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

#define MAX_VERTICES 5

struct Graph {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    bool visited[MAX_VERTICES];
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = false;
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1; // Directed edge src -> dest
}

// Recursive Depth-First Search Implementation
void DFS(struct Graph* graph, int vertex) {
    // Mark current node as visited
    graph->visited[vertex] = true;
    printf("%d ", vertex);
    fflush(stdout);
    sleep_ms(600);

    // Recursively visit all unvisited neighbors
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            DFS(graph, i); // Recurse deeper into path
        }
    }
}

int main() {
    struct Graph* graph = createGraph(MAX_VERTICES);

    // Build sample graph edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 3);

    system(CLEAR_SCREEN);
    printf("=== Depth-First Search (DFS) Visualizer ===\n\n");
    printf("Starting DFS from Vertex [2]...\n\nTraversal Order: ");

    DFS(graph, 2);

    printf("\n\nDFS Traversal Complete!\n");

    free(graph);
    return 0;
}