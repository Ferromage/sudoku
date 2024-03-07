#include "matrix_shuffler.h"
#include "matrix.h"

#include <numeric>
#include <algorithm>
#include <set>

MatrixShuffler::MatrixShuffler() {
    std::random_device rd;
    m_randomGen.seed(rd());
}

void MatrixShuffler::shuffleValues(Matrix &matrix) {
    static constexpr int typeActionCount = 5;
    
    for (int i = 0; i < actionCount; i++) {
        const int funcNum = m_randomGen() % typeActionCount;
        switch (funcNum) {
            case 0 : transposeMatrix(matrix); break;
            case 1 : swapTwoRows(matrix); break;
            case 2 : swapTwoColumns(matrix); break;
            case 3 : swapTwoRegionsHorizontal(matrix); break;
            case 4 : swapTwoRegionsVertical(matrix); break;
        }
    }
}

void MatrixShuffler::shuffleAttributes(Matrix &matrix, DifficultLevel level) {
    static constexpr int hiddenCellCount[] = {30, 50, 65};

    const auto lvl = static_cast<int>(level);
    if (0 <= lvl && lvl < sizeof(hiddenCellCount) / sizeof(hiddenCellCount[0])) {
        std::set<std::pair<size_t, size_t>> coordinates;
        int insertedItemCnt = 0;
        while (insertedItemCnt < hiddenCellCount[lvl]) {
            const size_t row = m_randomGen() % matrix.rows();
            const size_t col = m_randomGen() % matrix.columns();
            
            if (coordinates.count({row, col}) == 0) {
                coordinates.insert({row, col});
                insertedItemCnt++;
            }
        }

        for (const auto& [row, col] : coordinates) {
            matrix.m_data[row][col].setHiddenState();
        }
    }
}

void MatrixShuffler::transposeMatrix(Matrix &matrix) {
    const Matrix tmp = matrix;

    for (size_t row = 0; row < tmp.rows(); row++) {
        for (size_t col = 0; col < tmp.columns(); col++) {
            matrix.m_data[col][row] = tmp.m_data[row][col];
        }
    }
}

void MatrixShuffler::swapTwoRows(Matrix &matrix) {
    const int block = m_randomGen() % matrix.blocksInColumn();
    const int row1 = (m_randomGen() % matrix.itemsInColumnInBlock()) + block * matrix.itemsInColumnInBlock();
    const int row2 = (m_randomGen() % matrix.itemsInColumnInBlock()) + block * matrix.itemsInColumnInBlock();

    if (row1 != row2) {
        std::swap_ranges(matrix.m_data[row1].begin(), matrix.m_data[row1].end(), matrix.m_data[row2].begin());
    }
}

void MatrixShuffler::swapTwoColumns(Matrix &matrix) {
    const int block = m_randomGen() % matrix.blocksInRow();
    const int col1 = (m_randomGen() % matrix.itemsInRowInBlock()) + block * matrix.itemsInRowInBlock();
    const int col2 = (m_randomGen() % matrix.itemsInRowInBlock()) + block * matrix.itemsInRowInBlock();

    if (col1 != col2) {
        for (size_t row = 0; row < matrix.rows(); row++) {
            std::swap(matrix.m_data[row][col1], matrix.m_data[row][col2]);
        }
    }
}

void MatrixShuffler::swapTwoRegionsHorizontal(Matrix &matrix) {
    const int block1 = m_randomGen() % matrix.blocksInColumn();
    const int block2 = m_randomGen() % matrix.blocksInColumn();

    if (block1 != block2) {
        const int row1 = block1 * matrix.itemsInColumnInBlock();
        const int row2 = block2 * matrix.itemsInColumnInBlock();

        std::swap_ranges(matrix.m_data[row1 + 0].begin(), matrix.m_data[row1 + 0].end(), matrix.m_data[row2 + 0].begin());
        std::swap_ranges(matrix.m_data[row1 + 1].begin(), matrix.m_data[row1 + 1].end(), matrix.m_data[row2 + 1].begin());
        std::swap_ranges(matrix.m_data[row1 + 2].begin(), matrix.m_data[row1 + 2].end(), matrix.m_data[row2 + 2].begin());
    }
}

void MatrixShuffler::swapTwoRegionsVertical(Matrix &matrix) {
    const int block1 = m_randomGen() % matrix.blocksInRow();
    const int block2 = m_randomGen() % matrix.blocksInRow();

    if (block1 != block2) {
        const int col1 = block1 * matrix.itemsInRowInBlock();
        const int col2 = block2 * matrix.itemsInRowInBlock();

        for (size_t row = 0; row < matrix.rows(); row++) {
            std::swap(matrix.m_data[row][col1 + 0], matrix.m_data[row][col2 + 0]);
            std::swap(matrix.m_data[row][col1 + 1], matrix.m_data[row][col2 + 1]);
            std::swap(matrix.m_data[row][col1 + 2], matrix.m_data[row][col2 + 2]);
        }
    }
}
