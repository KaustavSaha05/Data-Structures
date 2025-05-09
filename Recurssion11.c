#include <stdio.h>
#include <stdlib.h>

// Linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to reverse the linked list recursively
struct Node* reverse(struct Node* node) {
    if (node == NULL || node->next == NULL) {
        return node;
    }
    struct Node* rest = reverse(node->next);
    node->next->next = node;
    node->next = NULL;
    return rest;
}

// Function to print the linked list
void print(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to insert a new node at the beginning of the list
void push(struct Node** head_ref, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = *head_ref;
    *head_ref = temp;
}

int main() {
    struct Node* head = NULL;
    push(&head, 20);
    push(&head, 4);
    push(&head, 15);
    push(&head, 85);

    printf("Given linked list:\n");
    print(head);

    head = reverse(head);

    printf("Reversed Linked list:\n");
    print(head);

    return 0;
}

