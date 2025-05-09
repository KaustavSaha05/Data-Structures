#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Student{
    char name[50];
    int rollNumber;
    float marks;
    struct Student* next;
}Student;

void displayStudents(Student *head){
    int i=1;
    while(head!=NULL){
        printf("Student %d\n", i);
        printf("Name: %s\n", head->name);
        printf("Roll Number: %d\n", head->rollNumber);
        printf("Marks: %f\n", head->marks);
        head=head->next;
        i++;
    }
}

void addStudent(Student *head, const char name[], int rollNumber, float marks){
    Student *ptr;
    ptr=(Student*)malloc(sizeof(Student));
    strcpy(ptr->name, name);
    ptr->rollNumber = rollNumber;
    ptr->marks = marks;
    Student *p =  head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = ptr;
    ptr->next = NULL;
    displayStudents(head);
}

void deleteAtHead(Student *head){
    Student *todelete=head;
    head=head->next;
    free(todelete);
    displayStudents(head);
}

void deleteStudent(Student *head, int rollNumber){
    if(head==NULL){
        return;
    }

    if(head->rollNumber == rollNumber){
        deleteAtHead(head);
    }

    Student *temp=head;
    while(temp->next->rollNumber != rollNumber){
        temp=temp->next;
    }
    Student *todelete=temp->next;
    temp->next=temp->next->next;
    free(todelete);
    displayStudents(head);   
}

int searchStudent(Student *head, int rollNumber){
    Student *p = head;
    if(p==NULL){
        return -1;
    }
    int i=0;
    while(p != NULL){
        if(p->rollNumber == rollNumber){
            return i;
            break;
        }
        p=p->next;
        i++;
    }
    
    return -1;
}

int main(){

    Student *head;
    head=(Student*)malloc(sizeof(Student));
    strcpy(head->name,"Kaustav Saha");
    head->rollNumber=01;
    head->marks=92.5;
    head->next=NULL;

    int ch, rollNumber;
    char name[50];
    float marks;
    while(1){
        printf ("enter you choice\n\t1: Display student record\n\t2: Add student record\n\t3: Delete student record\n\t4: Search student\n\t5: Exit\n\nchoice:: ");
		scanf("%d", &ch);
		switch (ch)
		{
			case 1:
				//display
				displayStudents(head);
				break;
			
            case 2:
				//add
				int n;
                printf("Enter no.of details to enter: ");
                scanf("%d", &n);
                while (getchar() != '\n'); 

                for(int i=1;i<=n;i++){
                    printf("Enter name: ");
				    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    printf("Enter roll number: ");
                    scanf("%d", &rollNumber);
                    printf("Enter marks: ");
                    scanf("%f", &marks);
                    while (getchar() != '\n');
			        addStudent(head, name, rollNumber, marks);
                }
				break;
            
            case 3:
				//delete
				printf ("enter roll number to be deleted:: ");
				scanf ("%d", &rollNumber);
			    deleteStudent(head, rollNumber);
				break;
            
            case 4:
                //search
                int a, m;
                printf("Enter roll number to search: ");
                scanf("%d", &m);
                a = searchStudent(head, m);
                if(a != -1){
                    printf("Student record found at index: %d\n ", a);
                }
                else{
                    printf("Student record not found!\n");
                }
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