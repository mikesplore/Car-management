#include <stdio.h>
#include <string.h>
#include "book.h"
#include <stdlib.h>
#include <time.h>


int rando() {
    srand(time(NULL));
    return rand() % 9000 + 1000;
    }
    

void registerNewBook() {
    struct Book book;
    printf("Enter Book ID: ");
    scanf("%d", &book.bookId);
    getchar(); 
    printf("Enter Book Title: ");
    scanf(" %[^\n]s", &book.title);
    getchar();
    printf("Enter Book Author: ");
    scanf(" %[^\n]s", &book.author);
    getchar(); 
    book.isBorrowed = 0;
    book.studentId[0] = '\0';
    book.borrowedByStudentId = -1;
    
    FILE *file = fopen("book.txt", "ab");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    fwrite(&book, sizeof(struct Book), 1, file);
    fclose(file);

    printf("Book registered successfully!\n");
}




void checkAvailableBooks() {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

     printf("\n                            List of Available Books                            \n");
    printf("================================================================================\n");
    printf("                    Book Id      Book title              Book author\n");
    printf("--------------------------------------------------------------------------------\n");

    struct Book book;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (!book.isBorrowed) { 
            printf("                    %d          %s              %s\n", book.bookId, book.title, book.author);
        }
    }

    fclose(file);
}


void borrowBook() {
    int bookIdToBorrow;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookIdToBorrow);
    getchar(); 

    FILE *file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookId == bookIdToBorrow) {
            found = 1;
            break;
        }
    }

    if (found) {
        if (book.isBorrowed) {
            printf("Book with ID %d is already borrowed.\n", bookIdToBorrow);
        } else {
            fseek(file, -sizeof(struct Book), SEEK_CUR);
            book.isBorrowed = 1;
            printf("Enter Student ID: ");
            scanf("%s", book.studentId);
            getchar(); 
            fwrite(&book, sizeof(struct Book), 1, file);

          
            struct Student student;
            printf("Enter Student Name: ");
            scanf(" %[^\n]s", student.name);

            // Append student information to a separate file
            FILE *studentFile = fopen("students.txt", "ab");
            if (studentFile == NULL) {
                printf("Failed to open student file\n");
                return;
            }
            fwrite(&student, sizeof(struct Student), 1, studentFile);
            fclose(studentFile);

            printf("Book with ID %d borrowed successfully!\n", bookIdToBorrow);
        }
    } else {
        printf("Book with ID %d not found.\n", bookIdToBorrow);
    }

    fclose(file);
}


void returnBook() {
    int bookIdToReturn;
    printf("Enter Book ID to return: ");
    scanf("%d", &bookIdToReturn);
    getchar(); 

    FILE *file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookId == bookIdToReturn) {
            found = 1;
            break;
        }
    }

    if (found) {
        if (!book.isBorrowed) {
            printf("Book with ID %d is not currently borrowed.\n", bookIdToReturn);
        } else {
            fseek(file, -sizeof(struct Book), SEEK_CUR);
            book.isBorrowed = 0;
            fwrite(&book, sizeof(struct Book), 1, file);

            
            FILE *studentFile = fopen("students.txt", "r+");
            if (studentFile == NULL) {
                printf("Failed to open student file\n");
                return;
            }
            struct Student student;
            int foundStudent = 0;
            while (fread(&student, sizeof(struct Student), 1, studentFile)) {
                if (strcmp(student.studentId, book.studentId) == 0) {
                    foundStudent = 1;
                    break;
                }
            }
            if (foundStudent) {
                fseek(studentFile, -sizeof(struct Student), SEEK_CUR);
                struct Student emptyStudent = {0}; 
                fwrite(&emptyStudent, sizeof(struct Student), 1, studentFile);
            }
            fclose(studentFile);

            printf("Book with ID %d returned successfully!\n", bookIdToReturn);
        }
    } else {
        printf("Book with ID %d not found.\n", bookIdToReturn);
    }

    fclose(file);
}

void checkBorrowedBooks() {
    FILE *bookFile = fopen("book.txt", "rb");
    if (bookFile == NULL) {
        printf("Failed to open book file\n");
        return;
    }
    printf("\n                            List of Borrowed Books                            \n");
    printf("================================================================================\n");
    printf("                    Student ID           Book ID\n");
    printf("--------------------------------------------------------------------------------\n");

    struct Book book;
    while (fread(&book, sizeof(struct Book), 1, bookFile)) {
        if (book.isBorrowed == 1) {
            printf("                    %s          %d\n", book.studentId, book.bookId);
        }
    }printf("-----------------------------------------------------------------------------\n");

    fclose(bookFile);
}

void deleteBook() {
    int bookId;
    printf("Enter Book ID to delete: ");
    scanf("%d", &bookId);
    getchar(); 

    FILE *file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    struct Book book;
    int found = 0;
    long int offset = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookId == bookId) {
            found = 1;
            break;
        }
        offset = ftell(file);
    }

    if (found) {
        fseek(file, offset, SEEK_SET); // Move file pointer to the beginning of the record to be deleted
        book.bookId = -1; // Set book ID to -1 to mark as deleted
        fwrite(&book, sizeof(struct Book), 1, file);
        printf("Book with ID %d deleted successfully!\n", bookId);
    } else {
        printf("Book with ID %d not found\n", bookId);
    }

    fclose(file);
}
            

 int authentication(int otp) {
    int theotp;
    int count = 0;
     // Generate random OTP using rando() function
    printf("Enter OTP: ");
    do {
        scanf("%d", &theotp);
        if (theotp == otp) {
            return 1;
        } else {
            printf("Invalid OTP, try again\nEnter OTP: ");
            count++;
        }
    } while (count < 3); // Limit loop to run only three times

    printf("Too many attempts. Try again later.\n");
    return 0;
}