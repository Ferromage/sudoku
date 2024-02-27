#pragma once

#include "matrix_item.h"
#include "matrix_shuffler.h"
#include <array>

class Matrix {
    friend class MatrixShuffler;
    static constexpr size_t SIZE = 9;    
    
public:
    Matrix();
    Matrix(const Matrix &rhs);

    inline size_t size() const { return SIZE * SIZE; }
    inline size_t columns() const { return SIZE; }
    inline size_t rows() const { return SIZE; }
    inline size_t blocksInRow() const { return SIZE / 3; }
    inline size_t blocksInColumn() const { return SIZE / 3; }
    inline size_t itemsInRowInBlock() const { return SIZE / 3; }
    inline size_t itemsInColumnInBlock() const { return SIZE / 3; }

    const MatrixItem& getItem(size_t row, size_t column) const;
    MatrixItem& getItem(size_t row, size_t column);
    void setItem(size_t row, size_t column, const MatrixItem& value);
    bool isValid() const;
    void reset();
    void shuffle(DifficultLevel level);

private:
    using Line = std::array<MatrixItem, SIZE>;
    
    std::array<Line, SIZE> m_data;
    MatrixShuffler m_shuffler;
};
