#include<stdio.h>
#include<stdlib.h>
#include<String.h>

#define MAX_SIZE 100

typedef struct Stack{
    char stack[MAX_SIZE];
    int top;
}Stack;

void initstack(Stack *s){
    s->top=-1;
}

int isEmpty(Stack *s){
    return s->top == -1;
}

int isFull(Stack *s){
    return s->top == MAX_SIZE-1;
}

void push(Stack *s, char value){
    if(isFull(s)){
        printf("Stack is full!!\n");
    }
    s->stack[++(s->top)]=value;
}

char pop(Stack *s){
    if(isEmpty(s)){
        printf("Stack underflow!!\n");
    }
    return s->stack[(s->top)--];
}

int parantheses(char *expr){
    Stack s;
    initstack (&s);

    for(int i=0; i<strlen(expr); i++){
        char ch=expr[i];
        if(ch=='(' || ch=='{' || ch=='['){
            push(&s, ch);
        }
        else if(ch==')' || ch=='}' || ch==']'){
            if(isEmpty(&s)){
                return 0;
            }
            char c = pop(&s);
            if(ch == ')' && c != '(' || ch == '}' && c != '{' || ch == ']' && c != '['){
                return 0;
            }
        }
    }
    return isEmpty(&s);
}

int main(){
    char expr1[100]="(a+b*[c-d)";
    char expr2[100]="[a+{b-c(a*c)+(b*c)}]";

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