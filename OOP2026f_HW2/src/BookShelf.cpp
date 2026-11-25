#include "BookShelf.hpp"
#include <string>
#include <stdexcept>
#include <algorithm>

BookShelf::BookShelf(BookCategory category) {

    this->bookCapacity = 1000;
    this->category = category;
}

BookShelf::BookShelf(BookCategory category, int bookCapacity) {

    this->bookCapacity = bookCapacity;
    this->category = category;
}

void BookShelf::setIDRange(int minID, int maxID) {

    int capacity = getCapacity() ;
    int range = maxID-minID+1 ;

    if ((minID >maxID) || (range >capacity)) { throw std::invalid_argument(""); }

    this->minID = minID;
    this->maxID = maxID;
}

void BookShelf::addBook(Book book) {

    if (book.getID() > maxID  || book.getID() < minID ) { throw std::invalid_argument(""); }
    if (book.getCategory() != category ){ throw std::invalid_argument(""); }
    if (books.size() >= bookCapacity ){ throw std::overflow_error(""); }

    for (const Book& existingBook : books) {
        if (existingBook.getID() == book.getID() ){throw std::invalid_argument(""); }
    }

    books.push_back(book);

    std::sort(books.begin(),books.end(),[](const auto& a,const auto& b ){
        return a.getID() < b.getID() ;
    });

}

void BookShelf::remove(int bookID) {

    for (auto i=books.begin(); i !=books.end(); i++) {
        if (i->getID() == bookID) {
            books.erase(i);
            return;
        }
    }
    throw std::invalid_argument("");
}

Book BookShelf::searchByBookID(int bookID) {

    for (const Book& book : books) {
        if (book.getID() == bookID) {return book; }
    }

    throw std::invalid_argument("");
}

Book BookShelf::searchByBookName(std::string bookName) {

    for (const Book& book : books) {
        if (book.getName()== bookName) {return book; }
    }

    throw std::invalid_argument("");
}

std::vector<Book> BookShelf::getBooks() const { return books; }

BookCategory BookShelf::getCategory() const { return category; }

int BookShelf::getCapacity() const { return bookCapacity; }