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

// Function to append a node with given data to the end of the list
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

// Recursive function to find the middle node
struct Node* findMiddleHelper(struct Node* slow, struct Node* fast) {
    // Base case: when fast pointer reaches the end or one before the end
    if (fast == NULL || fast->next == NULL) {
        return slow;
    }

    // Move slow pointer one step and fast pointer two steps
    return findMiddleHelper(slow->next, fast->next->next);
}

// Wrapper function to find the middle node
struct Node* findMiddle(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }
    return findMiddleHelper(head, head);
}

int main() {
    struct Node* head = NULL;

    int n;
    int val;
    printf("Enter no. of nodes list: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter value: ");
        scanf("%d", &val);

        appendNode(&head, val);
    }
    
    // Find the middle node
    struct Node* middle = findMiddle(head);

    // Print the middle node
    if (middle != NULL) {
        printf("Middle Node: %d\n", middle->data);
    } else {
        printf("The list is empty.\n");
    }

    return 0;
}
