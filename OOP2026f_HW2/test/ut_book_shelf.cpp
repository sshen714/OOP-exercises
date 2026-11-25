#include "gtest/gtest.h"
#include "BookShelf.hpp"

TEST(BookShelfTest, test_construct_without_capacity) {
    BookShelf shelf(BookCategory::SCIENCE);

    ASSERT_EQ(shelf.getCategory(), BookCategory::SCIENCE);
    ASSERT_EQ(shelf.getCapacity(), 1000);
}

TEST(BookShelfTest, test_construct) {
    BookShelf shelf(BookCategory::SCIENCE, 50);

    ASSERT_EQ(shelf.getCategory(), BookCategory::SCIENCE);
    ASSERT_EQ(shelf.getCapacity(), 50);
}

TEST(BookShelfTest, test_set_id_range) {
    BookShelf shelf(BookCategory::SCIENCE, 50);

    ASSERT_NO_THROW(shelf.setIDRange(1000, 1049));
}

TEST(BookShelfTest, test_set_invalid_id_range) {
    BookShelf shelf(BookCategory::SCIENCE, 50);

    ASSERT_THROW(shelf.setIDRange(1, 1000), std::invalid_argument);
    ASSERT_THROW(shelf.setIDRange(1050, 1000), std::invalid_argument);
}

TEST(BookShelfTest, test_add_and_remove_book) {
    BookShelf shelf(BookCategory::SCIENCE, 2);
    Book book1("Physics", 1, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 2, "Author B", BookCategory::SCIENCE);

    shelf.addBook(book1);
    shelf.addBook(book2);

    ASSERT_EQ(shelf.getBooks().size(), 2);
}

TEST(BookShelfTest, test_get_books_sorted_by_id) {
    BookShelf shelf(BookCategory::SCIENCE, 3);
    Book book1("Physics", 2, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 1, "Author B", BookCategory::SCIENCE);
    Book book3("Biology", 3, "Author C", BookCategory::SCIENCE);

    shelf.addBook(book1);
    shelf.addBook(book2);
    shelf.addBook(book3);

    auto books = shelf.getBooks();
    ASSERT_EQ(books[0].getID(), 1);
    ASSERT_EQ(books[1].getID(), 2);
    ASSERT_EQ(books[2].getID(), 3);
}

TEST(BookShelfTest, test_out_of_capacity) {
    BookShelf shelf(BookCategory::SCIENCE, 1);
    Book book1("Physics", 1, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 2, "Author B", BookCategory::SCIENCE);
    shelf.addBook(book1);

    ASSERT_THROW(shelf.addBook(book2), std::overflow_error);
}

TEST(BookShelfTest, test_invalid_category) {
    BookShelf shelf(BookCategory::SCIENCE, 1);
    Book book("Physics", 1, "Author A", BookCategory::RELIGION);

    ASSERT_THROW(shelf.addBook(book), std::invalid_argument);
}

TEST(BookShelfTest, add_duplicate_book_id) {
    BookShelf shelf(BookCategory::SCIENCE, 5);
    Book book1("Physics", 1, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 2, "Author B", BookCategory::SCIENCE);

    shelf.addBook(book1);
    shelf.addBook(book2);

    ASSERT_THROW(shelf.addBook(book1), std::invalid_argument);
}

TEST(BookShelfTest, test_remove_non_existent_book) {
    BookShelf shelf(BookCategory::SCIENCE, 2);
    Book book1("Physics", 1, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 2, "Author B", BookCategory::SCIENCE);

    shelf.addBook(book1);
    shelf.addBook(book2);

    ASSERT_THROW(shelf.remove(9999), std::invalid_argument);
}

TEST(BookShelfTest, test_add_invalid_id_range) {
    BookShelf shelf(BookCategory::SCIENCE, 50);
    shelf.setIDRange(1000, 1049);

    ASSERT_THROW(shelf.addBook(Book("Biology", 999, "Author C", BookCategory::SCIENCE)), std::invalid_argument); // ID below range
    ASSERT_THROW(shelf.addBook(Book("Biology", 1050, "Author C", BookCategory::SCIENCE)), std::invalid_argument); // ID above range
}

TEST(BookShelfTest, test_search_book_by_id) {
    BookShelf shelf(BookCategory::SCIENCE, 2);
    Book book1("Physics", 1, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 2, "Author B", BookCategory::SCIENCE);

    shelf.addBook(book1);
    shelf.addBook(book2);

    ASSERT_EQ(shelf.searchByBookID(1).getName(), "Physics");
    ASSERT_THROW(shelf.searchByBookID(999), std::invalid_argument);
}

TEST(BookShelfTest, test_search_book_by_name) {
    BookShelf shelf(BookCategory::SCIENCE, 2);
    Book book1("Physics", 1, "Author A", BookCategory::SCIENCE);
    Book book2("Chemistry", 2, "Author B", BookCategory::SCIENCE);

    shelf.addBook(book1);
    shelf.addBook(book2);

    ASSERT_EQ(shelf.searchByBookName("Chemistry").getID(), 2);
    ASSERT_THROW(shelf.searchByBookName("Biology"), std::invalid_argument);
}