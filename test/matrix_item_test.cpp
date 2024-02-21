#include "matrix_item.h"
#include <gtest/gtest.h>

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