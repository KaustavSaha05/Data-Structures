#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    int data;
    struct Stack* top;
}Stack;

void display(Stack *head){
    while(head!=NULL){
        printf("Element: %d\n", head->data);
        head=head->top;
    }
}

void push(Stack* head, int value){
    Stack *ptr;
    ptr=(Stack*)malloc(sizeof(Stack));
    ptr->data = value;
    Stack *p =  head;
    while(p->top != NULL){
        p = p->top;
    }
    p->top = ptr;
    ptr->top = NULL;
    printf("Element pushed into the stack successfully!!\n");
}

void pop(Stack* head){
    if (head == NULL) {  // Check if the stack is empty
        printf("Stack underflow! No element to pop.\n");
        return;
    }

    Stack *p = head;
    if(p->top == NULL){
        printf("Element popped: %d\n", p->data);
        free(p);
        head=NULL;
    }  
    else{
        while(p->top->top != NULL){
            p = p->top;
        }
        printf("Element popped: %d\n", p->top->data );
        free(p->top);
        p->top = NULL;  
    }  
}

int main(){
    Stack *head;
    head=(Stack*)malloc(sizeof(Stack));
    head->data=2;
    head->top=NULL;

    int n;
    
    while(1){
        printf("enter you choice\n\t1: Push element\n\t2: Display elements in stack\n\t3: Pop element and print\n\nchoice:: ");
        scanf("%d", &n);
        switch (n)
        {
            case 1:
                //Push
                int value;
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(head, value);
                break;

            case 2:
                //Display
                display(head);
                break;

            case 3:
                //Pop
                pop(head);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid input!!\n");
        }
    }
    return 0;
}




