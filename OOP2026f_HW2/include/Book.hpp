#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

enum class BookCategory {
    GENERAL = 000,
    PHILOSOPHY = 100,
    RELIGION = 200,
    SCIENCE = 300,
    APPLIED_SCIENCE = 400,
    SOCIAL_SCIENCE = 500,
    HISTORY_GEOGRAPHY_CHINA = 600,
    HISTORY_GEOGRAPHY_WORLD = 700,
    LANGUAGE_LITERATURE = 800,
    ARTS = 900
};

class Book {
public:

    Book(std::string bookName, int bookID);

    Book(std::string bookName, int bookID, std::string bookAuthor, BookCategory category);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getID() const;
    [[nodiscard]] std::string getAuthor() const;
    [[nodiscard]] BookCategory getCategory() const;

private:
    std::string name;
    int id;
    std::string author;
    BookCategory category;
};

#endif
