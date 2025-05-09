#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert nodes in a binary tree
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    char direction;
    printf("Where do you want to insert %d? (L/R from %d): ", data, root->data);
    scanf(" %c", &direction);
    
    if (direction == 'L' || direction == 'l') {
        root->left = insert(root->left, data);
    } else if (direction == 'R' || direction == 'r') {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Pre-order traversal
void preOrder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// In-order traversal
void inOrder(struct Node* root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

// Post-order traversal
void postOrder(struct Node* root) {
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

// Function to find the height of the binary tree
int findHeight(struct Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

// Function to count leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    
    if (root->left == NULL && root->right == NULL)
        return 1;
    
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int main() {
    struct Node* root = NULL;
    int n, data;

    // Input the number of nodes
    printf("Enter the number of nodes in the binary tree: ");
    scanf("%d", &n);

    // Input the elements of the binary tree
    printf("Enter the elements of the binary tree: \n");
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        if (root == NULL) {
            root = createNode(data);  // Set the first element as root
        } else {
            root = insert(root, data);  // Insert subsequent elements
        }
    }

    // Display traversal results
    printf("\nPre-order Traversal: ");
    preOrder(root);

    printf("\nIn-order Traversal: ");
    inOrder(root);

    printf("\nPost-order Traversal: ");
    postOrder(root);

    // Find height
    int height = findHeight(root);
    printf("\n\nHeight of the binary tree: %d", height);

    // Count leaf nodes
    int leafCount = countLeafNodes(root);
    printf("\nNumber of leaf nodes: %d\n", leafCount);

    return 0;
}
