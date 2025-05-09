#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char title[100];          // Book title
    char author[100];         // Book author
    int publicationYear;      // Year of publication
    struct Book* next;        // Pointer to the next book node
};

struct Genre {
    char genreName[50];       // Genre name
    struct Book* books;       // Pointer to the linked list of books
    struct Genre* next;       // Pointer to the next genre node
};

struct Book* createBookNode(char* title, char* author, int year) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->publicationYear = year;
    newBook->next = NULL;
    return newBook;
}

void insertBookAtFront(struct Book** head, char* title, char* author, int year) {
    struct Book* newBook = createBookNode(title, author, year);
    newBook->next = *head;
    *head = newBook;
}

void deleteBookFromFront(struct Book** head) {
    if (*head == NULL) return;
    struct Book* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void displayBooks(struct Book* head) {
    struct Book* current = head;
    while (current != NULL) {
        printf("Title: %s, Author: %s, Year: %d\n", current->title, current->author, current->publicationYear);
        current = current->next;
    }
}

struct Genre* createGenreNode(char* genreName) {
    struct Genre* newGenre = (struct Genre*)malloc(sizeof(struct Genre));
    strcpy(newGenre->genreName, genreName);
    newGenre->books = NULL; // Initialize the book linked list for this genre
    newGenre->next = NULL;
    return newGenre;
}

void insertGenreAtFront(struct Genre** head, char* genreName) {
    struct Genre* newGenre = createGenreNode(genreName);
    newGenre->next = *head;
    *head = newGenre;
}

void deleteGenreFromFront(struct Genre** head) {
    if (*head == NULL) return;
    struct Genre* temp = *head;
    *head = (*head)->next;

    // Free all books in the genre
    struct Book* currentBook = temp->books;
    while (currentBook != NULL) {
        struct Book* tempBook = currentBook;
        currentBook = currentBook->next;
        free(tempBook);
    }

    free(temp);
}

void displayGenres(struct Genre* head) {
    struct Genre* current = head;
    while (current != NULL) {
        printf("Genre: %s\n", current->genreName);
        printf("Books:\n");
        displayBooks(current->books);
        current = current->next;
    }
}

struct Book* searchBookByTitle(struct Genre* genreList, char* title) {
    struct Genre* currentGenre = genreList;
    while (currentGenre != NULL) {
        struct Book* currentBook = currentGenre->books;
        while (currentBook != NULL) {
            if (strcmp(currentBook->title, title) == 0) {
                return currentBook; // Return the found book
            }
            currentBook = currentBook->next;
        }
        currentGenre = currentGenre->next;
    }
    return NULL; // Book not found
}

void updateBookDetails(struct Book* book, char* newAuthor, int newYear) {
    if (book != NULL) {
        strcpy(book->author, newAuthor);
        book->publicationYear = newYear;
    }
}

int main() {
    struct Genre* genreList = NULL;  // Head of the Genre linked list
    struct Genre* genreNode = NULL;  // Moved declaration to the top of the function

    int choice;
    char genreName[50], bookTitle[100], author[100];
    int publicationYear;
    struct Book* foundBook;

    while (1) {
        printf("\nLibrary Catalog Management System\n");
        printf("1. Add Genre\n");
        printf("2. Add Book to Genre\n");
        printf("3. Delete Genre\n");
        printf("4. Delete Book from Genre\n");
        printf("5. Display All Genres and Books\n");
        printf("6. Search Book by Title\n");
        printf("7. Update Book Details\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter genre name: ");
                fgets(genreName, sizeof(genreName), stdin);
                genreName[strcspn(genreName, "\n")] = '\0';
                insertGenreAtFront(&genreList, genreName);
                printf("Genre added successfully.\n");
                break;

            case 2:
                printf("Enter genre name: ");
                fgets(genreName, sizeof(genreName), stdin);
                genreName[strcspn(genreName, "\n")] = '\0';

                // Find the genre where the book should be added
                genreNode = genreList;  // Use the already declared variable
                while (genreNode != NULL && strcmp(genreNode->genreName, genreName) != 0) {
                    genreNode = genreNode->next;
                }

                if (genreNode != NULL) {
                    printf("Enter book title: ");
                    fgets(bookTitle, sizeof(bookTitle), stdin);
                    bookTitle[strcspn(bookTitle, "\n")] = '\0';
                    printf("Enter author name: ");
                    fgets(author, sizeof(author), stdin);
                    author[strcspn(author, "\n")] = '\0';
                    printf("Enter publication year: ");
                    scanf("%d", &publicationYear);
                    insertBookAtFront(&(genreNode->books), bookTitle, author, publicationYear);
                    printf("Book added to the genre successfully.\n");
                } else {
                    printf("Genre not found!\n");
                }
                break;

            case 3:
                printf("Deleting the first genre from the catalog.\n");
                deleteGenreFromFront(&genreList);
                printf("Genre deleted successfully.\n");
                break;

            case 4:
                printf("Enter genre name: ");
                fgets(genreName, sizeof(genreName), stdin);
                genreName[strcspn(genreName, "\n")] = '\0';;

                genreNode = genreList;
                while (genreNode != NULL && strcmp(genreNode->genreName, genreName) != 0) {
                    genreNode = genreNode->next;
                }

                if (genreNode != NULL) {
                    printf("Deleting the first book from the genre.\n");
                    deleteBookFromFront(&(genreNode->books));
                    printf("Book deleted successfully.\n");
                } else {
                    printf("Genre not found!\n");
                }
                break;

            case 5:
                printf("Displaying all genres and books in the library catalog:\n");
                displayGenres(genreList);
                break;

            case 6:
                printf("Enter the title of the book to search: ");
                fgets(bookTitle, sizeof(bookTitle), stdin);
                bookTitle[strcspn(bookTitle, "\n")] = '\0';
                foundBook = searchBookByTitle(genreList, bookTitle);
                if (foundBook != NULL) {
                    printf("Book found! Title: %s, Author: %s, Year: %d\n", foundBook->title, foundBook->author, foundBook->publicationYear);
                } else {
                    printf("Book not found!\n");
                }
                break;

            case 7:
                printf("Enter the title of the book to update: ");
                fgets(bookTitle, sizeof(bookTitle), stdin);
                bookTitle[strcspn(bookTitle, "\n")] = '\0';
                foundBook = searchBookByTitle(genreList, bookTitle);
                if (foundBook != NULL) {
                    printf("Enter new author name: ");
                    fgets(author, sizeof(author), stdin);
                    author[strcspn(author, "\n")] = '\0';
                    printf("Enter new publication year: ");
                    scanf("%d", &publicationYear);
                    while (getchar() != '\n');
                    updateBookDetails(foundBook, author, publicationYear);
                    printf("Book details updated successfully.\n");
                } else {
                    printf("Book not found!\n");
                }
                break;

            case 8:
                printf("Exiting the system.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
