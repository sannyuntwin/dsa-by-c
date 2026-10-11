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

// --- Queue Implementation for BFS ---
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// --- Graph Adjacency Matrix & BFS ---
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
    // Add directed edge src -> dest
    graph->adjMatrix[src][dest] = 1;
}

// BFS Traversal
void bfs(struct Graph* graph, int startVertex) {
    Queue* q = createQueue();

    // Mark starting node as visited and enqueue it
    graph->visited[startVertex] = true;
    enqueue(q, startVertex);

    system(CLEAR_SCREEN);
    printf("=== Breadth-First Search (BFS) Visualizer ===\n\n");
    printf("Starting BFS from Vertex [%d]...\n\nTraversal Order: ", startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        fflush(stdout);
        sleep_ms(600);

        // Visit all adjacent vertices
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = true;
                enqueue(q, i);
            }
        }
    }
    printf("\n\nBFS Traversal Complete!\n");
    free(q);
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

    printf("Press Enter to start BFS Traversal...");
    getchar();

    bfs(graph, 2);

    free(graph);
    return 0;
}