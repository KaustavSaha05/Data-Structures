#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Declare front and rear of the queue
struct Node* front = NULL;
struct Node* rear = NULL;

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the queue is empty
int isEmpty() {
    return (front == NULL);
}

// Function to add an element to the rear of the queue (enqueue)
void enqueue(int value) {
    struct Node* newNode = createNode(value);
    
    if (isEmpty()) {
        // If the queue is empty, both front and rear point to the new node
        front = rear = newNode;
    } else {
        // Attach the new node to the end of the queue and update the rear
        rear->next = newNode;
        rear = newNode;
    }
    
    printf("Enqueued %d\n", value);
}

// Function to remove an element from the front of the queue (dequeue)
int dequeue() {
    if (isEmpty()) {
        printf("Queue is empty. Cannot dequeue\n");
        return -1;
    }

    int dequeuedValue = front->data;
    struct Node* temp = front;
    
    // Move the front to the next node
    front = front->next;
    
    // If the queue becomes empty after dequeue, set rear to NULL as well
    if (front == NULL) {
        rear = NULL;
    }

    // Free the dequeued node
    free(temp);

    printf("Dequeued %d\n", dequeuedValue);
    return dequeuedValue;
}

// Function to display the elements of the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate the queue operations
int main() {
    int n, m;
    printf("Enter number of elements to enqueue: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("Enter: ");
        scanf("%d", &m);
        enqueue(m);
    }
    display();
    dequeue();
    dequeue();
    display();
    return 0;
}
