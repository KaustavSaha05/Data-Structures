#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_WAREHOUSES 100
#define INF INT_MAX

typedef struct InventoryItem {
    char name[50];
    int quantity;
    float unit_cost;
    struct InventoryItem *next;
} InventoryItem;

typedef struct Warehouse {
    char name[50];
    char location[100];
    int capacity;
    struct InventoryItem *inventory;
    struct Warehouse *next;
} Warehouse;

typedef struct Region {
    char name[50];
    struct Region *child;
    struct Region *sibling;
    Warehouse *warehouses;
} Region;

typedef struct Graph {
    int vertices[MAX_WAREHOUSES][MAX_WAREHOUSES];
    int num_vertices;
} Graph;

// Function to initialize a graph
void initialize_graph(Graph *g, int num_vertices) {
    g->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            g->vertices[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// Function to add an edge to the graph
void add_edge(Graph *g, int from, int to, int weight) {
    g->vertices[from][to] = weight;
}

int min_distance(int dist[], int visited[], int num_vertices) {
    int min = INF, min_index;
    for (int v = 0; v < num_vertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(Graph *g, int start_node, int end_node) {
    int dist[MAX_WAREHOUSES], visited[MAX_WAREHOUSES], parent[MAX_WAREHOUSES];
    
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    dist[start_node] = 0;
    
    for (int count = 0; count < g->num_vertices - 1; count++) {
        int u = min_distance(dist, visited, g->num_vertices);
        visited[u] = 1;
        
        for (int v = 0; v < g->num_vertices; v++) {
            if (!visited[v] && g->vertices[u][v] && dist[u] != INF && dist[u] + g->vertices[u][v] < dist[v]) {
                dist[v] = dist[u] + g->vertices[u][v];
                parent[v] = u;
            }
        }
    }
    
    // Print the shortest path
    int current = end_node;
    printf("Shortest Path: ");
    while (current != -1) {
        printf("%d ", current);
        current = parent[current];
    }
    printf("\nDistance: %d\n", dist[end_node]);
}

// Functions to create regions and warehouses
Region* createRegion(char *name) {
    Region *newRegion = (Region *)malloc(sizeof(Region));
    strcpy(newRegion->name, name);
    newRegion->child = NULL;
    newRegion->sibling = NULL;
    newRegion->warehouses = NULL;
    return newRegion;
}

void addChildRegion(Region *parent, char *name) {
    Region *child = createRegion(name);
    child->sibling = parent->child;
    parent->child = child;
}

Warehouse* createWarehouse(char *name, char *location, int capacity) {
    Warehouse *newWarehouse = (Warehouse *)malloc(sizeof(Warehouse));
    strcpy(newWarehouse->name, name);
    strcpy(newWarehouse->location, location);
    newWarehouse->capacity = capacity;
    newWarehouse->inventory = NULL;
    newWarehouse->next = NULL;
    return newWarehouse;
}

void addWarehouse(Region *region, char *name, char *location, int capacity) {
    Warehouse *warehouse = createWarehouse(name, location, capacity);
    warehouse->next = region->warehouses;
    region->warehouses = warehouse;
}

void printWarehouses(Region *region) {
    Warehouse *current = region->warehouses;
    while (current != NULL) {
        printf("Name: %s, Location: %s, Capacity: %d\n", current->name, current->location, current->capacity);
        current = current->next;
    }
}

Warehouse* findWarehouse(Region *region, char *name) {
    Warehouse *current = region->warehouses;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateWarehouse(Warehouse *warehouse, char *newName, char *newLocation, int newCapacity) {
    strcpy(warehouse->name, newName);
    strcpy(warehouse->location, newLocation);
    warehouse->capacity = newCapacity;
}

void deleteWarehouse(Region *region, char *name) {
    Warehouse *current = region->warehouses;
    Warehouse *prev = NULL;
    
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Warehouse not found.\n");
        return;
    }
    
    if (prev == NULL) {
        region->warehouses = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
}

// Inventory Management Functions
InventoryItem* createInventoryItem(char *name, int quantity, float unit_cost) {
    InventoryItem *newItem = (InventoryItem *)malloc(sizeof(InventoryItem));
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->unit_cost = unit_cost;
    newItem->next = NULL;
    return newItem;
}

void addInventoryItem(Warehouse *warehouse, char *name, int quantity, float unit_cost) {
    InventoryItem *item = createInventoryItem(name, quantity, unit_cost);
    item->next = warehouse->inventory;
    warehouse->inventory = item;
}

void printInventory(Warehouse *warehouse) {
    InventoryItem *current = warehouse->inventory;
    while (current != NULL) {
        printf("Item: %s, Quantity: %d\n", current->name, current->quantity);
        current = current->next;
    }
}

InventoryItem* findInventoryItem(Warehouse *warehouse, char *name) {
    InventoryItem *current = warehouse->inventory;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateInventoryItem(InventoryItem *item, int newQuantity, float unit_cost) {
    item->quantity = newQuantity;
}

void deleteInventoryItem(Warehouse *warehouse, char *name) {
    InventoryItem *current = warehouse->inventory;
    InventoryItem *prev = NULL;
    
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Inventory item not found.\n");
        return;
    }
    
    if (prev == NULL) {
        warehouse->inventory = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
}

// Function to calculate the total cost of inventory items in a warehouse 
float calculateTotalCost(Warehouse *warehouse) { 
	float totalCost = 0.0; 
	InventoryItem *current = warehouse->inventory; 
	while (current != NULL) {
		totalCost += current->quantity * current->unit_cost; 
		current = current->next; 
	} 
	return totalCost; 
}

// Function to report analytics for a warehouse
void reportAnalytics(Warehouse *warehouse) {
    int totalItems = 0;
    int totalQuantity = 0;
    float totalCost = calculateTotalCost(warehouse);
    InventoryItem *current = warehouse->inventory;
    while (current != NULL) {
        totalItems++;
        totalQuantity += current->quantity;
        current = current->next;
    }
    float averageCost = (totalItems > 0) ? totalCost / totalQuantity : 0.0;

    printf("\nWarehouse Analytics:\n");
    printf("Total Items: %d\n", totalItems);
    printf("Total Quantity: %d\n", totalQuantity);
    printf("Total Cost: %.2f\n", totalCost);
    printf("Average Cost per Item: %.2f\n", averageCost);
}

void userInterface() {
    Region *region = createRegion("Main Region");
    int choice;
    char warehouseName[50];
    char location[100];
    int capacity;
    char itemName[50];
    int quantity;
    float unit_cost;
    int from, to, weight, start_node, end_node;
    Warehouse *warehouse;
    InventoryItem *item;
    Graph g;
    initialize_graph(&g, MAX_WAREHOUSES);

    do {
        printf("\nWarehouse Management System\n");
        printf("1. Add Warehouse\n");
        printf("2. Delete Warehouse\n");
        printf("3. Add Inventory Item\n");
        printf("4. Update Inventory Item\n");
        printf("5. Delete Inventory Item\n");
        printf("6. Print Warehouses\n");
        printf("7. Print Inventory\n");
        printf("8. Calculate Total Cost\n");
        printf("9. Report Analytics\n");
        printf("10. Add Route\n");
        printf("11. Find Shortest Route\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                printf("Enter location: ");
                scanf("%s", location);
                printf("Enter capacity: ");
                scanf("%d", &capacity);
                addWarehouse(region, warehouseName, location, capacity);
                printf("Warehouse added.\n");
                break;
            case 2:
                printf("Enter warehouse name to delete: ");
                scanf("%s", warehouseName);
                deleteWarehouse(region, warehouseName);
                printf("Warehouse deleted.\n");
                break;
            case 3:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                warehouse = findWarehouse(region, warehouseName);
                if (warehouse != NULL) {
                    printf("Enter item name: ");
                    scanf("%s", itemName);
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    printf("Enter unit cost: ");
                    scanf("%f", &unit_cost);
                    addInventoryItem(warehouse, itemName, quantity, unit_cost);
                    printf("Inventory item added.\n");
                } else {
                    printf("Warehouse not found.\n");
                }
                break;
            case 4:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                warehouse = findWarehouse(region, warehouseName);
                if (warehouse != NULL) {
                    printf("Enter item name to update: ");
                    scanf("%s", itemName);
                    item = findInventoryItem(warehouse, itemName);
                    if (item != NULL) {
                        printf("Enter new quantity: ");
                        scanf("%d", &quantity);
                        printf("Enter new unit cost: ");
                        scanf("%f", &unit_cost);
                        updateInventoryItem(item, quantity, unit_cost);
                        printf("Inventory item updated.\n");
                    } else {
                        printf("Inventory item not found.\n");
                    }
                } else {
                    printf("Warehouse not found.\n");
                }
                break;
            case 5:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                warehouse = findWarehouse(region, warehouseName);
                if (warehouse != NULL) {
                    printf("Enter item name to delete: ");
                    scanf("%s", itemName);
                    deleteInventoryItem(warehouse, itemName);
                    printf("Inventory item deleted.\n");
                } else {
                    printf("Warehouse not found.\n");
                }
                break;
            case 6:
                printWarehouses(region);
                break;
            case 7:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                warehouse = findWarehouse(region, warehouseName);
                if (warehouse != NULL) {
                    printInventory(warehouse);
                } else {
                    printf("Warehouse not found.\n");
                }
                break;
            case 8:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                warehouse = findWarehouse(region, warehouseName);
                if (warehouse != NULL) {
                    float totalCost = calculateTotalCost(warehouse);
                    printf("Total Cost of Inventory: %.2f\n", totalCost);
                } else {
                    printf("Warehouse not found.\n");
                }
                break;
            case 9:
                printf("Enter warehouse name: ");
                scanf("%s", warehouseName);
                warehouse = findWarehouse(region, warehouseName);
                if (warehouse != NULL) {
                    reportAnalytics(warehouse);
                } else {
                    printf("Warehouse not found.\n");
                }
                break;
            case 10:
                printf("Enter from warehouse index: ");
                scanf("%d", &from);
                printf("Enter to warehouse index: ");
                scanf("%d", &to);
                printf("Enter route weight: ");
                scanf("%d", &weight);
                add_edge(&g, from, to, weight);
                printf("Route added.\n");
                break;
            case 11:
                printf("Enter start warehouse index: ");
                scanf("%d", &start_node);
                printf("Enter end warehouse index: ");
                scanf("%d", &end_node);
                dijkstra(&g, start_node, end_node);
                break;
            case 12:
                printf("Exiting the system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 12);
}

int main() {
    userInterface(); 
    return 0;
}

