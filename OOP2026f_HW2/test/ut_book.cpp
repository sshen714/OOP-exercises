#include "Book.hpp"
#include <gtest/gtest.h>

TEST(BookTest, test_construct_without_author_and_category) {
    Book book = Book("1984", 1234567890);
    ASSERT_EQ("1984", book.getName());
    ASSERT_EQ(1234567890, book.getID());
    ASSERT_EQ("Unknown", book.getAuthor());
    ASSERT_EQ(BookCategory::GENERAL, book.getCategory());
}

TEST(BookTest, test_construct_with_all_parameters) {
    Book book = Book("1984", 1234567890, "George Orwell", BookCategory::LANGUAGE_LITERATURE);
    ASSERT_EQ("1984", book.getName());
    ASSERT_EQ(1234567890, book.getID());
    ASSERT_EQ("George Orwell", book.getAuthor());
    ASSERT_EQ(BookCategory::LANGUAGE_LITERATURE, book.getCategory());
}

TEST(BookTest, enum_category_values) {
    Book book = Book("1984", 1234567890, "George Orwell", BookCategory::SOCIAL_SCIENCE);
    ASSERT_EQ(static_cast<int>(book.getCategory()), 500);
}