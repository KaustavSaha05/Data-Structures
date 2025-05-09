#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF INT_MAX
#define MAX_STATIONS 100
#define MAX_NAME_LEN 100

typedef struct Node {
    int station;
    int travelTime;
    struct Node* next;
} Node;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char location[MAX_NAME_LEN];
    int platformCount;
} Station;

typedef struct Graph {
    int numStations;
    Station* stations[MAX_STATIONS]; // Array of pointers to Station
    Node* adjList[MAX_STATIONS];
} Graph;

typedef struct {
    int travelTime;
    int transfers;
    int ticketPrice;
} CostFactors;

Graph* createGraph(int numStations) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numStations = numStations;

    for (int i = 0; i < numStations; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

Node* createNode(int station, int travelTime) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->station = station;
    newNode->travelTime = travelTime;
    newNode->next = NULL;

    return newNode;
}

void addEdge(Graph* graph, int src, int dest, int travelTime) {
    Node* newNode = createNode(dest, travelTime);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src, travelTime);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void addStation(Graph* graph, int id, const char* name, const char* location, int platformCount) {
    if (graph->numStations >= MAX_STATIONS) {
        printf("Maximum number of stations reached.\n");
        return;
    }
    
    Station* newStation = (Station*)malloc(sizeof(Station));
    if (newStation == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newStation->id = id;
    strncpy(newStation->name, name, MAX_NAME_LEN);
    strncpy(newStation->location, location, MAX_NAME_LEN);
    newStation->platformCount = platformCount;

    graph->stations[graph->numStations] = newStation;
    graph->numStations++;
    
    printf("Station added: %s\n", name);
}

void removeStation(Graph* graph, int id) {
    int index = -1;
    for (int i = 0; i < graph->numStations; i++) {
        if (graph->stations[i]->id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Station not found.\n");
        return;
    }

    free(graph->stations[index]);
    for (int i = index; i < graph->numStations - 1; i++) {
        graph->stations[i] = graph->stations[i + 1];
    }

    graph->numStations--;
    printf("Station removed.\n");
}

void updateStation(Graph* graph, int id, const char* name, const char* location, int platformCount) {
    for (int i = 0; i < graph->numStations; i++) {
        if (graph->stations[i]->id == id) {
            strncpy(graph->stations[i]->name, name, MAX_NAME_LEN);
            strncpy(graph->stations[i]->location, location, MAX_NAME_LEN);
            graph->stations[i]->platformCount = platformCount;
            printf("Station updated: %s\n", name);
            return;
        }
    }

    printf("Station not found.\n");
}

int minDistance(int dist[], int sptSet[], int numStations) {
    int min = INF, minIndex;

    for (int v = 0; v < numStations; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(Graph* graph, int src, int dest) {
    int dist[MAX_STATIONS];
    int sptSet[MAX_STATIONS];
    int parent[MAX_STATIONS];

    for (int i = 0; i < graph->numStations; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < graph->numStations - 1; count++) {
        int u = minDistance(dist, sptSet, graph->numStations);
        sptSet[u] = 1;

        for (Node* pCrawl = graph->adjList[u]; pCrawl != NULL; pCrawl = pCrawl->next) {
            int v = pCrawl->station;
            if (!sptSet[v] && dist[u] != INF && dist[u] + pCrawl->travelTime < dist[v]) {
                dist[v] = dist[u] + pCrawl->travelTime;
                parent[v] = u;
            }
        }
    }

    // Print the result or store it
    if (dist[dest] == INF) {
        printf("No path found from %d to %d.\n", src, dest);
    } else {
        printf("Shortest path from %d to %d is %d\n", src, dest, dist[dest]);
        printf("Path: %d", dest);
        int crawl = dest;
        while (parent[crawl] != -1) {
            printf(" <- %d", parent[crawl]);
            crawl = parent[crawl];
        }
        printf("\n");
    }
}

void removeEdge(Graph* graph, int src, int dest) {
    Node** curr = &(graph->adjList[src]);
    while (*curr != NULL) {
        if ((*curr)->station == dest) {
            Node* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            break;
        }
        curr = &((*curr)->next);
    }

    curr = &(graph->adjList[dest]);
    while (*curr != NULL) {
        if ((*curr)->station == src) {
            Node* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            break;
        }
        curr = &((*curr)->next);
    }
}

void displayRoute(int parent[], int dest) {
    // Check if there's no route to the destination
    if (parent[dest] == -1) {
        printf("No route to destination.\n");
        return;
    }

    // Create a stack to store the path
    int stack[MAX_STATIONS];
    int top = -1;

    // Traverse from destination to source and store the path in the stack
    int crawl = dest;
    while (parent[crawl] != -1) {
        stack[++top] = crawl;
        crawl = parent[crawl];
    }
    stack[++top] = crawl;

    // Print the route
    printf("Route: ");
    while (top >= 0) {
        printf("%d", stack[top--]);
        if (top >= 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void dijkstraWithDisruption(Graph* graph, int src, int dest) {
    int dist[MAX_STATIONS];
    int sptSet[MAX_STATIONS];
    int parent[MAX_STATIONS];

    for (int i = 0; i < graph->numStations; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < graph->numStations - 1; count++) {
        int u = minDistance(dist, sptSet, graph->numStations);
        sptSet[u] = 1;

        for (Node* pCrawl = graph->adjList[u]; pCrawl != NULL; pCrawl = pCrawl->next) {
            int v = pCrawl->station;
            if (!sptSet[v] && dist[u] != INF && dist[u] + pCrawl->travelTime < dist[v]) {
                dist[v] = dist[u] + pCrawl->travelTime;
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INF) {
        printf("No path found from %d to %d.\n", src, dest);
    } else {
        printf("Shortest path length: %d\n", dist[dest]);
        displayRoute(parent, dest);
    }
}

void handleDisruption(Graph* graph, int disruptedSrc, int disruptedDest, int start, int end, int travelTime) {
    // Remove the edge representing the disruption
    removeEdge(graph, disruptedSrc, disruptedDest);

    // Find alternative routes using the modified graph
    printf("Finding alternative routes from %d to %d after disruption between %d and %d...\n", start, end, disruptedSrc, disruptedDest);
    dijkstraWithDisruption(graph, start, end);

    // Restore the disrupted edge if you want to reuse the original graph
    addEdge(graph, disruptedSrc, disruptedDest, travelTime);
}

int calculateTransfers(int parent[], int start, int end) {
    int transfers = 0;
    int current = end;

    while (parent[current] != -1) {
        transfers++;
        current = parent[current];
    }

    return transfers - 1; // -1 because the first station is not a transfer
}

int calculateRouteCost(Graph* graph, int dist[], int parent[], int start, int end, CostFactors factors) {
    int travelTime = dist[end];
    if (travelTime == INF) {
        printf("No valid path exists.\n");
        return INF;
    }

    int transfers = calculateTransfers(parent, start, end);
    int ticketPrice = factors.ticketPrice * transfers;

    int totalCost = (factors.travelTime * travelTime) + (factors.transfers * transfers) + ticketPrice;
    return totalCost;
}

void dijkstraWithCostCalculation(Graph* graph, int src, int dest, CostFactors factors) {
    int dist[MAX_STATIONS];
    int sptSet[MAX_STATIONS];
    int parent[MAX_STATIONS];

    for (int i = 0; i < graph->numStations; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < graph->numStations - 1; count++) {
        int u = minDistance(dist, sptSet, graph->numStations);
        sptSet[u] = 1;

        for (Node* pCrawl = graph->adjList[u]; pCrawl != NULL; pCrawl = pCrawl->next) {
            int v = pCrawl->station;
            if (!sptSet[v] && dist[u] != INF && dist[u] + pCrawl->travelTime < dist[v]) {
                dist[v] = dist[u] + pCrawl->travelTime;
                parent[v] = u;
            }
        }
    }

    int cost = calculateRouteCost(graph, dist, parent, src, dest, factors);
    if (cost == INF) {
        printf("No path found from %d to %d due to disruption.\n", src, dest);
    } else {
        printf("Total cost of the shortest path from %d to %d is: %d\n", src, dest, cost);
        printf("Path: %d", dest);
        int crawl = dest;
        while (parent[crawl] != -1) {
            printf(" <- %d", parent[crawl]);
            crawl = parent[crawl];
        }
        printf("\n");
    }
}

void findAlternativeRouteUI(Graph* graph) {
    int start, end;
    CostFactors factors;

    printf("Enter Start Station ID: ");
    scanf("%d", &start);
    printf("Enter End Station ID: ");
    scanf("%d", &end);

    // Define cost factors
    printf("Enter cost weight for travel time: ");
    scanf("%d", &factors.travelTime);
    printf("Enter cost weight for transfers: ");
    scanf("%d", &factors.transfers);
    printf("Enter base ticket price: ");
    scanf("%d", &factors.ticketPrice);

    printf("Finding alternative route from %d to %d...\n", start, end);
    dijkstraWithCostCalculation(graph, start, end, factors);
}

void displayMenu() {
    printf("\nTrain Journey Alternative Route Application\n");
    printf("1. Add Station\n");
    printf("2. Add Route\n");
    printf("3. Remove Route (Simulate Disruption)\n");
    printf("4. Find Alternative Route\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addStationUI(Graph* graph) {
    int id, platformCount;
    char name[MAX_NAME_LEN];
    char location[MAX_NAME_LEN];

    printf("Enter Station ID: ");
    scanf("%d", &id);
    printf("Enter Station Name: ");
    scanf("%s", name);
    printf("Enter Station Location: ");
    scanf("%s", location);
    printf("Enter Number of Platforms: ");
    scanf("%d", &platformCount);

    addStation(graph, id, name, location, platformCount);
}

void addRouteUI(Graph* graph) {
    int src, dest, travelTime;
    printf("Enter Source Station ID: ");
    scanf("%d", &src);
    printf("Enter Destination Station ID: ");
    scanf("%d", &dest);
    printf("Enter Travel Time: ");
    scanf("%d", &travelTime);

    addEdge(graph, src, dest, travelTime);
}

void removeRouteUI(Graph* graph) {
    int src, dest;
    printf("Enter Source Station ID of the route to remove: ");
    scanf("%d", &src);
    printf("Enter Destination Station ID of the route to remove: ");
    scanf("%d", &dest);

    removeEdge(graph, src, dest);
}

int main() {
    Graph* graph = createGraph(5);  // Example with initial capacity of 5 stations
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStationUI(graph);
                break;
            case 2:
                addRouteUI(graph);
                break;
            case 3:
                removeRouteUI(graph);
                break;
            case 4:
                findAlternativeRouteUI(graph);
                break;
            case 5:
                // Free allocated memory and exit
                for (int i = 0; i < graph->numStations; i++) {
                    Node* pCrawl = graph->adjList[i];
                    while (pCrawl != NULL) {
                        Node* temp = pCrawl;
                        pCrawl = pCrawl->next;
                        free(temp);
                    }
                }
                for (int i = 0; i < graph->numStations; i++) {
                    free(graph->stations[i]);
                }
                free(graph);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

