#include <gtest/gtest.h>
#include "BookSection.hpp"

TEST(BookSectionTest, test_construct) {
    BookSection section(10);
    ASSERT_EQ(section.getCapacity(), 10);
}

TEST(BookSectionTest, test_add_shelf) {
    BookSection section(10);
    BookShelf shelf(BookCategory::SCIENCE, 5);
    section.addShelf(shelf);
    ASSERT_EQ(section.getShelves().size(), 1);
}

TEST(BookSectionTest, test_search_by_category) {
    BookSection section(10);
    BookShelf shelf1(BookCategory::SCIENCE, 5);
    BookShelf shelf2(BookCategory::SCIENCE, 5);
    BookShelf shelf3(BookCategory::PHILOSOPHY, 5);
    section.addShelf(shelf1);
    section.addShelf(shelf2);
    section.addShelf(shelf3);

    auto shelfs = section.searchByCategory(BookCategory::SCIENCE);
    for (auto shelf: shelfs){
        ASSERT_EQ(shelf.getCategory(), BookCategory::SCIENCE);
    }
}