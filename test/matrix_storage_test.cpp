#include "matrix_storage.h"
#include "matrix.h"
#include <gtest/gtest.h>

TEST(MatrixStorageTest, WriteReadDefault) {
    Matrix matrixIn;
    const int secondsIn = 5;

    ASSERT_TRUE(MatrixStorage::saveMatrix(matrixIn, secondsIn));

    Matrix matrixOut;
    int secondsOut = 0;
    ASSERT_TRUE(MatrixStorage::loadMatrix(matrixOut, secondsOut));

    ASSERT_EQ(matrixIn, matrixOut);
    ASSERT_EQ(secondsIn, secondsOut);
}

TEST(MatrixStorageTest, WriteReadShuffled) {
    Matrix matrixIn;
    const int secondsIn = 12345678;
    matrixIn.shuffle(DifficultLevel::Normal);

    ASSERT_TRUE(MatrixStorage::saveMatrix(matrixIn, secondsIn));

    Matrix matrixOut;
    int secondsOut = 0;
    ASSERT_TRUE(MatrixStorage::loadMatrix(matrixOut, secondsOut));

    ASSERT_EQ(matrixIn, matrixOut);
    ASSERT_EQ(secondsIn, secondsOut);
}
