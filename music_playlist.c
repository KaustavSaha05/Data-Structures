#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct song{
    char title[50];
    char artist[50];
    struct song *next;
}Song;

void displayPlaylist(Song *head){
    int i=1;
    while(head!=NULL){
        printf("Song %d\n", i);
        printf("Title: %s\n", head->title);
        printf("Artist: %s\n", head->artist);
        head=head->next;
        i++;
    }
}

void addSong(Song *head, const char title[], const char artist[]){
    Song *ptr;
    ptr = (Song*)malloc(sizeof(Song));
    strcpy(ptr->title, title);
    strcpy(ptr->artist, artist);
    Song *p = head;
    while(p->next != NULL){
        p=p->next;
    }
    p->next=ptr;
    ptr->next=NULL;
    displayPlaylist(head);
}

void deleteAtHead(Song *head){
    Song *todelete = head;
    head=head->next;
    free(todelete);
    displayPlaylist(head);
}

void deleteSong(Song *head , char title[]){
    if (head==NULL){
        return;
    }

    if(strcmp(head->title, title) == 0){
        deleteAtHead(head);
    }

    Song *temp = head;
    while(temp->next != NULL && strcmp(temp->next->title, title) != 0){
        temp=temp->next;
    }
    Song *todelete = temp->next;
    temp->next=temp->next->next;
    free(todelete);
    displayPlaylist(head);
}

int searchSong(Song *head, char title[]){
    Song *p = head;
    if(p==NULL){
        return -1;
    }
    int i=0;
    while(p != NULL){
        if(strcmp(p->title, title) == 0){
            return i;
        }
        p=p->next;
        i++;
    }
    return -1;
}

int main(){
    Song *head;
    head=(Song *)malloc(sizeof(Song));
    strcpy(head->title, "Teri Deewani");
    strcpy(head->artist, "Kailash Kher");
    head->next=NULL;

    int ch;
    char artist[50];
    char title[50];

    while(1){
        printf ("enter you choice\n\t1: Display the playlist\n\t2: Add a song\n\t3: Delete song\n\t4: Search song\n\t5: Exit\n\nchoice:: ");
		scanf("%d", &ch);
        while (getchar() != '\n'); 
		switch (ch)
		{
			case 1:
				//display
				displayPlaylist(head);
				break;
			
            case 2:
				//add
				int n;
                printf("Enter no.of details to enter: ");
                scanf("%d", &n);
                while (getchar() != '\n'); 

                for(int i=1;i<=n;i++){
                    printf("Enter title: ");
				    fgets(title, sizeof(title), stdin);
                    title[strcspn(title, "\n")] = '\0';
                    printf("Enter artist ");
                    fgets(artist, sizeof(artist), stdin);
                    artist[strcspn(artist, "\n")] = '\0';
			        addSong(head, title, artist);
                }
				break;
            
            case 3:
				//delete
				printf ("Enter title of song to delete: ");
				fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
			    deleteSong(head, title);
				break;
            
            case 4:
                //search
                int a;
                printf("Enter song title to search: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                a = searchSong(head, title );
                if(a != -1){
                    printf("Song found at index: %d\n ", a);
                }
                else{
                    printf("Song not found!\n");
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
