#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

typedef struct Stack {
    int items[MAX_VERTICES];
    int top;
} Stack;

typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initGraph(Graph* g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

void addEdge(Graph* g, int src, int dest) {
    g->matrix[src][dest] = 1;
    g->matrix[dest][src] = 1; // For undirected graph
}

// Recursive DFS
void DFSRecursive(Graph* g, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 0; i < g->numVertices; i++) {
        if (g->matrix[vertex][i] && !visited[i]) {
            DFSRecursive(g, i, visited);
        }
    }
}

void DFS(Graph* g, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    DFSRecursive(g, startVertex, visited);
    printf("\n");
}

// Iterative DFS
void push(Stack* s, int value) {
    s->items[++(s->top)] = value;
}

int pop(Stack* s) {
    return s->items[(s->top)--];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void DFSIterative(Graph* g, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Stack stack;
    stack.top = -1;

    push(&stack, startVertex);

    while (!isEmpty(&stack)) {
        int vertex = pop(&stack);
        if (!visited[vertex]) {
            visited[vertex] = 1;
            printf("%d ", vertex);
        }

        for (int i = g->numVertices - 1; i >= 0; i--) {
            if (g->matrix[vertex][i] && !visited[i]) {
                push(&stack, i);
            }
        }
    }
    printf("\n");
}

// BFS
void enqueue(Queue* q, int value) {
    q->items[++(q->rear)] = value;
}

int dequeue(Queue* q) {
    return q->items[(q->front)++];
}

int isQueueEmpty(Queue* q) {
    return q->front > q->rear;
}

void BFS(Graph* g, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Queue queue;
    queue.front = 0;
    queue.rear = -1;

    visited[startVertex] = 1;
    enqueue(&queue, startVertex);

    while (!isQueueEmpty(&queue)) {
        int vertex = dequeue(&queue);
        printf("%d ", vertex);

        for (int i = 0; i < g->numVertices; i++) {
            if (g->matrix[vertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(&queue, i);
            }
        }
    }
    printf("\n");
}

// Dijkstra's Algorithm
int minDistance(int dist[], int visited[], int numVertices) {
    int min = INF, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(Graph* g, int src) {
    int dist[MAX_VERTICES], visited[MAX_VERTICES];
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < g->numVertices - 1; count++) {
        int u = minDistance(dist, visited, g->numVertices);
        visited[u] = 1;

        for (int v = 0; v < g->numVertices; v++) {
            if (!visited[v] && g->matrix[u][v] && dist[u] != INF && dist[u] + g->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + g->matrix[u][v];
            }
        }
    }

    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

int main() {
    Graph graph;
    int numVertices = 5;

    initGraph(&graph, numVertices);

    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 4);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);

    printf("DFS (Recursive):\n");
    DFS(&graph, 0);

    printf("DFS (Iterative):\n");
    DFSIterative(&graph, 0);

    printf("BFS:\n");
    BFS(&graph, 0);

    // Add weights for Dijkstra's Algorithm
    graph.matrix[0][1] = 10;
    graph.matrix[0][4] = 3;
    graph.matrix[1][2] = 2;
    graph.matrix[1][4] = 4;
    graph.matrix[2][3] = 9;
    graph.matrix[3][4] = 7;

    printf("Dijkstra's Algorithm:\n");
    dijkstra(&graph, 0);

    return 0;
}
