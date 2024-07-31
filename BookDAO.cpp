#include <iostream>
#include "BookAccount.cpp"

using namespace std;

class BookDAO{
public:
	virtual void addBook(BookAccount* BA) = 0;
    virtual void viewAllBook() = 0;
    virtual void updateBook(BookAccount* BA) = 0;
    virtual void deleteBook(BookAccount* BA) = 0;
    virtual void searchBook(BookAccount* BA) = 0;
    virtual void sortBook() = 0;
};