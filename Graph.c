#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 101

typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

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

void addVertices(Graph* g, int numVertices) {
    g->numVertices = numVertices;
}

void addDivisibleEdges(Graph* g) {
    for (int i = 1; i <= g->numVertices; i++) {
        for (int j = 1; j <= g->numVertices; j++) {
            if (i != j && i % j == 0) {
                addEdge(g, i, j);
            }
        }
    }
}

void findDegrees(Graph* g, int degrees[]) {
    for (int i = 1; i <= g->numVertices; i++) {
        degrees[i] = 0;
        for (int j = 1; j <= g->numVertices; j++) {
            if (g->matrix[i][j] == 1) {
                degrees[i]++;
            }
        }
    }
}

void printNeighbors(Graph* g, int vertex) {
    printf("Neighbors of vertex %d:\n", vertex);
    for (int i = 1; i <= g->numVertices; i++) {
        if (g->matrix[vertex][i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void printNeighborsOfNeighbors(Graph* g, int vertex) {
    int visited[MAX_VERTICES] = {0};
    printf("Neighbors of neighbors of vertex %d:\n", vertex);
    for (int i = 1; i <= g->numVertices; i++) {
        if (g->matrix[vertex][i] == 1) {
            for (int j = 1; j <= g->numVertices; j++) {
                if (g->matrix[i][j] == 1 && j != vertex && g->matrix[vertex][j] == 0) {
                    if (!visited[j]) {
                        printf("%d ", j);
                        visited[j] = 1;
                    }
                }
            }
        }
    }
    printf("\n");
}

void printCommonNeighbors(Graph* g, int v1, int v2) {
    printf("Common neighbors of vertices %d and %d:\n", v1, v2);
    for (int i = 1; i <= g->numVertices; i++) {
        if (g->matrix[v1][i] == 1 && g->matrix[v2][i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void findPrimeVertices(Graph* g) {
    printf("Prime numbered vertices:\n");
    for (int i = 1; i <= g->numVertices; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int numVertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    Graph graph;
    initGraph(&graph, numVertices);

    addVertices(&graph, numVertices);
    addDivisibleEdges(&graph);

    // Find degrees of all vertices
    int degrees[MAX_VERTICES];
    findDegrees(&graph, degrees);

    // Print degrees of all vertices
    printf("Degrees of all vertices:\n");
    for (int i = 1; i <= numVertices; i++) {
        printf("Vertex %d: %d\n", i, degrees[i]);
    }

    // Print neighbors of a given vertex
    int vertex;
    printf("Enter a vertex to find its neighbors: ");
    scanf("%d", &vertex);
    printNeighbors(&graph, vertex);

    // Print neighbors of neighbors of a given vertex
    printf("Enter a vertex to find its neighbors' neighbors: ");
    scanf("%d", &vertex);
    printNeighborsOfNeighbors(&graph, vertex);

    // Print common neighbors of two vertices
    int v1, v2;
    printf("Enter two vertices to find their common neighbors: ");
    scanf("%d %d", &v1, &v2);
    printCommonNeighbors(&graph, v1, v2);

    // Find and print all prime numbered vertices
    findPrimeVertices(&graph);

    return 0;
}
