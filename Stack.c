#include<stdio.h>
#define MAX_SIZE 5

int stack[MAX_SIZE];
int top=-1;

int isFull(){
    return top==MAX_SIZE-1;
}

int isEmpty(){
    return top==-1;
}

void push(int value){
    if(isFull()){
        printf("Stack overflow!!\n");
    }
    else{
        stack[++top]=value;
        printf("Element pushed into the stack successfully!!\n");
    }
}

void pop(){
    if(isEmpty()){
        printf("Stack underflow!!\n");
    }
    else{
        printf("Popped element: %d\n", stack[top--]);
    }
}

void display(){
    int i;
    if(isEmpty()){
        printf("Stack is empty!!");
    }
    else{
        printf("Stack elements: \n");
        for(i=0;i<=top;i++){
            printf("%d\n", stack[i]);
        }
    }
}

int main(){
    int n;
    
    while(1){
        printf("enter you choice\n\t1: Push element\n\t2: Display elements in stack\n\t3: Pop element and print\n\t4: Check if stack is empty\n\nchoice:: ");
        scanf("%d", &n);
        switch (n)
        {
            case 1:
                //Push
                int value;
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                //Display
                display();
                break;

            case 3:
                //Pop
                pop();
                break;

            case 4:
                //Check
                if(isEmpty()){
                    printf("Stack is empty!!\n");
                }
                else{
                    printf("Stack has elements\n");
                }   
                break;

            case 5:
                return 0;

            default:
                printf("Invalid input!!\n");
        }
    }
    return 0;
}
