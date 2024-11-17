#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 100
#define DATA_FILE "library_data.txt"

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_TITLE_LEN];
    int isBorrowed;
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

void loadBooksFromFile();
void saveBooksToFile();
void addBook();
void displayBooks();
void borrowBook();
void returnBook();
void searchBook();
void menu();

int main() {
    loadBooksFromFile();
    menu();
    saveBooksToFile();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n=== Library Management System ===\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Search Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 5: searchBook(); break;
            case 6: printf("Exiting the program. Goodbye!\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;

    printf("Enter the title of the book: ");
    fgets(newBook.title, MAX_TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter the author of the book: ");
    fgets(newBook.author, MAX_TITLE_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    newBook.isBorrowed = 0;

    library[bookCount++] = newBook;
    printf("Book added successfully! Book ID: %d\n", newBook.id);
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nList of Books:\n");
    printf("ID\tTitle\t\t\tAuthor\t\t\tStatus\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d\t%-20s\t%-20s\t%s\n", library[i].id, library[i].title, library[i].author,
               library[i].isBorrowed ? "Borrowed" : "Available");
    }
}

void borrowBook() {
    int id;
    printf("Enter the book ID to borrow: ");
    scanf("%d", &id);

    if (id < 1 || id > bookCount) {
        printf("Invalid book ID.\n");
        return;
    }

    if (library[id - 1].isBorrowed) {
        printf("Sorry, the book is already borrowed.\n");
    } else {
        library[id - 1].isBorrowed = 1;
        printf("You borrowed the book: %s\n", library[id - 1].title);
    }
}

void returnBook() {
    int id;
    printf("Enter the book ID to return: ");
    scanf("%d", &id);

    if (id < 1 || id > bookCount) {
        printf("Invalid book ID.\n");
        return;
    }

    if (!library[id - 1].isBorrowed) {
        printf("The book is already in the library.\n");
    } else {
        library[id - 1].isBorrowed = 0;
        printf("You returned the book: %s\n", library[id - 1].title);
    }
}

void searchBook() {
    char query[MAX_TITLE_LEN];
    printf("Enter the title of the book to search: ");
    getchar();
    fgets(query, MAX_TITLE_LEN, stdin);
    query[strcspn(query, "\n")] = '\0';

    printf("\nSearch Results:\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, query)) {
            printf("ID: %d, Title: %s, Author: %s, Status: %s\n",
                   library[i].id, library[i].title, library[i].author,
                   library[i].isBorrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found matching the title '%s'.\n", query);
    }
}

void loadBooksFromFile() {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        printf("No previous library data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%d\n", &library[bookCount].id) != EOF) {
        fgets(library[bookCount].title, MAX_TITLE_LEN, file);
        library[bookCount].title[strcspn(library[bookCount].title, "\n")] = '\0'; // Remove newline

        fgets(library[bookCount].author, MAX_TITLE_LEN, file);
        library[bookCount].author[strcspn(library[bookCount].author, "\n")] = '\0'; // Remove newline

        fscanf(file, "%d\n", &library[bookCount].isBorrowed);
        bookCount++;
    }
    fclose(file);
    printf("Library data loaded successfully.\n");
}

void saveBooksToFile() {
    FILE *file = fopen(DATA_FILE, "w");
    if (!file) {
        printf("Error saving library data.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d\n%s\n%s\n%d\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].isBorrowed);
    }
    fclose(file);
    printf("Library data saved successfully.\n");
}
