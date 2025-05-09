#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Recursive function to calculate the length of the linked list
int getLength(struct Node* head) {
    // Base case: If the current node is NULL, the length is 0
    if (head == NULL) {
        return 0;
    }
    
    // Recursive case: Return 1 (for the current node) plus the length of the rest of the list
    return 1 + getLength(head->next);
}

// Function to create a new node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a new node at the end of the list
void appendNode(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* temp = *headRef;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int main() {
    struct Node* head = NULL;

    // Creating a linked list: 1 -> 2 -> 3 -> 4 -> NULL
    //appendNode(&head, 1);
    //appendNode(&head, 2);
    //appendNode(&head, 3);
    //appendNode(&head, 4);

    int n;
    int val;
    printf("Enter no. of nodes: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter value: ");
        scanf("%d", &val);

        appendNode(&head, val);
    }
    // Calculate and print the length of the linked list
    int length = getLength(head);
    printf("Length of the linked list: %d\n", length);

    return 0;
}
