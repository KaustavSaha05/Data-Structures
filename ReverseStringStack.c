#include<stdio.h>
#include<string.h>
#define MAX_SIZE 10

int stack[MAX_SIZE];
int top=-1;

int isFull(){
    return top==MAX_SIZE-1;
}

int isEmpty(){
    return top==-1;
}

void push(char value){
    if(isFull()){
        printf("Stack overflow!!\n");
    }
    else{
        stack[++top]=value;
    }
}

void pop(){
    if(isEmpty()){
        printf("Stack underflow!!\n");
    }
    else{
        printf("%c", stack[top--]);
    }
}

int main(){
    int n;
    printf("Enter size of string: ");
    scanf("%d", &n);
    while (getchar() != '\n');
    char name[n];
    printf("Enter string: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    for(int i=0;i<n;i++){
        push(name[i]);
    }
    for(int i=n-1;i>=0;i--){
        pop();
    }
}