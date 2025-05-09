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

// Function to merge two sorted linked lists recursively
struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    // Base cases
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    // Recursive case: Choose the smaller of the two nodes and recurse
    if (list1->data <= list2->data) {
        list1->next = mergeSortedLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeSortedLists(list1, list2->next);
        return list2;
    }
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // Create first sorted linked list: 1 -> 3 -> 5 -> NULL
    int n;
    int val;
    printf("Enter no. of nodes of 1st list: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter value: ");
        scanf("%d", &val);

        appendNode(&list1, val);
    }

    // Create second sorted linked list: 2 -> 4 -> 6 -> NULL
    int m;
    int val1;
    printf("Enter no. of nodes of 2nd list: ");
    scanf("%d", &m);
    for(int i=0;i<n;i++){
        printf("Enter value: ");
        scanf("%d", &val1);

        appendNode(&list2, val1);
    }

    // Merge the two sorted linked lists
    struct Node* mergedList = mergeSortedLists(list1, list2);

    // Print the merged sorted linked list
    printf("Merged Sorted List:\n");
    printList(mergedList);

    return 0;
}
