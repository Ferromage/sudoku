#include "matrix_item.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

TEST(MatrixItemTest, DefaultCtor) {
    MatrixItem item;
    ASSERT_EQ(item.state(), MatrixItem::State::Generated);
    ASSERT_EQ(item.isGuessed(), true);
    ASSERT_LE(item.value(), 9);
    ASSERT_GE(item.value(), 1);
}

TEST(MatrixItemTest, SetValue) {
    MatrixItem item;
    
    item.setUserValue(1);
    ASSERT_EQ(item.value(), 1);
    ASSERT_EQ(item.state(), MatrixItem::State::UserSetted);

    item.setUserValue(5);
    ASSERT_EQ(item.value(), 5);
    ASSERT_EQ(item.state(), MatrixItem::State::UserSetted);

    item.setUserValue(0);
    ASSERT_EQ(item.value(), 5);
    ASSERT_EQ(item.state(), MatrixItem::State::UserSetted);

    item.setUserValue(9);
    ASSERT_EQ(item.value(), 9);
    ASSERT_EQ(item.state(), MatrixItem::State::UserSetted);

    item.setUserValue(10);
    ASSERT_EQ(item.value(), 9);
    ASSERT_EQ(item.state(), MatrixItem::State::UserSetted);
}

TEST(MatrixItemTest, Output) {
    MatrixItem item;

    {
        std::ostringstream oss;
        oss << item;
        ASSERT_EQ(oss.str(), std::string("100"));
    }

    {
        std::ostringstream oss;
        item.setUserValue(5);
        oss << item;
        ASSERT_EQ(oss.str(), std::string("152"));
    }

    {
        std::ostringstream oss;
        item.setUserValue(6);
        oss << item;
        ASSERT_EQ(oss.str(), std::string("162"));
    }
}

TEST(MatrixItemTest, Input) {
    MatrixItem item;

    {
        std::istringstream oss("000");
        oss >> item;
        ASSERT_EQ(item.state(), MatrixItem::State::Generated);
        ASSERT_EQ(item.value(), 0);
    }

    {
        std::istringstream oss("552");
        oss >> item;
        ASSERT_EQ(item.state(), MatrixItem::State::UserSetted);
        ASSERT_EQ(item.value(), 5);
    }
}

TEST(MatrixItemTest, Equality) {
    {
        MatrixItem item1;
        MatrixItem item2;
        ASSERT_EQ(item1, item2);
    }

    {
        MatrixItem item1;
        MatrixItem item2;
        item1.setUserValue(1);
        ASSERT_NE(item1, item2);
    }
}
