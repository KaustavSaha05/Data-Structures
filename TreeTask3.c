#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to calculate height of the tree
int height(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// Function to check if a tree is balanced
bool isBalanced(struct Node* root) {
    if (root == NULL) {
        return true;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return true;
    }

    return false;
}

// Helper function to validate BST
bool isBSTUtil(struct Node* node, int min, int max) {
    if (node == NULL) {
        return true;
    }

    if (node->data < min || node->data > max) {
        return false;
    }

    return isBSTUtil(node->left, min, node->data - 1) && 
           isBSTUtil(node->right, node->data + 1, max);
}

// Function to check if a tree is a BST
bool isBST(struct Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// Function to calculate the diameter of the tree
int diameter(struct Node* root, int* height) {
    int leftHeight = 0, rightHeight = 0;
    int leftDiameter = 0, rightDiameter = 0;

    if (root == NULL) {
        *height = 0;
        return 0;
    }

    leftDiameter = diameter(root->left, &leftHeight);
    rightDiameter = diameter(root->right, &rightHeight);

    *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    return (leftHeight + rightHeight + 1) > (leftDiameter > rightDiameter ? leftDiameter : rightDiameter) 
        ? (leftHeight + rightHeight + 1) 
        : (leftDiameter > rightDiameter ? leftDiameter : rightDiameter);
}

// Wrapper function to initiate the diameter calculation
int getDiameter(struct Node* root) {
    int height = 0;
    return diameter(root, &height);
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the tree
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Main function
int main() {
    struct Node* root = NULL;
    int n, data, choice;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    printf("\nChoose an option:\n");
    printf("1. Check if tree is balanced\n");
    printf("2. Check if tree is a BST\n");
    printf("3. Find the diameter of the tree\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (isBalanced(root)) {
                printf("The tree is balanced.\n");
            } else {
                printf("The tree is not balanced.\n");
            }
            break;
        case 2:
            if (isBST(root)) {
                printf("The tree is a valid BST.\n");
            } else {
                printf("The tree is not a valid BST.\n");
            }
            break;
        case 3:
            printf("The diameter of the tree is %d.\n", getDiameter(root));
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}



