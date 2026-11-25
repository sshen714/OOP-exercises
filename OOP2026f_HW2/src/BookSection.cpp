#include "BookSection.hpp"
#include <stdexcept>

BookSection::BookSection(int bookShelfCapacity) {
    this->bookShelfCapacity=bookShelfCapacity;
}

void BookSection::addShelf(BookShelf shelf) {

    if (bookShelfCapacity >= shelfs.size()) {
        shelfs.push_back(shelf);
    }
    else { throw std::invalid_argument("");}
}

std::vector<BookShelf> BookSection::searchByCategory(BookCategory category) {

    std::vector<BookShelf> temp;
    bool check =false;
    for (const BookShelf& bookShelf : shelfs) {
        if (bookShelf.getCategory() == category) {
            temp.push_back(bookShelf);
            check=true;
        }
    }

    if (check) { return temp; }
    throw std::invalid_argument("");
}

std::vector<BookShelf> BookSection::getShelves() const {

    return shelfs;
}

int BookSection::getCapacity() const { return bookShelfCapacity; }