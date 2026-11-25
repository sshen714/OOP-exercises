#ifndef BOOK_SHELF_HPP
#define BOOK_SHELF_HPP

#include "Book.hpp"
#include <vector>

class BookShelf {
public:
    BookShelf(BookCategory category);
    BookShelf(BookCategory category, int bookCapacity);

    void setIDRange(int minID, int maxID);
    void addBook(Book book);
    void remove(int bookID);
    [[nodiscard]] Book searchByBookID(int bookID);
    [[nodiscard]] Book searchByBookName(std::string bookName);
    [[nodiscard]] std::vector<Book> getBooks() const;
    [[nodiscard]] BookCategory getCategory() const;
    [[nodiscard]] int getCapacity() const;

private:
    int bookCapacity;
    int minID=0;
    int maxID=999;
    std::vector<Book> books;
    BookCategory category;
};
 
#endif
