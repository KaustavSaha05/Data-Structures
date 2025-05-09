#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Task{
    char description[100];
    int taskid;
    int priority;
    struct Task* next;
}Task;

void displayTask(Task *head){
    int i=1;
    while(head!=NULL){
        printf("Task %d\n", i);
        printf("Task ID: %d\n", head->taskid);
        printf("Description: %s\n", head->description);
        printf("Priority: %d\n", head->priority);
        head=head->next;
        i++;
    }
}

void addTask(Task *head, int taskid, const char description[], int priority){
    Task *ptr;
    ptr=(Task*)malloc(sizeof(Task));
    strcpy(ptr->description, description);
    ptr->taskid = taskid;
    ptr->priority = priority;
    Task *p =  head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = ptr;
    ptr->next = NULL;
    displayTask(head);
}

void deleteAtHead(Task *head){
    Task *todelete=head;
    head=head->next;
    free(todelete);
    displayTask(head);
}

void deleteTask(Task *head, int taskid){
    if(head==NULL){
        return;
    }

    if(head->taskid == taskid){
        deleteAtHead(head);
    }

    Task *temp=head;
    while(temp->next->taskid != taskid){
        temp=temp->next;
    }
    Task *todelete=temp->next;
    temp->next=temp->next->next;
    free(todelete);
    displayTask(head);   
}

int searchTask(Task *head, int taskid){
    Task *p = head;
    if(p==NULL){
        return -1;
    }
    int i=0;
    while(p != NULL){
        if(p->taskid == taskid){
            return i;
        }
        p=p->next;
        i++;
    }
    
    return -1;
}

int main(){

    Task *head;
    head=(Task*)malloc(sizeof(Task));
    strcpy(head->description,"Management");
    head->taskid=01;
    head->priority=01;
    head->next=NULL;

    int ch, taskid, priority;
    char description[100];
    while(1){
        printf ("enter you choice\n\t1: Display tasks\n\t2: Add task\n\t3: Delete task\n\t4: Search task\n\t5: Priority list\n\t6: Exit\n\nchoice:: ");
		scanf("%d", &ch);
		switch (ch)
		{
			case 1:
				//display
				displayTask(head);
				break;
			
            case 2:
				//add
				int n;
                printf("Enter no.of tasks to enter: ");
                scanf("%d", &n);
                while (getchar() != '\n'); 

                for(int i=1;i<=n;i++){
                    printf("Enter taskid: ");
                    scanf("%d", &taskid);
                    while (getchar() != '\n'); 

                    printf("Enter description: ");
				    fgets(description, sizeof(description), stdin);
                    description[strcspn(description, "\n")] = '\0';

                    printf("Enter priority: ");
                    scanf("%d", &priority);
                    while (getchar() != '\n');
			        addTask(head, taskid, description, priority);
                }
				break;
            
            case 3:
				//delete
				printf ("enter task ID to be deleted:: ");
				scanf ("%d", &taskid);
			    deleteTask(head, taskid);
				break;
            
            case 4:
                //search
                int m, a;
                printf("Enter task ID to search: ");
                scanf("%d", &m);
                a = searchTask(head, m);
                if(a != -1){
                    printf("Task record found at index: %d\n ", a);
                }
                else{
                    printf("Task not found!\n");
                }
                break;
            
            case 5:
                //prioritize
            
            default:
				//free the head
				free(head);
				printf ("Bye Bye!\n");
				exit(0);
        }
    }
    
    return 0;
}