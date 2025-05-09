#include <stdio.h>

#define MAX_SIZE 5  // Maximum size of the queue

int queue[MAX_SIZE]; // Array to represent the queue
int front = -1;      // Front of the queue
int rear = -1;       // Rear of the queue

// Function to check if the queue is empty
int isEmpty() {
    return (front == -1 && rear == -1);
}

// Function to check if the queue is full
int isFull() {
    return (rear == MAX_SIZE - 1);
}

// Function to add an element to the rear of the queue (enqueue)
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }
    if (isEmpty()) {
        front = 0;  // Initialize front when adding the first element
    }
    rear++;
    queue[rear] = value;
    printf("Enqueued %d\n", value);
}

// Function to remove an element from the front of the queue (dequeue)
int dequeue() {
    if (isEmpty()) {
        printf("Queue is empty. Cannot dequeue\n");
        return -1;
    }
    int dequeuedValue = queue[front];
    if (front == rear) {
        // Reset the queue after last element is dequeued
        front = rear = -1;
    } 
    else {
        front++;
    }
    return dequeuedValue;
}

// Function to display the elements of the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main(){
    int n, m;
    printf("Enter number of elements to enter: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("Enter element: ");
        scanf("%d", &m);
        enqueue(m);
    }
    display();
    printf("Dequeued value: %d\n", dequeue());
    display();
}