#include "Book.hpp"

std::string Book::getName() const {
    return name ;
}

int Book::getID() const {
    return id ;
}

std::string Book::getAuthor() const {
    return author ;
}

BookCategory Book::getCategory() const {
    return category;
}

Book::Book(std::string bookName, int bookID) {
    name = bookName ;
    id = bookID ;
    author = "Unknown" ;
    category = BookCategory::GENERAL;
}

Book::Book(std::string bookName, int bookID, std::string bookAuthor, BookCategory category) {
    name = bookName ;
    id = bookID ;
    author = bookAuthor ;
    this->category = category;
}
