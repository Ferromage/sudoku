#pragma once

#include <random>

class Matrix;
enum class DifficultLevel {Easy, Normal, Hard};

class MatrixShuffler {
public:
    MatrixShuffler();

    void shuffleValues(Matrix &matrix);
    void shuffleAttributes(Matrix &matrix, DifficultLevel level);

private:
    static constexpr int actionCount = 100;
    std::mt19937 m_randomGen;

    void transposeMatrix(Matrix &matrix);
    void swapTwoRows(Matrix &matrix);
    void swapTwoColumns(Matrix &matrix);
    void swapTwoRegionsHorizontal(Matrix &matrix);
    void swapTwoRegionsVertical(Matrix &matrix);
};
