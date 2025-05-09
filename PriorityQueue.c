#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;  // The value (priority) of the element
    struct Node* next;
};

// Front of the priority queue
struct Node* front = NULL;

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the priority queue is empty
int isEmpty() {
    return (front == NULL);
}

// Function to add an element to the priority queue (enqueue)
void enqueue(int value) {
    struct Node* newNode = createNode(value);
    
    // If the queue is empty or the new node has higher priority than the front
    if (isEmpty() || value > front->data) {
        newNode->next = front;
        front = newNode;
    } else {
        // Traverse the list to find the appropriate position for the new node
        struct Node* temp = front;
        while (temp->next != NULL && temp->next->data >= value) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    printf("Enqueued %d with priority %d\n", value, value);
}

// Function to remove the element with the highest priority (dequeue)
int dequeue() {
    if (isEmpty()) {
        printf("Priority queue is empty. Cannot dequeue\n");
        return -1;
    }

    int dequeuedValue = front->data;
    struct Node* temp = front;
    
    // Move front to the next node
    front = front->next;

    // Free the dequeued node
    free(temp);

    printf("Dequeued element with priority %d\n", dequeuedValue);
    return dequeuedValue;
}

// Function to display the elements of the priority queue
void display() {
    if (isEmpty()) {
        printf("Priority queue is empty.\n");
        return;
    }

    struct Node* temp = front;
    printf("Priority queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate the priority queue operations
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
