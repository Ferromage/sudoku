#include "matrix.h"

#include <stdexcept>
#include <unordered_set>

Matrix::Matrix() {
    reset();
}

Matrix::Matrix(const Matrix &rhs) {
    m_data = rhs.m_data;
}

const MatrixItem& Matrix::getItem(size_t row, size_t column) const {
    if (row >= rows() || column >= columns()) {
        throw std::out_of_range("Matrix::getItem() out of range (1)");
    }
    return m_data[row][column];
}

MatrixItem& Matrix::getItem(size_t row, size_t column) {
    if (row >= rows() || column >= columns()) {
        throw std::out_of_range("Matrix::getItem() out of range (2)");
    }
    return m_data[row][column];
}

void Matrix::setItem(size_t row, size_t column, const MatrixItem& value) {
    if (row >= rows() || column >= columns()) {
        throw std::out_of_range("Matrix::setItem() out of range");
    }        
    m_data[row][column] = value;
}

//setup basic matrix
void Matrix::reset() {
    const int base[SIZE][SIZE] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},        
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {9, 1, 2, 3, 4, 5, 6, 7, 8}
    };
    
    for (size_t row = 0; row < rows(); row++) {
        for (size_t col = 0; col < columns(); col++) {
            m_data[row][col].setGeneratedValue(base[row][col]);
        }
    }
}

bool Matrix::isValid() const {
    std::unordered_set<int> lineBuf;
    std::unordered_set<int> blockBuf[SIZE / 3];
    std::unordered_set<int> columnBuf[SIZE];

    for (size_t row = 0; row < rows(); row++) {
        for (size_t col = 0; col < columns(); col++) {
            const auto& item = m_data[row][col];
            const auto value = item.value();

            if (!item.isGuessed()) {
                return false;
            }

            if (lineBuf.count(value)) {
                return false;
            }
            lineBuf.insert(value);

            const int block = col / 3;
            if (blockBuf[block].count(value)) {
                return false;
            }
            blockBuf[block].insert(value);

            if (columnBuf[col].count(value)) {
                return false;
            }
            columnBuf[col].insert(value);
        }

        lineBuf.clear();

        if (row == 2 || row == 5) {
            blockBuf[0].clear();
            blockBuf[1].clear();
            blockBuf[2].clear();
        }
    }

    return true;
}

void Matrix::shuffle(DifficultLevel level) {
    m_shuffler.shuffleValues(*this);
    m_shuffler.shuffleAttributes(*this, level);
}


bool Matrix::operator== (const Matrix& rhs) const {
    for (size_t row = 0; row < rows(); row++) {
        for (size_t col = 0; col < columns(); col++) {
            if (m_data[row][col] != rhs.m_data[row][col]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!= (const Matrix& rhs) const {
    return !(*this == rhs);
}

bool Matrix::isFilledByUser() const {
    for (size_t row = 0; row < rows(); row++) {
        for (size_t col = 0; col < columns(); col++) {
            if (m_data[row][col].state() == MatrixItem::State::Hidden) {
                return false;
            }
        }
    }
    return true;
}
