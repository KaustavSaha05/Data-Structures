#include <stdio.h>

#define MAX_SIZE 5  // Maximum size of the circular queue

int queue[MAX_SIZE];  // Array to represent the circular queue
int front = -1;       // Front of the queue
int rear = -1;        // Rear of the queue

// Function to check if the circular queue is empty
int isEmpty() {
    return (front == -1);
}

// Function to check if the circular queue is full
int isFull() {
    return ((rear + 1) % MAX_SIZE == front);
}

// Function to add an element to the rear of the circular queue (enqueue)
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }

    if (isEmpty()) {
        // If the queue is empty, initialize both front and rear to 0
        front = rear = 0;
    } 
    else {
        // Move rear circularly
        rear = (rear + 1) % MAX_SIZE;
    }

    queue[rear] = value;
    printf("Enqueued %d\n", value);
}

// Function to remove an element from the front of the circular queue (dequeue)
int dequeue() {
    if (isEmpty()) {
        printf("Queue is empty. Cannot dequeue\n");
        return -1;
    }

    int dequeuedValue = queue[front];

    if (front == rear) {
        // If only one element was present, reset the queue
        front = rear = -1;
    } else {
        // Move front circularly
        front = (front + 1) % MAX_SIZE;
    }

    return dequeuedValue;
}

// Function to display the elements of the circular queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) {
            break;
        }
        i = (i + 1) % MAX_SIZE;
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

    printf("Dequeued: %d\n", dequeue());
    printf("Dequeued: %d\n", dequeue());

    display();

    if (isEmpty()) {
        printf("Queue is empty.\n");
    } 
    else {
        printf("Queue is not empty.\n");
    }

    enqueue(60);
    enqueue(70);

    display();
    return 0;
}