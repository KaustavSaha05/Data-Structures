#include<stdio.h>
#include<Stdlib.h>
#include<string.h>

typedef struct Stack{
    char data;
    struct Stack *next;
}Stack;

Stack *top = NULL;

void push(char value){
    Stack *newnode;
    newnode=(Stack*)malloc(sizeof(Stack));
    newnode->data = value;
    newnode->next = top;
    top = newnode;
}

char pop(){
    if (!top) {
        printf("Stack Underflow!\n");
        return -1; 
    }
    Stack *temp; 
    temp = top;
    char poppedvalue = temp->data;
    top = top->next;
    free(temp);
    return poppedvalue;
}

int isEmpty() {
    return  top == NULL;
}

int parantheses(char *expr){

    for(int i=0; i<strlen(expr); i++){
        char ch=expr[i];
        if(ch=='(' || ch=='{' || ch=='['){
            push(ch);
        }
        else if(ch==')' || ch=='}' || ch==']'){
            if(isEmpty()){
                return 0;
            }
            char c = pop();
            if(ch == ')' && c != '(' || ch == '}' && c != '{' || ch == ']' && c != '['){
                return 0;
            }
        }
    }
    return isEmpty();
}

int main(){
    char expr1[100];
    printf("Enter 1st expression: ");
    fgets(expr1, sizeof(expr1), stdin);
    expr1[strcspn(expr1, "\n")] = '\0';
    
    char expr2[100];
    printf("Enter 2nd expression: ");
    fgets(expr2, sizeof(expr2), stdin);
    expr2[strcspn(expr2, "\n")] = '\0';

    if (parantheses(expr1)) {
        printf("Expression 1 is balanced.\n");
    } else {
        printf("Expression 1 is not balanced.\n");
    }

    if (parantheses(expr2)) {
        printf("Expression 2 is balanced.\n");
    } else {
        printf("Expression 2 is not balanced.\n");
    }
}