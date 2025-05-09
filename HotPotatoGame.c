#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the QueueNode structure
struct QueueNode {
    char name[50];
    struct QueueNode* next;
};

// Function to create an empty queue
struct QueueNode* createQueue() {
    return NULL;
}

// Function to check if the queue is empty
int isEmpty(struct QueueNode* queue) {
    return (queue == NULL);
}

// Function to enqueue a player to the queue
void enqueuePlayer(struct QueueNode** queue, const char* playerName) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, playerName);
    if (*queue == NULL) {
        newNode->next = newNode;  // Circular queue
        *queue = newNode;
    } else {
        struct QueueNode* temp = *queue;
        while (temp->next != *queue) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *queue;
    }
}

// Function to dequeue a player from the queue
void dequeuePlayer(struct QueueNode** queue) {
    if (isEmpty(*queue)) {
        printf("Queue is empty, cannot dequeue.\n");
        return;
    }
    
    struct QueueNode* temp = *queue;
    
    if ((*queue)->next == *queue) {
        *queue = NULL;  // Only one element
    } else {
        struct QueueNode* last = *queue;
        while (last->next != *queue) {
            last = last->next;
        }
        last->next = (*queue)->next;
        *queue = (*queue)->next;
    }
    
    free(temp);
}

// Function to simulate the Hot Potato game
void playHotPotato(struct QueueNode** queue, int passCount) {
    while ((*queue)->next != *queue) {
        for (int i = 0; i < passCount - 1; ++i) {
            *queue = (*queue)->next;  // Pass the potato
        }
        printf("Eliminated: %s\n", (*queue)->name);
        dequeuePlayer(queue);  // Remove the player
    }
    
    printf("Winner: %s\n", (*queue)->name);  // The last remaining player is the winner
}

int main() {
    struct QueueNode* queue = createQueue();
    int numPlayers, passCount;
    
    // Input number of players
    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);
    
    // Input player names
    for (int i = 0; i < numPlayers; ++i) {
        char playerName[50];
        printf("Enter the name of player %d: ", i + 1);
        scanf("%s", playerName);
        enqueuePlayer(&queue, playerName);
    }
    
    // Input the pass count
    printf("Enter the number of passes before eliminating a player: ");
    scanf("%d", &passCount);
    
    // Simulate the Hot Potato game
    playHotPotato(&queue, passCount);
    
    return 0;
}
