#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define the stack structure
struct StackNode {
    int data;
    struct StackNode* next;
};

// Create a new stack node
struct StackNode* createNode(int value) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize an empty stack
struct StackNode* initializeStack() {
    return NULL;
}

// Check if the stack is empty
int isEmpty(struct StackNode* stack) {
    return (stack == NULL);
}

// Push an element onto the stack
void push(struct StackNode** stack, int value) {
    struct StackNode* newNode = createNode(value);
    newNode->next = *stack;
    *stack = newNode;
}

// Pop an element from the stack
int pop(struct StackNode** stack) {
    if (isEmpty(*stack)) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    struct StackNode* temp = *stack;
    *stack = (*stack)->next;
    int poppedValue = temp->data;
    free(temp);
    return poppedValue;
}

// Evaluate postfix expression
int evaluatePostfixExpression(const char* expression) {
    struct StackNode* stack = initializeStack();
    int i, operand1, operand2, result;

    for (i = 0; expression[i]; ++i) {
        // Skip spaces
        if (expression[i] == ' ') {
            continue;
        }

        // If the character is a digit, push it onto the stack
        if (isdigit(expression[i])) {
            push(&stack, expression[i] - '0'); // Convert char to integer
        } else {
            // Pop two operands from the stack
            operand2 = pop(&stack);
            operand1 = pop(&stack);

            // Perform the operation
            switch (expression[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator: %c\n", expression[i]);
                    exit(EXIT_FAILURE);
            }

            // Push the result back onto the stack
            push(&stack, result);
        }
    }

    // The final result will be the only element left in the stack
    result = pop(&stack);
    return result;
}

int main() {
    // Remove spaces between operands/operators
    char postfixExpression[] = "231*+9-"; 
    int result = evaluatePostfixExpression(postfixExpression);
    printf("Result of postfix expression: %d\n", result);
    return 0;
}
