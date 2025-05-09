#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

void displayList(Node *head){
    while(head!=NULL){
        printf("Element: %d\n", head->data);
        head=head->next;
    }
}

void insertNode(Node *head, int value){
    Node *ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr->data = value;
    Node *p =  head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = ptr;
    ptr->next = NULL;
    displayList(head);
}

void deleteAtHead(Node *head){
    Node *todelete=head;
    head=head->next;
    free(todelete);
    displayList(head);
}

void deleteNode(Node *head, int value){
    if(head==NULL){
        return;
    }

    if(head->data == value){
        deleteAtHead(head);
    }

    Node *temp=head;
    while(temp->next->data != value){
        temp=temp->next;
    }
    Node *todelete=temp->next;
    temp->next=temp->next->next;
    free(todelete);
    displayList(head);   
}
int searchNode(Node *head, int value){
    Node *p = head;
    if(p==NULL){
        return -1;
    }
    int i=0;
    while(p != NULL){
        if(p->data == value){
            return i;
        }
        p=p->next;
        i++;
    }
    return -1;
}

void reverseNode(Node *head){
    Node *prevptr = NULL;
    Node *current = head;
    Node *nextptr;

    while(current != NULL){
        nextptr=current->next;
        current->next=prevptr;

        prevptr=current;
        current=nextptr;
    }
    displayList(prevptr);
}

int main(){

    Node *head;
    head=(Node*)malloc(sizeof(Node));
    head->data=9;
    head->next=NULL;

    int ch, val;
    while(1){
        printf ("enter you choice\n\t1: Display list\n\t2: Add an element\n\t3: Remove an element\n\t4: Search element\n\t5: Reverse list\n\t6: Exit\n\nchoice:: ");
		scanf("%d", &ch);
		switch (ch)
		{
			case 1:
				//display
				displayList(head);
				break;
			
            case 2:
				//add
				int n;
                printf("Enter no.of terms to enter: ");
                scanf("%d", &n);
                for(int i=1;i<=n;i++){
                    printf("enter value to insert:: ");
				    scanf("%d", &val);
				    insertNode(head, val);
                }
				break;
            
            case 3:
				//delete
				printf ("enter value to be deleted:: ");
				scanf ("%d", &val);
			    deleteNode(head, val);
				break;
            
            case 4:
                //search
                int m, a;
                printf("Enter value to search: ");
                scanf("%d", &m);
                a = searchNode(head, m);
                if(a != -1){
                    printf("Value found at index: %d\n ", a);
                }
                else{
                    printf("Value not found!\n");
                }
                break;

            case 5:
                //reverse
                printf("The reversed linked list is: \n");
                reverseNode(head);
                break;

            default:
				//free the head
				free(head);
				printf ("Bye Bye!\n");
				exit(0);
        }
    }
    
    return 0;
}