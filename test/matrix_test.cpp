#include "matrix.h"
#include <gtest/gtest.h>

TEST(MatrixTest, DefaultCtor) {
    Matrix matrix;
    ASSERT_TRUE(matrix.isValid());
}

TEST(MatrixTest, Reset) {
    Matrix matrix;
    
    matrix.reset();
    ASSERT_TRUE(matrix.isValid());
}

TEST(MatrixTest, Shuffle) {
    {
        Matrix matrix;    
        matrix.shuffle(DifficultLevel::Easy);
        ASSERT_FALSE(matrix.isValid());
    }
    {
        Matrix matrix;    
        matrix.shuffle(DifficultLevel::Hard);
        ASSERT_FALSE(matrix.isValid());
    }
    {
        Matrix matrix;    
        matrix.shuffle(DifficultLevel::Normal);
        ASSERT_FALSE(matrix.isValid());
    }
}

TEST(MatrixTest, SetGet) {
    Matrix matrix;
    MatrixItem item;

    item.setUserValue(1);
    matrix.setItem(0, 0, item);
    auto res = matrix.getItem(0, 0);
    ASSERT_EQ(res.value(), 1);

    item.setUserValue(2);
    matrix.setItem(1, 1, item);
    res = matrix.getItem(1, 1);
    ASSERT_EQ(res.value(), 2);

    item.setUserValue(3);
    matrix.setItem(matrix.rows() - 1, 0, item);
    res = matrix.getItem(matrix.rows() - 1, 0);
    ASSERT_EQ(res.value(), 3);

    item.setUserValue(4);
    matrix.setItem(0, matrix.columns() - 1, item);
    res = matrix.getItem(0, matrix.columns() - 1);
    ASSERT_EQ(res.value(), 4);

    item.setUserValue(5);
    matrix.setItem(matrix.rows() - 1, matrix.columns() - 1, item);
    res = matrix.getItem(matrix.rows() - 1, matrix.columns() - 1);
    ASSERT_EQ(res.value(), 5);
}

TEST(MatrixTest, Equaity) {
    {
        Matrix matrix1;
        Matrix matrix2;
        ASSERT_EQ(matrix1, matrix2);
    }

    {
        Matrix matrix1;
        Matrix matrix2;

        MatrixItem item;
        item.setUserValue(7);
        matrix2.setItem(0, 0, item);

        ASSERT_NE(matrix1, matrix2);
    }
}
