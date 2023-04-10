#ifndef BOOK_H
#define BOOK_H

struct Book {
    int bookId;
    char title[100];
    char author[100];
    int isBorrowed;
    char studentId[20];
    int borrowedByStudentId;
    char studentname[100];
};

struct Student {
    char studentId[20];
    char name[100];
    char password[20];
};

struct admin{
    char staffNo[20];
    char name[100];
};




void registerNewBook();
void deleteBook();
void checkAvailableBooks();
void checkBorrowedBooks();
void borrowBook();
void returnBook();
int authentication();

    

#endif