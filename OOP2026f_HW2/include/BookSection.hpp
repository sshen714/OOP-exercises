#ifndef BOOK_SECTION_HPP
#define BOOK_SECTION_HPP

#include "BookShelf.hpp"

class BookSection {
public:
    BookSection(int bookShelfCapacity);

    void addShelf(BookShelf shelf);
    [[nodiscard]] std::vector<BookShelf> searchByCategory(BookCategory category);
    [[nodiscard]] std::vector<BookShelf> getShelves() const;
    [[nodiscard]] int getCapacity() const;

private:
    int bookShelfCapacity;
    std::vector<BookShelf> shelfs;
};

#endif
