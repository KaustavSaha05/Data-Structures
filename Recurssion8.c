#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

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

int search(struct Node* head, int target) {
    // Base case: If the current node is NULL, the value is not found
    if (head == NULL) {
        return 0;
    }
    
    // If the current node contains the target value, return 1 (found)
    if (head->data == target) {
        return 1;
    }
    
    // Recursive case: Continue searching in the next node
    return search(head->next, target);
}

int main() {
    struct Node* head = NULL;

    // Creating a linked list
    int n;
    int val;
    printf("Enter no. of nodes: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter value: ");
        scanf("%d", &val);

        appendNode(&head, val);
    }

    int target;
    printf("Enter value to search: ");
    scanf("%d", &target);

    if (search(head, target)) {
        printf("Value %d found in the linked list.\n", target);
    } else {
        printf("Value %d not found in the linked list.\n", target);
    }

    return 0;
}